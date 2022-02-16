#include "ros/ros.h"
#include "kobuki_msgs/BumperEvent.h"
#include "geometry_msgs/Twist.h"

#include "fsm_bump_go/BumpGo_Advanced.h"
#include <gtest/gtest.h>

class TestBumpGo_Advanced : public fsm_bump_go::BumpGo_Advanced
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
};
TEST(my_test, test_set_reading)
{
    TestBumpGo_Advanced fsm_bump_go;

    ASSERT_EQ(fsm_bump_go.get_detected_(), false);
    ASSERT_EQ(fsm_bump_go.get_state_(), 0);

}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    ros::init(argc, argv, "fsm_bump_go");
    return RUN_ALL_TESTS();
}