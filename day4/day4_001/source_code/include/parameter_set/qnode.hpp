#ifndef parameter_set_QNODE_HPP_
#define parameter_set_QNODE_HPP_

#include <rclcpp/rclcpp.hpp>
#include <QThread>
#include <string>  // std::string 사용을 위한 추가
class QNode : public QThread
{
  Q_OBJECT
public:
  QNode();
  ~QNode();

  std::shared_ptr<rclcpp::Node> get_node() const { return node; }

  void setParameter(const std::string &name, int value); // 파라미터 설정 함수
  int getParameter(const std::string &name); // 파라미터 가져오는 함수 추가
  void updateImageSize(int width, int height);

protected:
  void run();

private:
  std::shared_ptr<rclcpp::Node> node;

Q_SIGNALS:
  void rosShutDown();
  void parameterUpdated(const std::string &name, int value); // 파라미터 업데이트 시그널 추가
};

#endif /* parameter_set_QNODE_HPP_ */
