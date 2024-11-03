// src/turtlesim_draw.cpp

#include "turtlesim_draw/turtlesim_draw.hpp"
#include <iostream>
#include <chrono>
#include <cmath>
#include <thread>

using namespace std::chrono_literals;
using turtlesim_draw::TurtlesimDraw;

TurtlesimDraw::TurtlesimDraw()
    : Node("turtlesim_draw")
{
    pen_client_ = this->create_client<turtlesim::srv::SetPen>("/turtle1/set_pen");
    //teleport_client_ = this->create_client<turtlesim::srv::TeleportAbsolute>("/turtle1/teleport_absolute");
    velocity_publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);

    /*while (!pen_client_->wait_for_service(1s) || !teleport_client_->wait_for_service(1s))
    {
        RCLCPP_INFO(this->get_logger(), "서비스 대기 중...");
    }*/
}   

void TurtlesimDraw::setPen(const std::string &color, int width)
{
    auto request = std::make_shared<turtlesim::srv::SetPen::Request>();

    // 색상 설정
    if (color == "red") { request->r = 255; request->g = 0; request->b = 0; }
    else if (color == "blue") { request->r = 0; request->g = 0; request->b = 255; }
    else if (color == "green") { request->r = 0; request->g = 255; request->b = 0; }
    else { request->r = 0; request->g = 0; request->b = 0; }  // 기본 검정색

    // 두꼐 설정
    request->width = width;

    // SetPen 서비스 호출
    auto result = pen_client_->async_send_request(request);
    if (rclcpp::spin_until_future_complete(this->get_node_base_interface(), result) != rclcpp::FutureReturnCode::SUCCESS)
    {
        RCLCPP_ERROR(this->get_logger(), "펜 설정 실패");
    }
}

void TurtlesimDraw::publishVelocity(double linear, double angular)
{
    auto msg = geometry_msgs::msg::Twist();
    msg.linear.x = linear;
    msg.angular.z = angular;
    velocity_publisher_->publish(msg);
}

void TurtlesimDraw::drawCircle(double radius, double speed)
{
    std::thread([this, radius, speed]() {
        double circumference = 2 * M_PI * radius;
        double duration = circumference / speed;
        double travel_time = duration / 24;

        for (int i = 0; i < 26; i++)
        {
            publishVelocity(speed, speed / radius);
            rclcpp::sleep_for(std::chrono::milliseconds(static_cast<int>(travel_time * 1000)));
        }
        publishVelocity(0, 0);  // 멈춤
    }).detach();
}

void TurtlesimDraw::drawTriangle(int side_length)
{
    const double speed_factor = 0.1;
    for (int i = 0; i < 3; ++i)
    {
        publishVelocity(side_length * speed_factor, 0.0);
        rclcpp::sleep_for(std::chrono::seconds(2));
        publishVelocity(0, 2 * M_PI / 3);  // 120도 회전
        rclcpp::sleep_for(std::chrono::milliseconds(1000));
    }
    publishVelocity(0, 0);  // 멈춤
}

void TurtlesimDraw::drawSquare(int side_length)
{
    const double speed_factor = 0.1;
    for (int i = 0; i < 4; ++i)
    {
        publishVelocity(side_length * speed_factor, 0.0);
        rclcpp::sleep_for(std::chrono::seconds(2));
        publishVelocity(0, M_PI / 2);  // 90도 회전
        rclcpp::sleep_for(std::chrono::milliseconds(1000));
    }
    publishVelocity(0, 0);  // 멈춤
}
