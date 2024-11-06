#include "rclcpp/rclcpp.hpp"
#include "wall_follower/wall_follower_node.hpp"  // wall_follower_node.cpp가 선언된 헤더 파일

int main(int argc, char * argv[]) {
    // ROS 2 노드 초기화
    rclcpp::init(argc, argv);

    // WallFollowerNode 노드 실행
    auto node = std::make_shared<WallFollowerNode>();
    rclcpp::spin(node);

    // ROS 2 종료
    rclcpp::shutdown();
    return 0;
}
