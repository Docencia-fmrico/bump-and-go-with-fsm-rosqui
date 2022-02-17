// Copyright 2022 Intelligent Robotics Lab
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "fsm_bump_go/NearGo.h"

#include "geometry_msgs/Twist.h"

#include "ros/ros.h"

namespace fsm_bump_go
{

// Constructor
NearGo::NearGo()
{
  detected_ = false;
  state_= GOING_FORWARD;
  // n_ es el NodeHandler. Se encarga de suscribir y publicar donde haga falta.
  sub_laser_scan_ = n_.subscribe("/scan_filtered", 1, &NearGo::scanFilteredCallback, this);
  pub_vel_ = n_.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity",1);
}

float
NearGo::average(const sensor_msgs::LaserScan::ConstPtr& msg, int sector, int ranges_in_sector, int center)
{
  int divisor = ranges_in_sector;
  float average;
  float dividend = 0;

  for(int i = center + (sector*ranges_in_sector); i < center + ((sector+1)*ranges_in_sector); i++)
  {
    if(msg->ranges[i] > msg->range_max || msg->ranges[i] < msg->range_min)
    {
      divisor--;
    }else
    { 
      dividend += msg->ranges[i];
    }
  }
  if(!divisor)
  {// divisor = 0 => no hay lecturas en el rango, por lo que el sector apunta a infinito
    average = msg->range_max;
  }else{
    average = dividend/divisor;
  }
  // ROS_INFO("Average sector: %d = %f", sector, average); //Traza para calibrar el RPlidar
  return average;
}

// checks 20 sectors from:
// front -> right (number_ranges * proportion_to_check(0-0.5))
// front -> left 
// returns the sector wich average > MIN_RANGE_LASER
// else returns NUM_SECTORS +1 
int
NearGo::check_sector(const sensor_msgs::LaserScan::ConstPtr& msg, int num_ranges, float proportion_to_check, int center)
{
  int warning_sector = NUM_SECTORS+1;
  int ranges_in_sector = (num_ranges * proportion_to_check)/NUM_SECTORS;
  float sector_rang_avg;

  for(int sector = -NUM_SECTORS+1; sector < NUM_SECTORS; sector++)
  {
    if(MIN_RANGE_LASER > average(msg, sector, ranges_in_sector, center))
    {
      warning_sector = sector;
      ROS_INFO("WARNING SECTOR : %d", warning_sector);
      break;
    }
  }
  return warning_sector;
}

void
NearGo::scanFilteredCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
  float avg_right_values;
  float proportion = 0.1875;
  int num_ranges = (msg->angle_max-msg->angle_min)/msg->angle_increment;
  int front_range = num_ranges/2;
  int near_sector = check_sector(msg, num_ranges, proportion, front_range);

  if(near_sector < NUM_SECTORS && near_sector > CENTER_LIMIT_SECT)
  {
    detected_ = true;
    direction_ = DETECTED_RIGHT;
    ROS_INFO("DETECTED_RIGHT");
  }
  else if(near_sector > -NUM_SECTORS && near_sector < -CENTER_LIMIT_SECT)
  {
    detected_ = true;
    direction_ = DETECTED_LEFT;
    ROS_INFO("DETECTED_LEFT");
  }
  else if(near_sector > -CENTER_LIMIT_SECT && near_sector < CENTER_LIMIT_SECT)
  {
    detected_ = true;
    direction_ = DETECTED_FRONT;
    ROS_INFO("DETECTED_FRONT");
  }
  else
  {
    detected_ = false;
  }
}

void
NearGo::step()
{
  geometry_msgs::Twist cmd;

  switch (state_)
  {
    case GOING_FORWARD:
      cmd.linear.x = FORWARD_VEL;
      cmd.angular.z = 0;

      if (detected_)
      {
        press_ts_ = ros::Time::now();
        state_ = GOING_BACK;
        ROS_INFO("GOING_FORWARD -> GOING_BACK");
      }

      break;
    case GOING_BACK:
      cmd.linear.x = BACK_VEL;
      cmd.angular.z = 0;

      if ((ros::Time::now() - press_ts_).toSec() > BACKING_TIME )
      {
        turn_ts_ = ros::Time::now();
        if(direction_ == DETECTED_LEFT)
        {
          state_ = TURNING_RIGHT;
          ROS_INFO("GOING_BACK -> TURNING_RIGHT");
        }
        else
        {
          state_ = TURNING_LEFT;
          ROS_INFO("GOING_BACK -> TURNING_LEFT");
        }
      }

      break;
    case TURNING_LEFT:
      cmd.linear.x = 0;
      cmd.angular.z = TURNING_VEL_LEFT;

      if ((ros::Time::now()-turn_ts_).toSec() > TURNING_TIME )
      {
        state_ = GOING_FORWARD;
        ROS_INFO("TURNING -> GOING_FORWARD");
      }
      break;
    case TURNING_RIGHT:
      cmd.linear.x = 0;
      cmd.angular.z = TURNING_VEL_RIGHT;

      if ((ros::Time::now()-turn_ts_).toSec() > TURNING_TIME )
      {
        state_ = GOING_FORWARD;
        ROS_INFO("TURNING -> GOING_FORWARD");
      }
      break;
  }
    pub_vel_.publish(cmd);
}

}  // namespace fsm_bump_go
