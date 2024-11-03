// include/turtlesim_draw/turtlesim_draw.hpp

#ifndef TURTLESIM_DRAW_HPP
#define TURTLESIM_DRAW_HPP

#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <turtlesim/srv/set_pen.hpp>  
//#include <turtlesim/srv/teleport_absolute.hpp>  

namespace turtlesim_draw
{
    class TurtlesimDraw : public rclcpp::Node
    {
    public:
        TurtlesimDraw();
        void drawCircle(double radius, double speed);
        void drawTriangle(int side_length);
        void drawSquare(int side_length);
        void setPen(const std::string &color, int width); // setPen 함수 추가
        void publishVelocity(double linear, double angular);

    private:
        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr velocity_publisher_;
        rclcpp::Client<turtlesim::srv::SetPen>::SharedPtr pen_client_;
        //rclcpp::Client<turtlesim::srv::TeleportAbsolute>::SharedPtr teleport_client_;
    };
}

#endif // TURTLESIM_DRAW_HPP
