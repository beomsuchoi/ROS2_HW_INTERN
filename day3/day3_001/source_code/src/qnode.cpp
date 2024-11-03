#include "../include/image_print/qnode.hpp"

QNode::QNode()
{
  int argc = 0;
  char** argv = NULL;
  rclcpp::init(argc, argv);
  node = rclcpp::Node::make_shared("image_print");

  // 이미지 구독 설정
  subscription_ = node->create_subscription<sensor_msgs::msg::Image>(
    "/camera1/camera/image_raw", 10, std::bind(&QNode::imageCallback, this, std::placeholders::_1));

  this->start();
}

QNode::~QNode()
{
  if (rclcpp::ok())
  {
    rclcpp::shutdown();
  }
}

void QNode::run()
{
  rclcpp::WallRate loop_rate(20);
  while (rclcpp::ok())
  {
    rclcpp::spin_some(node);
    loop_rate.sleep();//20으로 계속
  }
  rclcpp::shutdown();
  Q_EMIT rosShutDown();//shutdown 신호
}

void QNode::imageCallback(const sensor_msgs::msg::Image::SharedPtr msg)
{
  try
  {
    // ROS 이미지 메시지를 OpenCV 이미지로 변환
    cv::Mat cv_image = cv_bridge::toCvCopy(msg, "bgr8")->image;

    // OpenCV 이미지를 QImage로 변환
    QImage qimage(cv_image.data, cv_image.cols, cv_image.rows, cv_image.step, QImage::Format_RGB888);
    QPixmap pixmap = QPixmap::fromImage(qimage.rgbSwapped());  // RGB 형식 변경

    // newImage 신호로 MainWindow에 pixmap 전달
    Q_EMIT newImage(pixmap);
  }
  catch (cv_bridge::Exception& e)
  {
    RCLCPP_ERROR(node->get_logger(), "Error converting image: %s", e.what());
  }
}
