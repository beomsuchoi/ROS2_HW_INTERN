#ifndef QNODE_HPP_
#define QNODE_HPP_

#include <rclcpp/rclcpp.hpp>
#include <QObject>
#include <QThread>
#include <geometry_msgs/msg/twist.hpp>
#include <std_srvs/srv/empty.hpp>
#include <rclcpp/parameter_client.hpp> // 파라미터 관련 서비스
#include <turtlesim/srv/set_pen.hpp>

class QNode : public QThread {
  Q_OBJECT
public:
  QNode();
  ~QNode();
  void publishVelocity(double linear_x, double angular_z);
  void backgroundColor(int r, int g, int b); // 배경색 변경 메서드
  void lineColor(int r, int g, int b); // 선 색상을 변경하는 함수
  void PenWidth(int width);

protected:
  void run();

private:
  std::shared_ptr<rclcpp::Node> node;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr velocity_pub;
  rclcpp::Client<std_srvs::srv::Empty>::SharedPtr clear_client;
  rclcpp::Client<turtlesim::srv::SetPen>::SharedPtr set_pen_client;

  int current_r = 0;  // 현재 펜 색상 R 값
  int current_g = 0;  // 현재 펜 색상 G 값
  int current_b = 0;  // 현재 펜 색상 B 값
  int current_width = 1;  // 현재 펜 두께 값

Q_SIGNALS:
  void rosShutDown();
  void cmdVelPublished(QString data);

};

#endif // QNODE_HPP_
