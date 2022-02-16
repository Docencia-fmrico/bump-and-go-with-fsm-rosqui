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
  src/fsm_bump_go/BumpGo_Advanced.cpp
  src/fsm_bump_go/BumpGo.cpp
)

add_executable(bumpgo_node src/bumpgo_node.cpp)
add_executable(bumpgo_node_advanced src/bumpgo_node_advanced.cpp)
target_link_libraries(bumpgo_node ${catkin_LIBRARIES} ${PROJECT_NAME})
target_link_libraries(bumpgo_node_advanced ${catkin_LIBRARIES} ${PROJECT_NAME})

roslint_cpp(
 src/bumpgo_node.cpp
 src/bumpgo_node_advanced.cpp
 src/fsm_bump_go/BumpGo.cpp
 src/fsm_bump_go/BumpGo_Advanced.cpp
 include/fsm_bump_go/BumpGo.h
 include/fsm_bump_go/BumpGo_Advanced.h
 include/fsm_bump_go/BumpGo_Base.h
 
)

catkin_add_gtest(BumpGo_tests tests/BumpGo_tests)
add_dependencies(BumpGo_tests ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
if(TARGET BumpGo_tests)
  target_link_libraries(BumpGo_tests ${catkin_LIBRARIES} ${PROJECT_NAME})
endif()

catkin_add_gtest(BumpGo_Advanced_tests tests/BumpGo_Advanced_tests)
add_dependencies(BumpGo_Advanced_tests ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
if(TARGET BumpGo_Advanced_tests)
  target_link_libraries(BumpGo_Advanced_tests ${catkin_LIBRARIES} ${PROJECT_NAME})
endif()

catkin_add_gtest(NearGo tests/NearGo)
add_dependencies(NearGo ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
if(TARGET NearGo)
  target_link_libraries(NearGo ${catkin_LIBRARIES} ${PROJECT_NAME})
endif()