#include "chatter_cli/listener.hpp"

ListenerNode::ListenerNode() : Node("listener"), received_count_(-1) {
    string_subscription_ = this->create_subscription<std_msgs::msg::String>(
        "/chatter_cli", 10, std::bind(&ListenerNode::Callback, this, std::placeholders::_1));
    
    count_subscription_ = this->create_subscription<std_msgs::msg::Int64>(
        "/chatter_count", 10, std::bind(&ListenerNode::count_cb, this, std::placeholders::_1));
}

void ListenerNode::Callback(const std_msgs::msg::String::SharedPtr msg) {
    received_message_ = msg->data;
    display_msg();
}

void ListenerNode::count_cb(const std_msgs::msg::Int64::SharedPtr msg) {
    received_count_ = msg->data;
    display_msg();
}

void ListenerNode::display_msg() {
    if (!received_message_.empty() && received_count_ != -1) {
        RCLCPP_INFO(this->get_logger(), "Subscribed: \"%s\" \"%d\"", received_message_.c_str(), received_count_);
    }
}
