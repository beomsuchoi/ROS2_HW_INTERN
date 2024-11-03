#include "qnode.hpp"
#include <QString>
#include <turtlesim/srv/set_pen.hpp>
#include <thread>

QNode::QNode() {
  int argc = 0;
  char** argv = nullptr;
  rclcpp::init(argc, argv);
  node = rclcpp::Node::make_shared("turtlesim_control");

  // 퍼블리셔 초기화
  velocity_pub = node->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);

  set_pen_client = node->create_client<turtlesim::srv::SetPen>("/turtle1/set_pen");
  // 배경색을 위한 clear 서비스 초기화
  clear_client = node->create_client<std_srvs::srv::Empty>("/clear");

  current_r = 0;
  current_g = 0;
  current_b = 0;
  current_width = 2;

  this->start();
}

QNode::~QNode() {
  if (rclcpp::ok()) {
    rclcpp::shutdown();
  }
}

void QNode::run() {
  rclcpp::WallRate loop_rate(20);
  while (rclcpp::ok()) {
    rclcpp::spin_some(node);
    loop_rate.sleep();
  }
  rclcpp::shutdown();
}

// 퍼블리시 함수 // 속도 제어
void QNode::publishVelocity(double linear_x, double angular_z) {
  geometry_msgs::msg::Twist twist;
  twist.linear.x = linear_x;
  twist.angular.z = angular_z;  
  velocity_pub->publish(twist);

  QString data = QString("velocity  : Linear=%1, Angular=%2").arg(linear_x).arg(angular_z);
  Q_EMIT cmdVelPublished(data);
}

// 배경색 변경 함수
void QNode::backgroundColor(int r, int g, int b) {
  auto param_client = std::make_shared<rclcpp::AsyncParametersClient>(node, "turtlesim");
  if (param_client->wait_for_service(std::chrono::seconds(1))) {
    param_client->set_parameters({
      rclcpp::Parameter("background_r", r),
      rclcpp::Parameter("background_g", g),
      rclcpp::Parameter("background_b", b)
    });

    if (clear_client->wait_for_service(std::chrono::seconds(1))) {
      auto request = std::make_shared<std_srvs::srv::Empty::Request>();
      clear_client->async_send_request(request);
    } else {
      RCLCPP_WARN(node->get_logger(), "Failed to call /clear service");
    }
  } else {
    RCLCPP_WARN(node->get_logger(), "Failed to set parameters on turtlesim node");
  }
}

// 선 색상 및 두께 설정 함수
void QNode::lineColor(int r, int g, int b) {
  current_r = r;
  current_g = g;
  current_b = b;

  if (set_pen_client->wait_for_service(std::chrono::seconds(1))) {
    auto request = std::make_shared<turtlesim::srv::SetPen::Request>();
    request->r = current_r;
    request->g = current_g;
    request->b = current_b;
    request->width = current_width;  // 현재 저장된 두께 사용
    request->off = 0;

    auto future = set_pen_client->async_send_request(request);
    if (future.wait_for(std::chrono::seconds(1)) == std::future_status::ready) {
      RCLCPP_INFO(node->get_logger(), "Pen color changed to RGB(%d, %d, %d) with width %d", current_r, current_g, current_b, current_width);
    } else {
      RCLCPP_WARN(node->get_logger(), "Failed to set pen attributes on turtlesim node");
    }
  } else {
    RCLCPP_WARN(node->get_logger(), "Service /turtle1/set_pen not available");
  }
}

// 펜 두께 설정 함수
void QNode::PenWidth(int width) {
  
  current_width = width;  // 현재 두께 값을 업데이트

  if (set_pen_client->wait_for_service(std::chrono::seconds(1))) {
    auto request = std::make_shared<turtlesim::srv::SetPen::Request>();
    request->width = current_width;
    request->r = current_r;  // 저장된 색상 값 사용
    request->g = current_g;
    request->b = current_b;
    request->off = 0;

    auto future = set_pen_client->async_send_request(request);
    if (future.wait_for(std::chrono::seconds(1)) == std::future_status::ready) {
      RCLCPP_INFO(node->get_logger(), "Pen width changed to %d with RGB(%d, %d, %d)", current_width, current_r, current_g, current_b);
    } else {
      RCLCPP_WARN(node->get_logger(), "Failed to set pen width on turtlesim node");
    }
  } else {
    RCLCPP_WARN(node->get_logger(), "Service /turtle1/set_pen not available");
  }
}

void QNode::clearDrawing() {
  if (clear_client->wait_for_service(std::chrono::seconds(1))) {
    auto request = std::make_shared<std_srvs::srv::Empty::Request>();
    clear_client->async_send_request(request);
    rclcpp::sleep_for(std::chrono::milliseconds(500));  // 잠시 기다림
  }
}

void QNode::drawCircle(double radius, double speed) {
    std::thread([this, radius, speed]() {
        double circumference = 2 * M_PI * radius;  // 원의 둘레 계산
        double duration = circumference / speed;    // 전체 이동 시간
        double travel_time = duration / 24;         // 24단계

        for (int i = 0; i < 26; i++) {              // 26단계 반복
            publishVelocity(speed, speed / radius); // 선속도와 각속도 설정
            rclcpp::sleep_for(std::chrono::milliseconds(static_cast<int>(travel_time * 1000))); // 대기 시간
        }
        publishVelocity(0, 0); // 멈춤
    }).detach(); // 스레드 분리
}//원이 끝까지 그려지지 않는 문제로 인해 원은 스레드 분리해 완성. 상단에서 thread include


void QNode::drawTriangle(int side_length) {
  const double speed_factor = 0.1;  // 속도 계수
  for (int i = 0; i < 3; ++i) {
    publishVelocity(side_length * speed_factor, 0.0);  // 이동
    rclcpp::sleep_for(std::chrono::seconds(2));  // 더 긴 시간 이동
    publishVelocity(0, 2 * M_PI / 3);  // 120도 회전
    rclcpp::sleep_for(std::chrono::milliseconds(1000));
  }
  publishVelocity(0, 0);  // 멈춤
}

void QNode::drawSquare(int side_length) {
  const double speed_factor = 0.1;  // 속도 계수
  for (int i = 0; i < 4; ++i) {
    publishVelocity(side_length * speed_factor, 0.0);  // 이동
    rclcpp::sleep_for(std::chrono::seconds(2));  // 더 긴 시간 이동
    publishVelocity(0, M_PI / 2);  // 90도 회전
    rclcpp::sleep_for(std::chrono::milliseconds(1000));
  }
  publishVelocity(0, 0);  // 멈춤
}
