/****************************************************************************
** Meta object code from reading C++ file 'levelselectwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MainMenu/levelselectwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'levelselectwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_LevelSelectWindow_t {
    QByteArrayData data[16];
    char stringdata0[229];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LevelSelectWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LevelSelectWindow_t qt_meta_stringdata_LevelSelectWindow = {
    {
QT_MOC_LITERAL(0, 0, 17), // "LevelSelectWindow"
QT_MOC_LITERAL(1, 18, 6), // "logOut"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 9), // "startGame"
QT_MOC_LITERAL(4, 36, 9), // "showEvent"
QT_MOC_LITERAL(5, 46, 11), // "QShowEvent*"
QT_MOC_LITERAL(6, 58, 8), // "showMenu"
QT_MOC_LITERAL(7, 67, 17), // "on_Level1_clicked"
QT_MOC_LITERAL(8, 85, 17), // "on_Level2_clicked"
QT_MOC_LITERAL(9, 103, 17), // "on_Level3_clicked"
QT_MOC_LITERAL(10, 121, 17), // "on_Level4_clicked"
QT_MOC_LITERAL(11, 139, 17), // "on_Level5_clicked"
QT_MOC_LITERAL(12, 157, 17), // "on_Level6_clicked"
QT_MOC_LITERAL(13, 175, 17), // "on_Level7_clicked"
QT_MOC_LITERAL(14, 193, 17), // "on_Level8_clicked"
QT_MOC_LITERAL(15, 211, 17) // "on_Level9_clicked"

    },
    "LevelSelectWindow\0logOut\0\0startGame\0"
    "showEvent\0QShowEvent*\0showMenu\0"
    "on_Level1_clicked\0on_Level2_clicked\0"
    "on_Level3_clicked\0on_Level4_clicked\0"
    "on_Level5_clicked\0on_Level6_clicked\0"
    "on_Level7_clicked\0on_Level8_clicked\0"
    "on_Level9_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LevelSelectWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x08 /* Private */,
       3,    1,   80,    2, 0x08 /* Private */,
       4,    1,   83,    2, 0x08 /* Private */,
       6,    0,   86,    2, 0x08 /* Private */,
       7,    0,   87,    2, 0x08 /* Private */,
       8,    0,   88,    2, 0x08 /* Private */,
       9,    0,   89,    2, 0x08 /* Private */,
      10,    0,   90,    2, 0x08 /* Private */,
      11,    0,   91,    2, 0x08 /* Private */,
      12,    0,   92,    2, 0x08 /* Private */,
      13,    0,   93,    2, 0x08 /* Private */,
      14,    0,   94,    2, 0x08 /* Private */,
      15,    0,   95,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void LevelSelectWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LevelSelectWindow *_t = static_cast<LevelSelectWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->logOut(); break;
        case 1: _t->startGame((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->showEvent((*reinterpret_cast< QShowEvent*(*)>(_a[1]))); break;
        case 3: _t->showMenu(); break;
        case 4: _t->on_Level1_clicked(); break;
        case 5: _t->on_Level2_clicked(); break;
        case 6: _t->on_Level3_clicked(); break;
        case 7: _t->on_Level4_clicked(); break;
        case 8: _t->on_Level5_clicked(); break;
        case 9: _t->on_Level6_clicked(); break;
        case 10: _t->on_Level7_clicked(); break;
        case 11: _t->on_Level8_clicked(); break;
        case 12: _t->on_Level9_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject LevelSelectWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_LevelSelectWindow.data,
      qt_meta_data_LevelSelectWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *LevelSelectWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LevelSelectWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_LevelSelectWindow.stringdata0))
        return static_cast<void*>(const_cast< LevelSelectWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int LevelSelectWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
