#include "rclcpp/rclcpp.hpp"
#include "turtlesim_cli/turtlesim_cli.hpp"

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TurtlesimCliNode>();  // TurtlesimCliNode로 수정
    node->start_cli();
    rclcpp::shutdown();
    return 0;
}
