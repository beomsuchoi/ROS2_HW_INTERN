#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/int64.hpp"
#include <iostream>
#include <string>

class TalkerNode : public rclcpp::Node {
public:
    TalkerNode() : Node("talker"), count_(1) {
        // 퍼블리셔 생성
        string_publisher_ = this->create_publisher<std_msgs::msg::String>("/chatter_cli", 10);
        count_publisher_ = this->create_publisher<std_msgs::msg::Int64>("/chatter_count", 10);
    }

    void publishMessage() {
        std::cout << "Enter message: ";
        std::string input;
        std::getline(std::cin, input);

        auto message = std_msgs::msg::String();
        message.data = input;
        string_publisher_->publish(message);

        auto count_message = std_msgs::msg::Int64();
        count_message.data = count_++;
        count_publisher_->publish(count_message);

        RCLCPP_INFO(this->get_logger(), "Published: \"%s\", Count: %d", input.c_str(), count_message.data);
    }

private:
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr string_publisher_;
    rclcpp::Publisher<std_msgs::msg::Int64>::SharedPtr count_publisher_;
    int count_;
};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TalkerNode>();

    while (rclcpp::ok()) {
        node->publishMessage();
        rclcpp::spin_some(node);
    }

    rclcpp::shutdown();
    return 0;
}

