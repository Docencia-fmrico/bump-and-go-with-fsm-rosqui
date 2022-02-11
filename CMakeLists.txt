cmake_minimum_required(VERSION 2.8.3)
project(fsm_bump_go)

set(CMAKE_CXX_STANDARD 17)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  roslint
)

catkin_package(
CATKIN_DEPENDS roscpp std_msgs kobuki_msgs sensor_msgs
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  include
)

add_library(${PROJECT_NAME}
  src/fsm_bump_go/BumpGo_basic.cpp
)

add_executable(bumpgo_basic_node src/bumpgo_basic_node.cpp)
target_link_libraries(bumpgo_basic_node ${catkin_LIBRARIES} ${PROJECT_NAME})

roslint_cpp(
 src/bumpgo_basic_node.cpp
 src/fsm_bump_go/BumpGo_base.cpp
 src/fsm_bump_go/BumpGo_basic.cpp
 include/fsm_bump_go/BumpGo.h
)
