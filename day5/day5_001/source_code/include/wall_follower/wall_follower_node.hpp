#ifndef WALL_FOLLOWER__WALL_FOLLOWER_NODE_HPP_
#define WALL_FOLLOWER__WALL_FOLLOWER_NODE_HPP_

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
#include "geometry_msgs/msg/twist.hpp"

class WallFollowerNode : public rclcpp::Node {
public:
    WallFollowerNode();

private:
    void scanCallback(const sensor_msgs::msg::LaserScan::SharedPtr scan_msg);

    rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr scan_subscriber_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_publisher_;
    double desired_distance_;
};

#endif  // WALL_FOLLOWER__WALL_FOLLOWER_NODE_HPP_
