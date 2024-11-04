#include "../include/parameter_set/main_window.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindowDesign)
{
  ui->setupUi(this);

  QIcon icon("://ros-icon.png");
  this->setWindowIcon(icon);

  qnode = new QNode();
  // ImageNode 초기화
  imageNode = new ImageNode();

  // ImageNode 종료 연결
  QObject::connect(imageNode, SIGNAL(rosShutDown()), this, SLOT(close()));

  // ImageNode로부터 새 이미지 수신 시 displayImage 호출
  // connect(imageNode, &ImageNode::newImage, this, &MainWindow::displayImage);
  connect(imageNode, &ImageNode::newImage, this, &MainWindow::displayImages);

  imageNode->start(); // ImageNode 시작

  ui->sliderHUpper->setValue(180);
  ui->spinHUpper->setValue(180);
  ui->sliderSUpper->setValue(255);
  ui->spinSUpper->setValue(255);
  ui->sliderVUpper->setValue(255);
  ui->spinVUpper->setValue(255);

  // Canny 초기화
  ui->sliderThreshold1->setValue(75);
  ui->sliderThreshold2->setValue(175);
  ui->spinThreshold1->setValue(75);
  ui->spinThreshold2->setValue(175);

  // Erode 및 Dilate 초기화
  ui->sliderErode->setValue(1);
  ui->spinErode->setValue(1);
  ui->sliderDilate->setValue(2);
  ui->spinDilate->setValue(2);

  // 이미지 크기
  ui->sliderWidth->setValue(displayWidth);
  ui->spinWidth->setValue(displayWidth);
  ui->sliderHeight->setValue(displayHeight);
  ui->spinHeight->setValue(displayHeight);

  // 슬라이더와 스핀박스 동기화 설정
  connect(ui->sliderHlower, &QSlider::valueChanged, ui->spinHLower, &QSpinBox::setValue);
  connect(ui->spinHLower, QOverload<int>::of(&QSpinBox::valueChanged), ui->sliderHlower, &QSlider::setValue);

  connect(ui->sliderHUpper, &QSlider::valueChanged, ui->spinHUpper, &QSpinBox::setValue);
  connect(ui->spinHUpper, QOverload<int>::of(&QSpinBox::valueChanged), ui->sliderHUpper, &QSlider::setValue);

  connect(ui->sliderSLower, &QSlider::valueChanged, ui->spinSLower, &QSpinBox::setValue);
  connect(ui->spinSLower, QOverload<int>::of(&QSpinBox::valueChanged), ui->sliderSLower, &QSlider::setValue);

  connect(ui->sliderSUpper, &QSlider::valueChanged, ui->spinSUpper, &QSpinBox::setValue);
  connect(ui->spinSUpper, QOverload<int>::of(&QSpinBox::valueChanged), ui->sliderSUpper, &QSlider::setValue);

  connect(ui->sliderVLower, &QSlider::valueChanged, ui->spinVLower, &QSpinBox::setValue);
  connect(ui->spinVLower, QOverload<int>::of(&QSpinBox::valueChanged), ui->sliderVLower, &QSlider::setValue);

  connect(ui->sliderVUpper, &QSlider::valueChanged, ui->spinVUpper, &QSpinBox::setValue);
  connect(ui->spinVUpper, QOverload<int>::of(&QSpinBox::valueChanged), ui->sliderVUpper, &QSlider::setValue);
  // ROI spinbox, slider
  connect(ui->sliderROIx_1, &QSlider::valueChanged, ui->spinROIx_1, &QSpinBox::setValue);
  connect(ui->spinROIx_1, QOverload<int>::of(&QSpinBox::valueChanged), ui->sliderROIx_1, &QSlider::setValue);

  connect(ui->sliderROIx_2, &QSlider::valueChanged, ui->spinROIx_2, &QSpinBox::setValue);
  connect(ui->spinROIx_2, QOverload<int>::of(&QSpinBox::valueChanged), ui->sliderROIx_2, &QSlider::setValue);

  connect(ui->sliderROIx_3, &QSlider::valueChanged, ui->spinROIx_3, &QSpinBox::setValue);
  connect(ui->spinROIx_3, QOverload<int>::of(&QSpinBox::valueChanged), ui->sliderROIx_3, &QSlider::setValue);

  connect(ui->sliderROIx_4, &QSlider::valueChanged, ui->spinROIx_4, &QSpinBox::setValue);
  connect(ui->spinROIx_4, QOverload<int>::of(&QSpinBox::valueChanged), ui->sliderROIx_4, &QSlider::setValue);

  connect(ui->sliderROIy_1, &QSlider::valueChanged, ui->spinROIy_1, &QSpinBox::setValue);
  connect(ui->spinROIy_1, QOverload<int>::of(&QSpinBox::valueChanged), ui->sliderROIy_1, &QSlider::setValue);

  connect(ui->sliderROIy_2, &QSlider::valueChanged, ui->spinROIy_2, &QSpinBox::setValue);
  connect(ui->spinROIy_2, QOverload<int>::of(&QSpinBox::valueChanged), ui->sliderROIy_2, &QSlider::setValue);

  connect(ui->sliderROIy_3, &QSlider::valueChanged, ui->spinROIy_3, &QSpinBox::setValue);
  connect(ui->spinROIy_3, QOverload<int>::of(&QSpinBox::valueChanged), ui->sliderROIy_3, &QSlider::setValue);

  connect(ui->sliderROIy_4, &QSlider::valueChanged, ui->spinROIy_4, &QSpinBox::setValue);
  connect(ui->spinROIy_4, QOverload<int>::of(&QSpinBox::valueChanged), ui->sliderROIy_4, &QSlider::setValue);
  // Erode 및 Dilate 동기화 추가
  connect(ui->sliderErode, &QSlider::valueChanged, ui->spinErode, &QSpinBox::setValue);
  connect(ui->spinErode, QOverload<int>::of(&QSpinBox::valueChanged), ui->sliderErode, &QSlider::setValue);

  connect(ui->sliderDilate, &QSlider::valueChanged, ui->spinDilate, &QSpinBox::setValue);
  connect(ui->spinDilate, QOverload<int>::of(&QSpinBox::valueChanged), ui->sliderDilate, &QSlider::setValue);


  connect(ui->sliderThreshold1, &QSlider::valueChanged, ui->spinThreshold1, &QSpinBox::setValue);
  connect(ui->spinThreshold1, QOverload<int>::of(&QSpinBox::valueChanged), ui->sliderThreshold1, &QSlider::setValue);

  connect(ui->sliderThreshold2, &QSlider::valueChanged, ui->spinThreshold2, &QSpinBox::setValue);
  connect(ui->spinThreshold2, QOverload<int>::of(&QSpinBox::valueChanged), ui->sliderThreshold2, &QSlider::setValue);

  connect(ui->sliderWidth, &QSlider::valueChanged, ui->spinWidth, &QSpinBox::setValue);
  connect(ui->spinWidth, QOverload<int>::of(&QSpinBox::valueChanged), ui->sliderWidth, &QSlider::setValue);

  connect(ui->sliderHeight, &QSlider::valueChanged, ui->spinHeight, &QSpinBox::setValue);
  connect(ui->spinHeight, QOverload<int>::of(&QSpinBox::valueChanged), ui->sliderHeight, &QSlider::setValue);

  connect(ui->sliderThreshold1, &QSlider::valueChanged, this, &MainWindow::updateParameterThreshold1);
  connect(ui->sliderThreshold2, &QSlider::valueChanged, this, &MainWindow::updateParameterThreshold2);
  connect(ui->sliderErode, &QSlider::valueChanged, this, &MainWindow::updateParameterErode);
  connect(ui->sliderDilate, &QSlider::valueChanged, this, &MainWindow::updateParameterDilate);
  connect(ui->sliderWidth, &QSlider::valueChanged, this, &MainWindow::updateParameterImageWidth);
  connect(ui->sliderHeight, &QSlider::valueChanged, this, &MainWindow::updateParameterImageHeight);
  // 파라미터 업데이트 연결
  connect(ui->sliderHlower, &QSlider::valueChanged, this, &MainWindow::updateParameterHLower);
  connect(ui->sliderHUpper, &QSlider::valueChanged, this, &MainWindow::updateParameterHUpper);
  connect(ui->sliderSLower, &QSlider::valueChanged, this, &MainWindow::updateParameterSLower);
  connect(ui->sliderSUpper, &QSlider::valueChanged, this, &MainWindow::updateParameterSUpper);
  connect(ui->sliderVLower, &QSlider::valueChanged, this, &MainWindow::updateParameterVLower);
  connect(ui->sliderVUpper, &QSlider::valueChanged, this, &MainWindow::updateParameterVUpper);

  connect(ui->sliderThreshold1, &QSlider::valueChanged, this, &MainWindow::updateParameterThreshold1);
  connect(ui->sliderThreshold2, &QSlider::valueChanged, this, &MainWindow::updateParameterThreshold2);
  connect(ui->sliderErode, &QSlider::valueChanged, this, &MainWindow::updateParameterErode);
  connect(ui->sliderDilate, &QSlider::valueChanged, this, &MainWindow::updateParameterDilate);

  // 슬라이더와 스핀박스 값 변경 시 이미지 크기 업데이트
  connect(ui->sliderWidth, &QSlider::valueChanged, this, [=](int value)
          { qnode->updateImageSize(value, ui->spinHeight->value()); });

  connect(ui->sliderHeight, &QSlider::valueChanged, this, [=](int value)
          { qnode->updateImageSize(ui->spinWidth->value(), value); });

  // QNode에서 파라미터 업데이트 신호가 발생했을 때 이미지 크기 업데이트
  connect(qnode, &QNode::parameterUpdated, this, [=](const std::string &name, int value)
          {
    if (name == "image_width" || name == "image_height") {
        ui->labelImageOriginal->setFixedSize(ui->sliderWidth->value(), ui->sliderHeight->value());
        ui->labelBinaryWhite->setFixedSize(ui->sliderWidth->value(), ui->sliderHeight->value());
        ui->labelImageFiltered->setFixedSize(ui->sliderWidth->value(), ui->sliderHeight->value());
    } }); // 람다 함수 닫힘 괄호와 connect 구문 닫힘 괄호 추가
}

