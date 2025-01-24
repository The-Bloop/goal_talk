#include "goal_talk.h"
#include <typeinfo>
using namespace std::chrono_literals;

GTNode::GTNode(const std::string &nodeName) : rclcpp::Node(nodeName)
{
    action_client_ptr = rclcpp_action::create_client<NavigateToPose>(this, "/navigate_to_pose");
    RCLCPP_INFO(get_logger(),"Init done");
    
}

void GTNode::setup()
{
    //action_client_ptr = rclcpp_action::create_client<NavigateToPose>(this, "/navigate_to_pose");
    const auto timer_period = 1000ms;
    timer_ = this->create_wall_timer(timer_period, std::bind(&GTNode::talk, this));

    rclcpp::spin(shared_from_this());
    //rclcpp::shutdown();
}

void GTNode::talk()
{
    timer_->cancel();
    auto  send_goal_options = rclcpp_action::Client<NavigateToPose>::SendGoalOptions();
    send_goal_options.result_callback = std::bind(&GTNode::nav_to_pose_result_callback, this, std::placeholders::_1);
    send_goal_options.goal_response_callback = std::bind(&GTNode::nav_to_pose_goal_handle_callback, this, std::placeholders::_1);
    send_goal_options.feedback_callback = std::bind(&GTNode::nav_to_pose_feedback_callback, this, std::placeholders::_1, std::placeholders::_2);

    auto goal_msg = NavigateToPose::Goal();
    goal_msg.pose.header.frame_id = "base_footprint";
    goal_msg.pose.pose.position.x = 0.75;
    goal_msg.pose.pose.position.y = 0.75;

    tf2::Quaternion q;
    q.setRPY(0, 0, 2.653);
    q.normalize();
    goal_msg.pose.pose.orientation = tf2::toMsg(q);

    action_client_ptr->async_send_goal(goal_msg, send_goal_options);
    RCLCPP_INFO(get_logger(), "Goal Sent");

}

void GTNode::nav_to_pose_result_callback(const GoalHandleNav::WrappedResult &result)
{
    if(result.result)
    {
        RCLCPP_INFO(this->get_logger(),"Goal Reached");
    }
    else
    {
        RCLCPP_WARN(this->get_logger(), "Some Error, Check goal location");
    }
    rclcpp::shutdown();
}

void GTNode::nav_to_pose_goal_handle_callback(const GoalHandleNav::SharedPtr &goalHandle)
{
    RCLCPP_INFO(get_logger(), "Inside goal handler");
    auto handler = goalHandle.get();
    if(!handler)
    {
        RCLCPP_ERROR(this->get_logger(), "Goal was not handled");
    }
    else
    {
        RCLCPP_INFO(this->get_logger(), "Goal Handled, Moving on to next step");
    }
}

void GTNode::nav_to_pose_feedback_callback(const GoalHandleNav::SharedPtr, const std::shared_ptr<const NavigateToPose::Feedback> feedback)
{
    std::stringstream ss;
    ss << "Next number in sequence received: ";
    /*for (auto number : feedback->partial_sequence) {
      ss << number << " ";
    }*/
    RCLCPP_INFO(this->get_logger(), "Next number in sequence received: ");
}

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<GTNode>("goal_talk_node");
    node->setup();

    return 0;
}
