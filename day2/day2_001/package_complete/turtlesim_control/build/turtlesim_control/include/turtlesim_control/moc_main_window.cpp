/****************************************************************************
** Meta object code from reading C++ file 'main_window.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../include/turtlesim_control/main_window.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'main_window.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[21];
    char stringdata0[263];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 12), // "on_W_clicked"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 12), // "on_S_clicked"
QT_MOC_LITERAL(4, 38, 12), // "on_A_clicked"
QT_MOC_LITERAL(5, 51, 12), // "on_D_clicked"
QT_MOC_LITERAL(6, 64, 13), // "displayCmdVel"
QT_MOC_LITERAL(7, 78, 4), // "data"
QT_MOC_LITERAL(8, 83, 18), // "BackgroundColorRed"
QT_MOC_LITERAL(9, 102, 20), // "BackgroundColorGreen"
QT_MOC_LITERAL(10, 123, 19), // "BackgroundColorBlue"
QT_MOC_LITERAL(11, 143, 12), // "lineColorRed"
QT_MOC_LITERAL(12, 156, 14), // "lineColorGreen"
QT_MOC_LITERAL(13, 171, 13), // "lineColorBlue"
QT_MOC_LITERAL(14, 185, 15), // "changeLineWidth"
QT_MOC_LITERAL(15, 201, 5), // "width"
QT_MOC_LITERAL(16, 207, 10), // "drawCircle"
QT_MOC_LITERAL(17, 218, 12), // "drawTriangle"
QT_MOC_LITERAL(18, 231, 10), // "drawSquare"
QT_MOC_LITERAL(19, 242, 15), // "changeShapeSize"
QT_MOC_LITERAL(20, 258, 4) // "size"

    },
    "MainWindow\0on_W_clicked\0\0on_S_clicked\0"
    "on_A_clicked\0on_D_clicked\0displayCmdVel\0"
    "data\0BackgroundColorRed\0BackgroundColorGreen\0"
    "BackgroundColorBlue\0lineColorRed\0"
    "lineColorGreen\0lineColorBlue\0"
    "changeLineWidth\0width\0drawCircle\0"
    "drawTriangle\0drawSquare\0changeShapeSize\0"
    "size"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x08 /* Private */,
       3,    0,   95,    2, 0x08 /* Private */,
       4,    0,   96,    2, 0x08 /* Private */,
       5,    0,   97,    2, 0x08 /* Private */,
       6,    1,   98,    2, 0x08 /* Private */,
       8,    0,  101,    2, 0x08 /* Private */,
       9,    0,  102,    2, 0x08 /* Private */,
      10,    0,  103,    2, 0x08 /* Private */,
      11,    0,  104,    2, 0x08 /* Private */,
      12,    0,  105,    2, 0x08 /* Private */,
      13,    0,  106,    2, 0x08 /* Private */,
      14,    1,  107,    2, 0x08 /* Private */,
      16,    0,  110,    2, 0x08 /* Private */,
      17,    0,  111,    2, 0x08 /* Private */,
      18,    0,  112,    2, 0x08 /* Private */,
      19,    1,  113,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   20,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_W_clicked(); break;
        case 1: _t->on_S_clicked(); break;
        case 2: _t->on_A_clicked(); break;
        case 3: _t->on_D_clicked(); break;
        case 4: _t->displayCmdVel((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->BackgroundColorRed(); break;
        case 6: _t->BackgroundColorGreen(); break;
        case 7: _t->BackgroundColorBlue(); break;
        case 8: _t->lineColorRed(); break;
        case 9: _t->lineColorGreen(); break;
        case 10: _t->lineColorBlue(); break;
        case 11: _t->changeLineWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->drawCircle(); break;
        case 13: _t->drawTriangle(); break;
        case 14: _t->drawSquare(); break;
        case 15: _t->changeShapeSize((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
