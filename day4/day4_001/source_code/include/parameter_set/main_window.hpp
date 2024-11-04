#ifndef parameter_set_MAIN_WINDOW_H
#define parameter_set_MAIN_WINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QLabel>
#include "qnode.hpp"
#include "image_node.hpp" // QNode 대신 image_node 사용
#include "ui_mainwindow.h"
#include <thread>

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  QNode *qnode;
  ImageNode *imageNode; // QNode 대신 ImageNode 사용

public slots:
  // 이미지 표시 슬롯
  void displayImages(const QPixmap &original, const QPixmap &binary, const QPixmap &edges);
  void updateDisplaySize();

  // HSV 파라미터 업데이트 슬롯
  void updateParameterHLower(int value);
  void updateParameterHUpper(int value);
  void updateParameterSLower(int value);
  void updateParameterSUpper(int value);
  void updateParameterVLower(int value);
  void updateParameterVUpper(int value);

  // Canny, Erode, Dilate 파라미터 업데이트 슬롯
  void updateParameterThreshold1(int value);
  void updateParameterThreshold2(int value);
  void updateParameterErode(int value);
  void updateParameterDilate(int value);

  // 이미지 크기 파라미터 업데이트 슬롯
  void updateParameterImageWidth(int value);
  void updateParameterImageHeight(int value);

private:
  Ui::MainWindowDesign *ui;
  QLabel *labelImageOriginal; // 이미지를 표시할 QLabel
  int displayWidth = 640;
  int displayHeight = 480;
  void closeEvent(QCloseEvent *event);
};

#endif // parameter_set_MAIN_WINDOW_H
