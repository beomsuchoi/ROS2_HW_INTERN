#include "main_window.hpp"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindowDesign), qnode(new QNode()) {
  ui->setupUi(this);

  qnode->lineColor(255, 0, 0);//기본 펜 색을 빨강으로 고정해서 처음 검정으로 나타나는 오류 해결

  // 버튼 클릭 연결 -> 함수 연결
  connect(ui->W, &QPushButton::clicked, this, &MainWindow::on_W_clicked); // 조종
  connect(ui->A, &QPushButton::clicked, this, &MainWindow::on_A_clicked);
  connect(ui->S, &QPushButton::clicked, this, &MainWindow::on_S_clicked);
  connect(ui->D, &QPushButton::clicked, this, &MainWindow::on_D_clicked);

  connect(ui->background_r, &QPushButton::clicked, this, &MainWindow::BackgroundColorRed);
  connect(ui->background_g, &QPushButton::clicked, this, &MainWindow::BackgroundColorGreen);
  connect(ui->background_b, &QPushButton::clicked, this, &MainWindow::BackgroundColorBlue);

  connect(ui->line_r, &QPushButton::clicked, this, &MainWindow::lineColorRed);
  connect(ui->line_g, &QPushButton::clicked, this, &MainWindow::lineColorGreen);
  connect(ui->line_b, &QPushButton::clicked, this, &MainWindow::lineColorBlue);

  connect(ui->width_line, &QSlider::valueChanged, this, &MainWindow::changeLineWidth);

  connect(qnode, &QNode::cmdVelPublished, this, &MainWindow::displayCmdVel); // GUI 출력

  connect(ui->shape1, &QPushButton::clicked, this, &MainWindow::drawCircle);
  connect(ui->shape2, &QPushButton::clicked, this, &MainWindow::drawTriangle);
  connect(ui->shape3, &QPushButton::clicked, this, &MainWindow::drawSquare);

  connect(ui->size_shape, &QSlider::valueChanged, this, &MainWindow::changeShapeSize);

}

MainWindow::~MainWindow() {
  delete ui;
  delete qnode;
}

void MainWindow::changeLineWidth(int width) {
  qnode->PenWidth(width);  // QNode의 펜 두께 함수 호출
}

void MainWindow::closeEvent(QCloseEvent* event) {
  QMainWindow::closeEvent(event);
}

void MainWindow::on_W_clicked() {
  qnode->publishVelocity(1.0, 0.0);  // 앞으로 이동
}

void MainWindow::on_S_clicked() {
  qnode->publishVelocity(-1.0, 0.0);  // 뒤로 이동
}

void MainWindow::on_A_clicked() {
  qnode->publishVelocity(0.0, 1.0);  // 왼쪽 회전
}

void MainWindow::on_D_clicked() {
  qnode->publishVelocity(0.0, -1.0);  // 오른쪽 회전
}

// 배경색 변경 함수들
void MainWindow::BackgroundColorRed() {
  qnode->backgroundColor(255, 0, 0);  // 빨강
}

void MainWindow::BackgroundColorGreen() {
  qnode->backgroundColor(0, 255, 0);  // 초록
}

void MainWindow::BackgroundColorBlue() {
  qnode->backgroundColor(0, 0, 255);  // 파랑
}

void MainWindow::lineColorRed() {
  qnode->lineColor(255, 0, 0);  // 빨강
}

void MainWindow::lineColorGreen() {
  qnode->lineColor(0, 255, 0);  // 초록
}

void MainWindow::lineColorBlue() {
  qnode->lineColor(0, 0, 255);  // 파랑
}

void MainWindow::displayCmdVel(QString data) {
  ui->text->append(data); // "text"에 데이터 추가
}

void MainWindow::drawCircle() {
  int shape_size = ui->size_shape->value();  // QSlider에서 가져온 크기 값
  double speed = 1;  // 원을 그릴 속도 설정

  qnode->drawCircle(shape_size*0.2, speed);  // 현재 크기와 속도로 원 그리기
}

void MainWindow::drawTriangle() {
  
  qnode->drawTriangle(shape_size*3);  // 현재 크기로 정삼각형 그리기
}

void MainWindow::drawSquare() {
  
  qnode->drawSquare(shape_size*3);  // 현재 크기로 정사각형 그리기
}

void MainWindow::changeShapeSize(int size) {
  shape_size = size;  // 슬라이더 값으로 크기 설정
}