/**
 * @file /include/talker_listener/main_window.hpp
 *
 * @brief Qt based GUI for the talker_listener package.
 *
 * @date August 2024
 **/

#ifndef TALKER_LISTENER_MAIN_WINDOW_H
#define TALKER_LISTENER_MAIN_WINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include "talker.hpp"       // talker 노드 포함
#include "listener.hpp"     // listener 노드 포함
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  std::shared_ptr<Talker> talker_node;     // talker 노드 객체
  std::shared_ptr<Listener> listener_node; // listener 노드 객체
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

private slots:
  void on_publish_clicked();  // 퍼블리시 버튼 클릭 시 호출되는 슬롯 함수
  void displayMessage(const QString &message);

private:
  Ui::MainWindowDesign* ui;

  QLineEdit* messageInput;        // 메시지 입력 필드
  QLabel* receivedMessageLabel;   // 수신 메시지 표시 라벨

  void closeEvent(QCloseEvent* event);  // 창 닫기 이벤트
};

#endif  // TALKER_LISTENER_MAIN_WINDOW_H