void MainWindow::closeEvent(QCloseEvent *event)
{
  QMainWindow::closeEvent(event);
}

MainWindow::~MainWindow()
{

  delete imageNode;
  delete qnode;
  delete ui;
}

void MainWindow::updateDisplaySize()
{
  displayWidth = ui->spinWidth->value();
  displayHeight = ui->spinHeight->value();

  // 이미지를 표시하는 라벨의 크기 조정
  ui->labelImageOriginal->setFixedSize(displayWidth, displayHeight);
  ui->labelBinaryWhite->setFixedSize(displayWidth, displayHeight);

  qnode->setParameter("image_width", displayWidth);
  qnode->setParameter("image_height", displayHeight);

  qnode->updateImageSize(displayWidth, displayHeight);
}

// 이미지 표시 슬롯 구현
/*void MainWindow::displayImage(const QPixmap &original, const QPixmap &binary)
{
  int displayWidth = ui->labelImageOriginal->width();
  int displayHeight = ui->labelImageOriginal->height();

  if (!original.isNull())
  {
    QPixmap scaledOriginal = original.scaled(displayWidth, displayHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->labelImageOriginal->setPixmap(scaledOriginal);
    ui->labelImageOriginal->setAlignment(Qt::AlignCenter);
  }

  if (!binary.isNull())
  {
    QPixmap scaledBinary = binary.scaled(displayWidth, displayHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->labelBinaryWhite->setPixmap(scaledBinary);
    ui->labelBinaryWhite->setAlignment(Qt::AlignCenter);
  }
}*/

