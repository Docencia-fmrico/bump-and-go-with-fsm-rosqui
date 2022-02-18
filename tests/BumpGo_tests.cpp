#include "ros/ros.h"
#include "kobuki_msgs/BumperEvent.h"
#include "geometry_msgs/Twist.h"

#include "fsm_bump_go/BumpGo.h"
#include <gtest/gtest.h>

static const int GOING_FORWARD = 0;
static const int GOING_BACK = 1;
static const int TURNING_LEFT = 2;
static const int TURNING_RIGHT = 3;


class TestBumpGo : public fsm_bump_go::BumpGo
{
public:

    bool get_detected_()
    {
        return detected_;
    }
    int get_state_()
    {
        return state_;
    }
    void set_state_(int new_state)
    {
        state_ = new_state;
    }
    void set_detected_(bool new_detected)
    {
        detected_ = new_detected;
    }

};
TEST(BumpGo_test_1, test_set_reading)
{
    TestBumpGo fsm_bump_go;

    ASSERT_EQ(fsm_bump_go.get_detected_(), false);
    ASSERT_EQ(fsm_bump_go.get_state_(), GOING_FORWARD);
}

TEST(BumpGo_test_2, test_set_reading)
{
    TestBumpGo fsm_bump_go;

    fsm_bump_go.set_detected_(true);
    fsm_bump_go.step();
    ASSERT_EQ(fsm_bump_go.get_state_(), GOING_BACK);
}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    ros::init(argc, argv, "fsm_bump_go");
    return RUN_ALL_TESTS();
}