#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include "qnode.hpp"
#include "ui_mainwindow.h"

namespace Ui {
class MainWindowDesign;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

private slots:
  void on_W_clicked();
  void on_S_clicked();
  void on_A_clicked();
  void on_D_clicked();
  void displayCmdVel(QString data);

  void BackgroundColorRed();
  void BackgroundColorGreen();
  void BackgroundColorBlue();

  void lineColorRed();    // 빨강
  void lineColorGreen();  // 초록
  void lineColorBlue();   // 파랑

  void changeLineWidth(int width);

  void drawCircle();     // 원 그리기 함수
  void drawTriangle();   // 정삼각형 그리기 함수
  void drawSquare();     // 정사각형 그리기 함수
  void changeShapeSize(int size); // 슬라이더를 통한 크기 조정 함수


private:
  Ui::MainWindowDesign* ui;
  QNode* qnode;
  void closeEvent(QCloseEvent* event);

  int shape_size = 10;
  
};

#endif  // MAIN_WINDOW_H
