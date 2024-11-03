#ifndef TALKER_HPP
#define TALKER_HPP

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/int64.hpp"
#include <string>

class TalkerNode : public rclcpp::Node {
public:
    TalkerNode();
    void publishMessage();

private:
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr string_publisher_;
    rclcpp::Publisher<std_msgs::msg::Int64>::SharedPtr count_publisher_;
    int count_;
};

#endif // TALKER_HPP
