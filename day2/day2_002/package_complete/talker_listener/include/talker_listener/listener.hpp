/**
 * @file /include/talker_listener/listener.hpp
 *
 * @brief ROS 2 listener node for subscribing to messages, with Qt signal support.
 *
 **/

#ifndef TALKER_LISTENER_LISTENER_HPP_
#define TALKER_LISTENER_LISTENER_HPP_

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <QObject>
#include <QString>

class Listener : public QObject, public rclcpp::Node
{
  Q_OBJECT

public:
  Listener();

signals:
  void messageReceived(const QString &message);  // 메시지를 전달하는 시그널

private:
  void messageCallback(const std_msgs::msg::String::SharedPtr msg);  // 메시지 수신 콜백 함수
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;  // 서브스크라이버
};

#endif  // TALKER_LISTENER_LISTENER_HPP_
