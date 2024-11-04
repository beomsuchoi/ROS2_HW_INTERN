#include "image_node.hpp"

ImageNode::ImageNode()
{
    int argc = 0;
    char **argv = NULL;

    if (!rclcpp::ok())
    {
        rclcpp::init(argc, argv);
    }

    node = rclcpp::Node::make_shared("image_node");

    // 파라미터 선언
    node->declare_parameter("H_lower", 0);
    node->declare_parameter("H_upper", 180);
    node->declare_parameter("S_lower", 0);
    node->declare_parameter("S_upper", 255);
    node->declare_parameter("V_lower", 0);
    node->declare_parameter("V_upper", 255);
    node->declare_parameter("Threshold1", 75);
    node->declare_parameter("Threshold2", 175);
    node->declare_parameter("Erode", 1);
    node->declare_parameter("Dilate", 2);
    node->declare_parameter("image_width", 640);
    node->declare_parameter("image_height", 480);

    // 이미지 구독 설정
    subscription_ = node->create_subscription<sensor_msgs::msg::Image>(
        "/camera1/camera/image_raw", 10, std::bind(&ImageNode::imageCallback, this, std::placeholders::_1));

    this->start();
}

ImageNode::~ImageNode()
{
    if (rclcpp::ok())
    {
        rclcpp::shutdown();
    }
}

void ImageNode::setParameter(const std::string &name, int value)
{
    node->set_parameter(rclcpp::Parameter(name, value));
}

void ImageNode::run()
{
    rclcpp::WallRate loop_rate(20);
    while (rclcpp::ok())
    {
        rclcpp::spin_some(node);
        loop_rate.sleep();
    }
    Q_EMIT rosShutDown();
}


// image_node.cpp
void ImageNode::imageCallback(const sensor_msgs::msg::Image::SharedPtr msg)
{
    try
    {
        cv::Mat cv_image = cv_bridge::toCvCopy(msg, "bgr8")->image;

        // H, S, V 값 읽기
        int h_lower = getParameter("H_lower");
        int h_upper = getParameter("H_upper");
        int s_lower = getParameter("S_lower");
        int s_upper = getParameter("S_upper");
        int v_lower = getParameter("V_lower");
        int v_upper = getParameter("V_upper");

        int erode_iter = getParameter("Erode");
        int dilate_iter = getParameter("Dilate");

        int threshold1 = getParameter("Threshold1");
        int threshold2 = getParameter("Threshold2");
        // 이미지 HSV 변환
        cv::Mat hsv_image;
        cv::cvtColor(cv_image, hsv_image, cv::COLOR_BGR2HSV);

        // 이진화 마스크 생성
        cv::Mat mask;
        cv::inRange(hsv_image, cv::Scalar(h_lower, s_lower, v_lower), cv::Scalar(h_upper, s_upper, v_upper), mask);


        if (erode_iter > 0)
        {
            cv::erode(mask, mask, cv::Mat(), cv::Point(-1, -1), erode_iter);
        }
        if (dilate_iter > 0)
        {
            cv::dilate(mask, mask, cv::Mat(), cv::Point(-1, -1), dilate_iter);
        }
        // 마스크를 이용해 이진 이미지를 만듭니다.
        cv::Mat binary_image;
        cv::bitwise_and(cv_image, cv_image, binary_image, mask);

        cv::Mat edges;
        cv::Canny(binary_image, edges, threshold1, threshold2);

        // OpenCV 이미지를 QImage로 변환
        QImage qimage(cv_image.data, cv_image.cols, cv_image.rows, cv_image.step, QImage::Format_RGB888);
        QPixmap pixmap_original = QPixmap::fromImage(qimage.rgbSwapped());

        QImage qimage_binary(binary_image.data, binary_image.cols, binary_image.rows, binary_image.step, QImage::Format_RGB888);
        QPixmap pixmap_binary = QPixmap::fromImage(qimage_binary.rgbSwapped());

        QImage qimage_edges(edges.data, edges.cols, edges.rows, edges.step, QImage::Format_Grayscale8);
        QPixmap pixmap_edges = QPixmap::fromImage(qimage_edges);
        // 이미지 크기 파라미터 읽기
        int targetWidth = getParameter("image_width");
        int targetHeight = getParameter("image_height");

        // 비율을 유지하면서 크기 조정
        QPixmap resized_original = pixmap_original.scaled(targetWidth, targetHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QPixmap resized_binary = pixmap_binary.scaled(targetWidth, targetHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QPixmap resized_edges = pixmap_edges.scaled(targetWidth, targetHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);

        // 원본 이미지와 이진 이미지를 GUI로 전송
        Q_EMIT newImage(resized_original, resized_binary, resized_edges); // 변환한 원본 이미지와 이진 이미지 전송
        RCLCPP_INFO(node->get_logger(), "Image received and processed.");
    }
    catch (cv_bridge::Exception &e)
    {
        RCLCPP_ERROR(node->get_logger(), "Error converting image: %s", e.what());
    }
}

// image_node.cpp


int ImageNode::getParameter(const std::string &name)
{
    int value;
    if (node->get_parameter(name, value))
    {
        return value;
    }
    else
    {
        RCLCPP_WARN(node->get_logger(), "Parameter %s not found, returning 0 as default.", name.c_str());
        return 0; // 기본값 반환
    }
}