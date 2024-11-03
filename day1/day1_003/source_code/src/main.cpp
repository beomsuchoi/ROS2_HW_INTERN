#include "chatter_cli/talker.hpp"
#include "chatter_cli/listener.hpp"
#include "rclcpp/rclcpp.hpp"

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);

    auto talker_node = std::make_shared<TalkerNode>();
    auto listener_node = std::make_shared<ListenerNode>();

    // 하나의 루프에서 talker와 listener 처리
    while (rclcpp::ok()) {
        // talker 노드에서 메시지 퍼블리시
        talker_node->publishMessage();

        // listener 노드에서 수신된 메시지 처리
        rclcpp::spin_some(listener_node);
    }

    rclcpp::shutdown();
    return 0;
}
