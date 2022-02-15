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

#ifndef FSM_BUMP_GO_NEARGO_H
#define FSM_BUMP_GO_NEARGO_H

//Clase padre
#include "fsm_bump_go/BumpGo_Base.h"

#include "ros/ros.h"

#include "geometry_msgs/Twist.h"

namespace fsm_bump_go
{

class NearGo: public BumpGo_Base
{
public:
  NearGo();
  virtual void step();
};

}  // namespace fsm_bump_go

#endif  // FSM_BUMP_GO_NEARGO_H