// src/main.cpp

#include "turtlesim_draw/turtlesim_draw.hpp"
#include <rclcpp/rclcpp.hpp>
#include <iostream>

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<turtlesim_draw::TurtlesimDraw>();

    while (rclcpp::ok())
    {
        std::string shape;
        int size;
        std::string color;
        int width;
        char choice;

        std::cout << "그릴 도형을 선택하세요 (triangle, circle, square): ";
        std::cin >> shape;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "도형의 크기를 입력하세요 (변 길이 또는 지름): ";
        std::cin >> size;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "펜 색상을 선택하세요 (예: red, blue, green): ";
        std::cin >> color;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "펜의 굵기를 입력하세요: ";
        std::cin >> width;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        node->setPen(color, width);

        if (shape == "circle")
        {
            node->drawCircle(size / 2.0, 1.0);  // 반지름과 속도 설정
        }
        else if (shape == "triangle")
        {
            node->drawTriangle(size * 2);
        }
        else if (shape == "square")
        {
            node->drawSquare(size * 2);
        }
        else
        {
            std::cout << "알 수 없는 도형입니다." << std::endl;
        }

        std::cout << "계속해서 다른 도형을 그리시겠습니까? (y/n): ";
        std::cin >> choice;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 'n')
        {
            break;
        }
    }

    rclcpp::shutdown();
    return 0;
}
