#include "chatter_cli/talker.hpp"
#include <iostream>


TalkerNode::TalkerNode() : Node("talker"), count_(1) {
    string_publisher_ = this->create_publisher<std_msgs::msg::String>("/chatter_cli", 10);
    count_publisher_ = this->create_publisher<std_msgs::msg::Int64>("/chatter_count", 10);
}

void TalkerNode::publishMessage() {
    std::cout << "Enter message: ";
    std::string input;
    std::getline(std::cin, input);

    auto message = std_msgs::msg::String();
    message.data = input;
    string_publisher_->publish(message);

    auto count_message = std_msgs::msg::Int64();
    count_message.data = count_++;
    count_publisher_->publish(count_message);

    RCLCPP_INFO(this->get_logger(), "Published: \"%s\", Count: %ld", input.c_str(), count_message.data);
}
