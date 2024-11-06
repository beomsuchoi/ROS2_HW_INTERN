#include "wall_follower/wall_follower_node.hpp"

WallFollowerNode::WallFollowerNode() : Node("wall_follower")
{
    this->declare_parameter<double>("desired_distance", 1.4); // 벽과의 목표 거리
    this->get_parameter("desired_distance", desired_distance_);

    scan_subscriber_ = this->create_subscription<sensor_msgs::msg::LaserScan>(
        "/scan", 10, std::bind(&WallFollowerNode::scanCallback, this, std::placeholders::_1));

    cmd_vel_publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);
}

void WallFollowerNode::scanCallback(const sensor_msgs::msg::LaserScan::SharedPtr scan_msg)
{
    double left_distance = scan_msg->ranges[270];
    double right_distance = scan_msg->ranges[90];
    double front_distance = scan_msg->ranges[0];

    geometry_msgs::msg::Twist cmd_vel_msg;
    cmd_vel_msg.linear.x = 0.15; // 전진 속도 설정

    if (front_distance < desired_distance_)
    {
        cmd_vel_msg.angular.z = -0.7; // 오른쪽으로 회전
        RCLCPP_INFO(this->get_logger(), "Front wall");
    }

    // 오른쪽 벽이 가까울 때 왼쪽으로 회전
    else if (right_distance < desired_distance_)
    {
        cmd_vel_msg.angular.z = 0.7; // 왼쪽으로 회전
        RCLCPP_INFO(this->get_logger(), "Turning left.");
    }
    // 왼쪽 벽이 가까울 때 오른쪽으로 회전
    else if (left_distance < desired_distance_)
    {
        cmd_vel_msg.angular.z = -0.7; // 오른쪽으로 회전
        RCLCPP_INFO(this->get_logger(), "Turning right.");
    }
    // 양쪽 벽이 적절한 거리일 때는 직진
    else
    {
        cmd_vel_msg.angular.z = 0.0;
        RCLCPP_INFO(this->get_logger(), "Both sides clear. Moving straight.");
    }

    RCLCPP_INFO(this->get_logger(), "Left distance: %f, Right distance: %f", left_distance, right_distance);
    RCLCPP_INFO(this->get_logger(), "cmd_vel: linear.x=%f, angular.z=%f",
                cmd_vel_msg.linear.x, cmd_vel_msg.angular.z);

    cmd_vel_publisher_->publish(cmd_vel_msg);
}
