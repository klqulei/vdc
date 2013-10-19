/****************************************************************************
** Meta object code from reading C++ file 'vscvwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../vwidget/vscvwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vscvwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_VSCVWidget_t {
    QByteArrayData data[12];
    char stringdata[154];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_VSCVWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_VSCVWidget_t qt_meta_stringdata_VSCVWidget = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 18),
QT_MOC_LITERAL(2, 30, 0),
QT_MOC_LITERAL(3, 31, 3),
QT_MOC_LITERAL(4, 35, 19),
QT_MOC_LITERAL(5, 55, 17),
QT_MOC_LITERAL(6, 73, 16),
QT_MOC_LITERAL(7, 90, 10),
QT_MOC_LITERAL(8, 101, 12),
QT_MOC_LITERAL(9, 114, 12),
QT_MOC_LITERAL(10, 127, 12),
QT_MOC_LITERAL(11, 140, 12)
    },
    "VSCVWidget\0ShowDisplayClicked\0\0nId\0"
    "ShowFloatingClicked\0ShowTabbedClicked\0"
    "ShowFocusClicked\0stopAction\0showDisplay1\0"
    "showDisplay2\0showDisplay3\0showDisplay4\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSCVWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x05,
       4,    0,   62,    2, 0x05,
       5,    0,   63,    2, 0x05,
       6,    1,   64,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       7,    0,   67,    2, 0x08,
       8,    0,   68,    2, 0x08,
       9,    0,   69,    2, 0x08,
      10,    0,   70,    2, 0x08,
      11,    0,   71,    2, 0x08,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void VSCVWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VSCVWidget *_t = static_cast<VSCVWidget *>(_o);
        switch (_id) {
        case 0: _t->ShowDisplayClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->ShowFloatingClicked(); break;
        case 2: _t->ShowTabbedClicked(); break;
        case 3: _t->ShowFocusClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->stopAction(); break;
        case 5: _t->showDisplay1(); break;
        case 6: _t->showDisplay2(); break;
        case 7: _t->showDisplay3(); break;
        case 8: _t->showDisplay4(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (VSCVWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VSCVWidget::ShowDisplayClicked)) {
                *result = 0;
            }
        }
        {
            typedef void (VSCVWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VSCVWidget::ShowFloatingClicked)) {
                *result = 1;
            }
        }
        {
            typedef void (VSCVWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VSCVWidget::ShowTabbedClicked)) {
                *result = 2;
            }
        }
        {
            typedef void (VSCVWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VSCVWidget::ShowFocusClicked)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject VSCVWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_VSCVWidget.data,
      qt_meta_data_VSCVWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *VSCVWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSCVWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VSCVWidget.stringdata))
        return static_cast<void*>(const_cast< VSCVWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int VSCVWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void VSCVWidget::ShowDisplayClicked(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VSCVWidget::ShowFloatingClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void VSCVWidget::ShowTabbedClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void VSCVWidget::ShowFocusClicked(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
