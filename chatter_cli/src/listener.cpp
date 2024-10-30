#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/int64.hpp"

class ListenerNode : public rclcpp::Node {
public:
    ListenerNode() : Node("listener") {
        // 구독자 생성
        string_subscription_ = this->create_subscription<std_msgs::msg::String>(
            "/chatter_cli", 10, std::bind(&ListenerNode::Callback, this, std::placeholders::_1));
        
        count_subscription_ = this->create_subscription<std_msgs::msg::Int64>(
            "/chatter_count", 10, std::bind(&ListenerNode::count_cb, this, std::placeholders::_1));
    }

private:
    void Callback(const std_msgs::msg::String::SharedPtr msg) {
        received_message_ = msg->data;
        display_msg();
    }

    void count_cb(const std_msgs::msg::Int64::SharedPtr msg) {
        received_count_ = msg->data;
        display_msg();
    }

    void display_msg() {
        if (!received_message_.empty() && received_count_ != -1) {
            RCLCPP_INFO(this->get_logger(), "Subscribed: \"%s\" \"%d\"", received_message_.c_str(), received_count_);
        }
    }

    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr string_subscription_;
    rclcpp::Subscription<std_msgs::msg::Int64>::SharedPtr count_subscription_;
    std::string received_message_;
    int received_count_ = -1;
};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ListenerNode>());
    rclcpp::shutdown();
    return 0;
}

