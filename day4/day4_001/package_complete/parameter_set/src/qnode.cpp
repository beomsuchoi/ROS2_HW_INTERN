#include "../include/parameter_set/qnode.hpp"

QNode::QNode()
{
    int argc = 0;
    char** argv = NULL;

    // ROS가 이미 초기화된 경우 init을 건너뜁니다.
    if (!rclcpp::ok()) {
        rclcpp::init(argc, argv);
    }
    
    node = rclcpp::Node::make_shared("parameter_set");

    RCLCPP_INFO(node->get_logger(), "QNode started.");

    // HSV, ROI, Canny, Erode, Dilate, Image Size 파라미터 선언 (기존 코드 유지)
    node->declare_parameter("H_lower", 0);
    node->declare_parameter("H_upper", 180);
    node->declare_parameter("S_lower", 0);
    node->declare_parameter("S_upper", 255);
    node->declare_parameter("V_lower", 0);
    node->declare_parameter("V_upper", 255);
    node->declare_parameter("ROI_x", 0);
    node->declare_parameter("ROI_y", 0);
    node->declare_parameter("ROI_width", 640);
    node->declare_parameter("ROI_height", 480);
    node->declare_parameter("Threshold1", 0);
    node->declare_parameter("Threshold2", 0);
    node->declare_parameter("Erode", 0);
    node->declare_parameter("Dilate", 0);
    node->declare_parameter("image_width", 640);
    node->declare_parameter("image_height", 480);

    this->start();
}

QNode::~QNode()
{
    RCLCPP_INFO(node->get_logger(), "QNode is shutting down.");
    if (rclcpp::ok()) {
        rclcpp::shutdown();
    }
}

void QNode::run()
{
    rclcpp::WallRate loop_rate(20);
    while (rclcpp::ok()) {
        // 예시: 주기적으로 H_lower 파라미터 값을 읽고 GUI로 전달
        int h_lower = getParameter("H_lower");
        Q_EMIT parameterUpdated("H_lower", h_lower);

        rclcpp::spin_some(node);
        loop_rate.sleep();
    }
    rclcpp::shutdown();
    Q_EMIT rosShutDown();
}

void QNode::setParameter(const std::string &name, int value)
{
    node->set_parameter(rclcpp::Parameter(name, value));
    Q_EMIT parameterUpdated(name, value); // 파라미터 업데이트 시그널 전송
}

int QNode::getParameter(const std::string &name)
{
    int value;
    if (node->get_parameter(name, value)) {
        return value;
    } else {
        RCLCPP_WARN(node->get_logger(), "Parameter %s not found, returning 0 as default.", name.c_str());
        return 0; // 기본값 반환
    }
}

void QNode::updateImageSize(int width, int height)
{
    setParameter("image_width", width);
    setParameter("image_height", height);
}