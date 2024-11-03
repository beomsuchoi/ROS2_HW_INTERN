/**
 * @file /include/talker_listener/talker.hpp
 *
 * @brief ROS 2 talker node for publishing messages.
 *
 **/

#ifndef TALKER_LISTENER_TALKER_HPP_
#define TALKER_LISTENER_TALKER_HPP_

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

class Talker : public rclcpp::Node
{
public:
  Talker();
  void publishMessage(const std::string &message);  // 메시지 퍼블리시 메서드

private:
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;  // 퍼블리셔
};

#endif  // TALKER_LISTENER_TALKER_HPP_
