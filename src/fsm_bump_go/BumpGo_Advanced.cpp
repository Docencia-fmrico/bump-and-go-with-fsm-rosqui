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

#include "fsm_bump_go/BumpGo_Advanced.h"

#include "kobuki_msgs/BumperEvent.h"
#include "geometry_msgs/Twist.h"

#include "ros/ros.h"

namespace fsm_bump_go
{

// Constructor
BumpGo_Advanced::BumpGo_Advanced()
{
  pressed_ = false;
  state_= GOING_FORWARD;
  // n_ es el NodeHandler. Se encarga de suscribir y publicar donde haga falta.
  sub_bumber_ = n_.subscribe("/mobile_base/events/bumper", 100, &BumpGo_Advanced::bumperCallback, this);
  pub_vel_ = n_.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity",1);
}

void
BumpGo_Advanced::bumperCallback(const kobuki_msgs::BumperEvent::ConstPtr& msg)
{
  pressed_ = msg->state == kobuki_msgs::BumperEvent::PRESSED ;
  bumper_ =  msg->bumper;

  ROS_INFO("BUMPER: [%d]", bumper_);

}

}  // namespace fsm_bump_go