void MainWindow::displayImages(const QPixmap &original, const QPixmap &binary, const QPixmap &edges)
{
  ui->labelImageOriginal->setPixmap(original.scaled(ui->labelImageOriginal->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
  ui->labelBinaryWhite->setPixmap(binary.scaled(ui->labelBinaryWhite->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
  ui->labelImageFiltered->setPixmap(edges.scaled(ui->labelImageFiltered->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}
// 파라미터 업데이트 슬롯 함수들 (HSV)
void MainWindow::updateParameterHLower(int value)
{
  imageNode->setParameter("H_lower", value);
}
void MainWindow::updateParameterHUpper(int value)
{
  imageNode->setParameter("H_upper", value);
}
void MainWindow::updateParameterSLower(int value)
{
  imageNode->setParameter("S_lower", value);
}
void MainWindow::updateParameterSUpper(int value)
{
  imageNode->setParameter("S_upper", value);
}
void MainWindow::updateParameterVLower(int value)
{
  imageNode->setParameter("V_lower", value);
}
void MainWindow::updateParameterVUpper(int value)
{
  imageNode->setParameter("V_upper", value);
}

// 파라미터 업데이트 슬롯 함수들 (Canny, Erode, Dilate)
void MainWindow::updateParameterThreshold1(int value)
{
  imageNode->setParameter("Threshold1", value);
}
void MainWindow::updateParameterThreshold2(int value)
{
  imageNode->setParameter("Threshold2", value);
}
void MainWindow::updateParameterErode(int value)
{
  imageNode->setParameter("Erode", value);
}
void MainWindow::updateParameterDilate(int value)
{
  imageNode->setParameter("Dilate", value);
}

// Image Size 파라미터 업데이트 슬롯 함수들
void MainWindow::updateParameterImageWidth(int value)
{
  imageNode->setParameter("image_width", value);
}
void MainWindow::updateParameterImageHeight(int value)
{
  imageNode->setParameter("image_height", value);
}
