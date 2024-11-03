#ifndef LISTENER_HPP
#define LISTENER_HPP

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/int64.hpp"
#include <string>

class ListenerNode : public rclcpp::Node {
public:
    ListenerNode();

private:
    void Callback(const std_msgs::msg::String::SharedPtr msg);
    void count_cb(const std_msgs::msg::Int64::SharedPtr msg);
    void display_msg();

    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr string_subscription_;
    rclcpp::Subscription<std_msgs::msg::Int64>::SharedPtr count_subscription_;
    std::string received_message_;
    int received_count_;
};

#endif // LISTENER_HPP
