#ifndef image_print_QNODE_HPP_
#define image_print_QNODE_HPP_

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <QThread>
#include <QPixmap>

class QNode : public QThread
{
  Q_OBJECT
public:
  QNode();
  ~QNode();

protected:
  void run();

private:
  std::shared_ptr<rclcpp::Node> node;
  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription_;

  void imageCallback(const sensor_msgs::msg::Image::SharedPtr msg);

Q_SIGNALS:
  void rosShutDown();
  void newImage(const QPixmap& pixmap);  // 새로운 이미지 수신 신호
};

#endif /* image_print_QNODE_HPP_ */
