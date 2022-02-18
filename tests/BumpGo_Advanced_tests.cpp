#include "ros/ros.h"
#include "kobuki_msgs/BumperEvent.h"
#include "geometry_msgs/Twist.h"

#include "fsm_bump_go/BumpGo_Advanced.h"
#include <gtest/gtest.h>

  static const int GOING_FORWARD = 0;
  static const int GOING_BACK = 1;
  static const int TURNING_LEFT = 2;
  static const int TURNING_RIGHT = 3;

  static const int DETECTED_LEFT = 0;
  static const int DETECTED_FRONT = 1;
  static const int DETECTED_RIGHT = 2;

class TestBumpGo_Advanced : public fsm_bump_go::BumpGo_Advanced
{
public:
    bool get_detected_()
    {
        return detected_;
    }
    void set_detected_(bool new_detected)
    {
        detected_ = new_detected;
    }
    int get_state_()
    {
        return state_;
    }
    void set_state_(int new_state)
    {
        state_ = new_state;
    }
    void set_direction_(int new_direction)
    {
        direction_ = new_direction;
    }
    void set_time_(ros::Time ts_)
    {
        press_ts_ = ts_;
    }
};
TEST(BumpGo_Advanced_test1, test_set_reading)
{
    TestBumpGo_Advanced fsm_bump_go;

    ASSERT_EQ(fsm_bump_go.get_detected_(), false);
    ASSERT_EQ(fsm_bump_go.get_state_(), GOING_FORWARD);

    fsm_bump_go.set_detected_(true);
    fsm_bump_go.step();
    ASSERT_EQ(fsm_bump_go.get_state_(), GOING_BACK);
    fsm_bump_go.set_direction_(DETECTED_LEFT);

    fsm_bump_go.set_state_(TURNING_RIGHT);
    
    ASSERT_EQ(fsm_bump_go.get_state_(), TURNING_RIGHT);

}

TEST(BumpGo_Advanced_test2, test_set_reading)
{
    TestBumpGo_Advanced fsm_bump_go;

    ASSERT_EQ(fsm_bump_go.get_detected_(), false);
    ASSERT_EQ(fsm_bump_go.get_state_(), GOING_FORWARD);

    fsm_bump_go.set_detected_(true);
    fsm_bump_go.step();
    ASSERT_EQ(fsm_bump_go.get_state_(), GOING_BACK);
    fsm_bump_go.set_direction_(DETECTED_RIGHT);

    fsm_bump_go.set_state_(TURNING_LEFT);
    
    ASSERT_EQ(fsm_bump_go.get_state_(), TURNING_LEFT);

}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    ros::init(argc, argv, "fsm_bump_go");
    return RUN_ALL_TESTS();
}