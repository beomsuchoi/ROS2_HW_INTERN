#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "turtlesim/srv/set_pen.hpp"
#include "turtlesim/srv/spawn.hpp"
#include <termios.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <cctype>

// 키보드 입력을 위한 함수
char getKey() {
  struct termios oldt, newt;
  char ch;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  ch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  return ch;
}

class TeleopTurtle : public rclcpp::Node {
public:
  TeleopTurtle() : Node("teleop_turtle") {
    publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel", 10);
    set_pen_client_ = this->create_client<turtlesim::srv::SetPen>("turtle1/set_pen");
    spawn_client_ = this->create_client<turtlesim::srv::Spawn>("/spawn");
    this->declare_parameter("background_r", 255);
    this->declare_parameter("background_g", 255);
    this->declare_parameter("background_b", 255);
    std::cout << "Select Mode: 1 for WASD control, 2 for Background color settings, 3 for Pen settings, 4 for Turtle type selection." << std::endl;
  }

  void keyLoop() {
    char c;
    int mode = 0;
    geometry_msgs::msg::Twist msg;
    uint8_t pen_r = 255, pen_g = 255, pen_b = 255;
    uint8_t pen_width = 1;
    uint8_t bg_r = 255, bg_g = 255, bg_b = 255;

    while (rclcpp::ok()) {
      c = getKey();
      if (mode == 0) {
        if (c == '1') {
          mode = 1;
          std::cout << "WASD control mode Press Q to quit." << std::endl;
        } else if (c == '2') {
          mode = 2;
          std::cout << "Background color settings mode. Press Q to quit." << std::endl;
          std::cout << "Use R/G/B to change background." << std::endl;
        } else if (c == '3') {
          mode = 3;
          std::cout << "Pen settings mode activated. Press Q to quit." << std::endl;
          std::cout << "Use R/G/B to change color, and 1-9 to set pen." << std::endl;
        } else if (c == '4') {
          mode = 4;
          std::cout << "Turtle type selection mode. Press Q to quit." << std::endl;
          std::cout << "Select Turtle type" << std::endl;
        }
      } else if (mode == 1) {
        switch (c) {
          case 'w':
            msg.linear.x = 1.0;
            msg.angular.z = 0.0;
            break;
          case 's':
            msg.linear.x = -1.0;
            msg.angular.z = 0.0;
            break;
          case 'a':
            msg.linear.x = 0.0;
            msg.angular.z = 1.0;
            break;
          case 'd':
            msg.linear.x = 0.0;
            msg.angular.z = -1.0;
            break;
          case 'q':
            mode = 0;
            std::cout << "OUT WASD control mode." << std::endl;
            continue;
          default:
            msg.linear.x = 0.0;
            msg.angular.z = 0.0;
        }
        publisher_->publish(msg);
      } else if (mode == 2) {
        switch (c) {
          case 'r':
            bg_r = 148;
            setBackgroundColor("background_r", bg_r);
            std::cout << "Background color red." << std::endl;
            break;
          case 'g':
            bg_g = 148;
            setBackgroundColor("background_g", bg_g);
            std::cout << "Background color green." << std::endl;
            break;
          case 'b':
            bg_b = 148;
            setBackgroundColor("background_b", bg_b);
            std::cout << "Background color blue." << std::endl;
            break;
          case 'q':
            mode = 0;
            std::cout << "OUT Background color settings mode." << std::endl;
            continue;
          default:
            std::cout << "Invalid command in Background color settings mode." << std::endl;
            continue;
        }
      } else if (mode == 3) {
        if (isdigit(c) && c >= '1' && c <= '9') {
          pen_width = c - '0';
          std::cout << "Pen width set : " << static_cast<int>(pen_width) << std::endl;
        } else {
          switch (c) {
            case 'r':
              pen_r = 255;
              pen_g = 0;
              pen_b = 0;
              std::cout << "Pen color red." << std::endl;
              changePenSettings(pen_r, pen_g, pen_b, pen_width);
              mode = 0;
              std::cout << "OUT Pen settings mode. Other mode." << std::endl;
              break;
            case 'g':
              pen_g = (pen_g == 255) ? 0 : 255;
              std::cout << "Green value set to: " << static_cast<int>(pen_g) << std::endl;
              break;
            case 'b':
              pen_b = (pen_b == 255) ? 0 : 255;
              std::cout << "Blue value set to: " << static_cast<int>(pen_b) << std::endl;
              break;
            case 'q':
              mode = 0;
              std::cout << "OUT Pen settings mode." << std::endl;
              continue;
            default:
              std::cout << "Invalid command in Pen settings mode." << std::endl;
              continue;
          }
        }
        changePenSettings(pen_r, pen_g, pen_b, pen_width);
      } else if (mode == 4) {
        switch (c) {
          case '1':
            spawnTurtle(5.5, 5.5, 0.0, "classic");
            std::cout << "Turtle type Classic." << std::endl;
            break;
          case '2':
            spawnTurtle(5.5, 5.5, 0.0, "speedy");
            std::cout << "Turtle type Speedy." << std::endl;
            break;
          case '3':
            spawnTurtle(5.5, 5.5, 0.0, "ninja");
            std::cout << "Turtle type Ninja." << std::endl;
            break;
          case '4':
            spawnTurtle(5.5, 5.5, 0.0, "elder");
            std::cout << "Turtle type Elder." << std::endl;
            break;
          case 'q':
            mode = 0;
            std::cout << "OUT Turtle type selection mode." << std::endl;
            continue;
          default:
            std::cout << "Invalid command in Turtle type selection mode." << std::endl;
            continue;
        }
        mode = 0;
        std::cout << "OUT Turtle type selection mode." << std::endl;
      }
    }
  }

private:
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
  rclcpp::Client<turtlesim::srv::SetPen>::SharedPtr set_pen_client_;
  rclcpp::Client<turtlesim::srv::Spawn>::SharedPtr spawn_client_;

