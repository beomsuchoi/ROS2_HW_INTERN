#include "../include/image_print/main_window.hpp"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindowDesign)
{
  ui->setupUi(this);

  QIcon icon("://ros-icon.png");
  this->setWindowIcon(icon);

  qnode = new QNode();

  QObject::connect(qnode, &QNode::rosShutDown, this, &MainWindow::close);
  QObject::connect(qnode, &QNode::newImage, this, &MainWindow::updateImage);  // 이미지 업데이트 연결
}

void MainWindow::updateImage(const QPixmap& pixmap)
{
  ui->label->setPixmap(pixmap.scaled(640, 480, Qt::KeepAspectRatio));  // QLabel에 이미지 설정
}

void MainWindow::closeEvent(QCloseEvent* event)
{
  QMainWindow::closeEvent(event);
}

MainWindow::~MainWindow()
{
  delete ui;
}
