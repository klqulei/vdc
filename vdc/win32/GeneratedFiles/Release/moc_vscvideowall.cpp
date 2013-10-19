/****************************************************************************
** Meta object code from reading C++ file 'vscvideowall.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../vwidget/vscvideowall.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vscvideowall.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_VSCVideoWall_t {
    QByteArrayData data[15];
    char stringdata[224];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_VSCVideoWall_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_VSCVideoWall_t qt_meta_stringdata_VSCVideoWall = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 18),
QT_MOC_LITERAL(2, 32, 0),
QT_MOC_LITERAL(3, 33, 3),
QT_MOC_LITERAL(4, 37, 19),
QT_MOC_LITERAL(5, 57, 17),
QT_MOC_LITERAL(6, 75, 16),
QT_MOC_LITERAL(7, 92, 14),
QT_MOC_LITERAL(8, 107, 16),
QT_MOC_LITERAL(9, 124, 16),
QT_MOC_LITERAL(10, 141, 16),
QT_MOC_LITERAL(11, 158, 16),
QT_MOC_LITERAL(12, 175, 14),
QT_MOC_LITERAL(13, 190, 17),
QT_MOC_LITERAL(14, 208, 14)
    },
    "VSCVideoWall\0ShowDisplayClicked\0\0nId\0"
    "ShowFloatingClicked\0ShowTabbedClicked\0"
    "ShowFocusClicked\0floatingAction\0"
    "unFloatingAction\0SetLayoutMode4x4\0"
    "SetLayoutMode3x3\0SetLayoutMode2x2\0"
    "SetLayoutMode6\0SetLayoutMode12p1\0"
    "SetLayoutMode1\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSCVideoWall[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x05,
       4,    0,   77,    2, 0x05,
       5,    0,   78,    2, 0x05,
       6,    1,   79,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       7,    0,   82,    2, 0x0a,
       8,    0,   83,    2, 0x0a,
       9,    0,   84,    2, 0x0a,
      10,    0,   85,    2, 0x0a,
      11,    0,   86,    2, 0x0a,
      12,    0,   87,    2, 0x0a,
      13,    0,   88,    2, 0x0a,
      14,    0,   89,    2, 0x0a,

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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void VSCVideoWall::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VSCVideoWall *_t = static_cast<VSCVideoWall *>(_o);
        switch (_id) {
        case 0: _t->ShowDisplayClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->ShowFloatingClicked(); break;
        case 2: _t->ShowTabbedClicked(); break;
        case 3: _t->ShowFocusClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->floatingAction(); break;
        case 5: _t->unFloatingAction(); break;
        case 6: _t->SetLayoutMode4x4(); break;
        case 7: _t->SetLayoutMode3x3(); break;
        case 8: _t->SetLayoutMode2x2(); break;
        case 9: _t->SetLayoutMode6(); break;
        case 10: _t->SetLayoutMode12p1(); break;
        case 11: _t->SetLayoutMode1(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (VSCVideoWall::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VSCVideoWall::ShowDisplayClicked)) {
                *result = 0;
            }
        }
        {
            typedef void (VSCVideoWall::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VSCVideoWall::ShowFloatingClicked)) {
                *result = 1;
            }
        }
        {
            typedef void (VSCVideoWall::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VSCVideoWall::ShowTabbedClicked)) {
                *result = 2;
            }
        }
        {
            typedef void (VSCVideoWall::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VSCVideoWall::ShowFocusClicked)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject VSCVideoWall::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_VSCVideoWall.data,
      qt_meta_data_VSCVideoWall,  qt_static_metacall, 0, 0}
};


const QMetaObject *VSCVideoWall::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSCVideoWall::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VSCVideoWall.stringdata))
        return static_cast<void*>(const_cast< VSCVideoWall*>(this));
    return QWidget::qt_metacast(_clname);
}

int VSCVideoWall::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void VSCVideoWall::ShowDisplayClicked(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VSCVideoWall::ShowFloatingClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void VSCVideoWall::ShowTabbedClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void VSCVideoWall::ShowFocusClicked(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
