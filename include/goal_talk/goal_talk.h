#include "rclcpp/rclcpp.hpp"
#include "nav2_msgs/action/navigate_to_pose.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include <tf2/LinearMath/Quaternion.h>
#include "tf2_geometry_msgs/tf2_geometry_msgs.hpp"
#include <string>

class GTNode : public rclcpp::Node
{
    public:

        explicit GTNode(const std::string &node_name);
        void setup();
        void talk();
    
    private:

        using NavigateToPose = nav2_msgs::action::NavigateToPose;
        using GoalHandleNav = rclcpp_action::ClientGoalHandle<NavigateToPose>;

        rclcpp_action::Client<NavigateToPose>::SharedPtr action_client_ptr;
        rclcpp::TimerBase::SharedPtr timer_;

        void nav_to_pose_result_callback(const GoalHandleNav::WrappedResult &result);
        void nav_to_pose_goal_handle_callback(const GoalHandleNav::SharedPtr &goal_handle);
        void nav_to_pose_feedback_callback(const GoalHandleNav::SharedPtr, const std::shared_ptr<const NavigateToPose::Feedback> feedback);
    
};