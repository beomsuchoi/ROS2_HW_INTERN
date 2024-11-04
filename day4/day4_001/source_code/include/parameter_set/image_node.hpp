#ifndef PARAMETER_SET_IMAGE_NODE_HPP
#define PARAMETER_SET_IMAGE_NODE_HPP

#include <rclcpp/rclcpp.hpp>
#include <QThread>
#include <sensor_msgs/msg/image.hpp>
#include <cv_bridge/cv_bridge.h>
#include <QPixmap>
#include <QObject>
#include <opencv2/opencv.hpp>

class ImageNode : public QThread
{
    Q_OBJECT

public:
    ImageNode();
    ~ImageNode();

    void setParameter(const std::string &name, int value); // 파라미터 설정 함수 추가
    int getParameter(const std::string &name);

protected:
    void run();

private:
    void imageCallback(const sensor_msgs::msg::Image::SharedPtr msg);
    std::shared_ptr<rclcpp::Node> node;
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription_;

signals:
    void newImage(const QPixmap &original, const QPixmap &binary, const QPixmap &edges); // 원본 이미지와 이진 이미지를 전달
    void rosShutDown();
};

#endif // PARAMETER_SET_IMAGE_NODE_HPP
