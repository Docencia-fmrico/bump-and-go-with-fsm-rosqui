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

#include "fsm_bump_go/BumpGo_basic.h"

namespace fsm_bump_go
{

// Constructor
BumpGo_basic()
: BumpGo_base() { state_(GOING_FORWARD) pressed_(false); }
{
  // n_ es el NodeHandler. Se encarga de suscribir y publicar donde haga falta.
  sub_bumber_ = n_.subscribe("/mobile_base/events/bumper", 1, &BumpGo::Callback, this);
  pub_vel_ = n_.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity",1);
}

void
BumpGo_basic::Callback(const kobuki_msgs::BumperEvent::ConstPtr& msg)
{
  pressed_ = msg->state == kobuki_msgs::BumperEvent::PRESSED ;
  //  ...
}

void
BumpGo_basic::step()
{
  geometry_msgs::Twist cmd;

  switch (state_)
  {
    case GOING_FORWARD:
      cmd.linear.x = FORWARD_VEL;
      cmd.angular.z = 0;

      if (pressed_)
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
        state_ = TURNING;
        ROS_INFO("GOING_BACK -> TURNING");
      }

      break;
    case TURNING:
      cmd.linear.x = 0;
      cmd.angular.z = TURNING_VEL;

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
