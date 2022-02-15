#include "ros/ros.h"
#include "kobuki_msgs/BumperEvent.h"
#include "geometry_msgs/Twist.h"

#include "fsm_bump_go/BumpGo.h"
#include <gtest/gtest.h>

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
};
TEST(my_test, test_set_reading)
{
    TestBumpGo fsm_bump_go;

    ASSERT_EQ(fsm_bump_go.get_detected_(), false);
    ASSERT_EQ(fsm_bump_go.get_state_(), 0);

}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}