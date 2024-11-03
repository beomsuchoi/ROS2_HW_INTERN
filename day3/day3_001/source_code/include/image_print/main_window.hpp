#ifndef image_print_MAIN_WINDOW_H
#define image_print_MAIN_WINDOW_H

#include <QMainWindow>
#include "QIcon"
#include "qnode.hpp"
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

private:
  Ui::MainWindowDesign* ui;
  QNode* qnode;
  void closeEvent(QCloseEvent* event);

public Q_SLOTS:
  void updateImage(const QPixmap& pixmap);  // 이미지 업데이트 슬롯
};

#endif  // image_print_MAIN_WINDOW_H
