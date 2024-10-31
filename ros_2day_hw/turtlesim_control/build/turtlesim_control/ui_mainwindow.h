/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowDesign
{
public:
    QAction *action_Quit;
    QAction *action_Preferences;
    QAction *actionAbout;
    QAction *actionAbout_Qt;
    QWidget *centralwidget;
    QPushButton *W;
    QPushButton *S;
    QPushButton *A;
    QPushButton *D;
    QPushButton *background_r;
    QPushButton *background_g;
    QPushButton *background_b;
    QPushButton *line_r;
    QPushButton *line_g;
    QPushButton *line_b;
    QPushButton *shape1;
    QPushButton *shape2;
    QPushButton *shape3;
    QTextBrowser *text;
    QSlider *width_line;
    QSlider *size_shape;

    void setupUi(QMainWindow *MainWindowDesign)
    {
        if (MainWindowDesign->objectName().isEmpty())
            MainWindowDesign->setObjectName(QString::fromUtf8("MainWindowDesign"));
        MainWindowDesign->resize(930, 700);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindowDesign->setWindowIcon(icon);
        MainWindowDesign->setLocale(QLocale(QLocale::English, QLocale::Australia));
        action_Quit = new QAction(MainWindowDesign);
        action_Quit->setObjectName(QString::fromUtf8("action_Quit"));
        action_Quit->setShortcutContext(Qt::ApplicationShortcut);
        action_Preferences = new QAction(MainWindowDesign);
        action_Preferences->setObjectName(QString::fromUtf8("action_Preferences"));
        actionAbout = new QAction(MainWindowDesign);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionAbout_Qt = new QAction(MainWindowDesign);
        actionAbout_Qt->setObjectName(QString::fromUtf8("actionAbout_Qt"));
        centralwidget = new QWidget(MainWindowDesign);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        W = new QPushButton(centralwidget);
        W->setObjectName(QString::fromUtf8("W"));
        W->setGeometry(QRect(170, 440, 71, 71));
        S = new QPushButton(centralwidget);
        S->setObjectName(QString::fromUtf8("S"));
        S->setGeometry(QRect(170, 530, 71, 71));
        A = new QPushButton(centralwidget);
        A->setObjectName(QString::fromUtf8("A"));
        A->setGeometry(QRect(80, 530, 71, 71));
        D = new QPushButton(centralwidget);
        D->setObjectName(QString::fromUtf8("D"));
        D->setGeometry(QRect(260, 530, 71, 71));
        background_r = new QPushButton(centralwidget);
        background_r->setObjectName(QString::fromUtf8("background_r"));
        background_r->setGeometry(QRect(468, 390, 101, 25));
        background_g = new QPushButton(centralwidget);
        background_g->setObjectName(QString::fromUtf8("background_g"));
        background_g->setGeometry(QRect(590, 390, 101, 25));
        background_b = new QPushButton(centralwidget);
        background_b->setObjectName(QString::fromUtf8("background_b"));
        background_b->setGeometry(QRect(710, 390, 101, 25));
        line_r = new QPushButton(centralwidget);
        line_r->setObjectName(QString::fromUtf8("line_r"));
        line_r->setGeometry(QRect(468, 490, 101, 25));
        line_g = new QPushButton(centralwidget);
        line_g->setObjectName(QString::fromUtf8("line_g"));
        line_g->setGeometry(QRect(590, 490, 101, 25));
        line_b = new QPushButton(centralwidget);
        line_b->setObjectName(QString::fromUtf8("line_b"));
        line_b->setGeometry(QRect(710, 490, 101, 25));
        shape1 = new QPushButton(centralwidget);
        shape1->setObjectName(QString::fromUtf8("shape1"));
        shape1->setGeometry(QRect(468, 590, 101, 25));
        shape2 = new QPushButton(centralwidget);
        shape2->setObjectName(QString::fromUtf8("shape2"));
        shape2->setGeometry(QRect(590, 590, 101, 25));
        shape3 = new QPushButton(centralwidget);
        shape3->setObjectName(QString::fromUtf8("shape3"));
        shape3->setGeometry(QRect(710, 590, 101, 25));
        text = new QTextBrowser(centralwidget);
        text->setObjectName(QString::fromUtf8("text"));
        text->setGeometry(QRect(50, 80, 831, 261));
        width_line = new QSlider(centralwidget);
        width_line->setObjectName(QString::fromUtf8("width_line"));
        width_line->setGeometry(QRect(870, 400, 16, 200));
        width_line->setOrientation(Qt::Vertical);
        size_shape = new QSlider(centralwidget);
        size_shape->setObjectName(QString::fromUtf8("size_shape"));
        size_shape->setGeometry(QRect(470, 630, 341, 31));
        size_shape->setMaximum(10);
        size_shape->setOrientation(Qt::Horizontal);
        MainWindowDesign->setCentralWidget(centralwidget);

        retranslateUi(MainWindowDesign);
        QObject::connect(action_Quit, SIGNAL(triggered()), MainWindowDesign, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindowDesign);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowDesign)
    {
        MainWindowDesign->setWindowTitle(QCoreApplication::translate("MainWindowDesign", "QRosApp", nullptr));
        action_Quit->setText(QCoreApplication::translate("MainWindowDesign", "&Quit", nullptr));
#if QT_CONFIG(shortcut)
        action_Quit->setShortcut(QCoreApplication::translate("MainWindowDesign", "Ctrl+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        action_Preferences->setText(QCoreApplication::translate("MainWindowDesign", "&Preferences", nullptr));
        actionAbout->setText(QCoreApplication::translate("MainWindowDesign", "&About", nullptr));
        actionAbout_Qt->setText(QCoreApplication::translate("MainWindowDesign", "About &Qt", nullptr));
        W->setText(QCoreApplication::translate("MainWindowDesign", "W", nullptr));
        S->setText(QCoreApplication::translate("MainWindowDesign", "S", nullptr));
        A->setText(QCoreApplication::translate("MainWindowDesign", "A", nullptr));
        D->setText(QCoreApplication::translate("MainWindowDesign", "D", nullptr));
        background_r->setText(QCoreApplication::translate("MainWindowDesign", "background_r", nullptr));
        background_g->setText(QCoreApplication::translate("MainWindowDesign", "background_g", nullptr));
        background_b->setText(QCoreApplication::translate("MainWindowDesign", "background_b", nullptr));
        line_r->setText(QCoreApplication::translate("MainWindowDesign", "line_r", nullptr));
        line_g->setText(QCoreApplication::translate("MainWindowDesign", "line_g", nullptr));
        line_b->setText(QCoreApplication::translate("MainWindowDesign", "line_b", nullptr));
        shape1->setText(QCoreApplication::translate("MainWindowDesign", "shape1", nullptr));
        shape2->setText(QCoreApplication::translate("MainWindowDesign", "shape2", nullptr));
        shape3->setText(QCoreApplication::translate("MainWindowDesign", "shape3", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindowDesign: public Ui_MainWindowDesign {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