  void changePenSettings(uint8_t r, uint8_t g, uint8_t b, uint8_t width) {
    if (!set_pen_client_->wait_for_service(std::chrono::seconds(1))) {
      RCLCPP_WARN(this->get_logger(), "Waiting set_pen ");
      return;
    }

    auto request = std::make_shared<turtlesim::srv::SetPen::Request>();
    request->r = r;
    request->g = g;
    request->b = b;
    request->width = width;
    request->off = 0;

    auto future = set_pen_client_->async_send_request(request);
    try {
      auto response = future.get();
    } catch (const std::exception &e) {
      RCLCPP_ERROR(this->get_logger(), "Service call failed: %s", e.what());
    }
  }

  void setBackgroundColor(const std::string &param_name, uint8_t value) {
    if (!this->has_parameter(param_name)) {
      RCLCPP_WARN(this->get_logger(), "Parameter %s not declared.", param_name.c_str());
      return;
    }
    this->set_parameter(rclcpp::Parameter(param_name, value));
  }

  void spawnTurtle(float x, float y, float theta, const std::string &name) {
    if (!spawn_client_->wait_for_service(std::chrono::seconds(1))) {
      RCLCPP_WARN(this->get_logger(), "Waiting spawn");
      return;
    }

    auto request = std::make_shared<turtlesim::srv::Spawn::Request>();
    request->x = x;
    request->y = y;
    request->theta = theta;
    request->name = name;

    auto future = spawn_client_->async_send_request(request);
    try {
      auto response = future.get();
      RCLCPP_INFO(this->get_logger(), "Spawned turtle: %s", response->name.c_str());
    } catch (const std::exception &e) {
      RCLCPP_ERROR(this->get_logger(), "Service call failed: %s", e.what());
    }
  }
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<TeleopTurtle>();

  rclcpp::Rate rate(10); // 10 Hz loop rate
  while (rclcpp::ok()) {
    node->keyLoop();
    rclcpp::spin_some(node);
    rate.sleep();
  }

  rclcpp::shutdown();
  return 0;
}

