/****************************************************************************
** Meta object code from reading C++ file 'vsccameraadd.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../main/vsccameraadd.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vsccameraadd.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_VSCCameraAdd_t {
    QByteArrayData data[7];
    char stringdata[96];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_VSCCameraAdd_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_VSCCameraAdd_t qt_meta_stringdata_VSCCameraAdd = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 17),
QT_MOC_LITERAL(2, 31, 0),
QT_MOC_LITERAL(3, 32, 14),
QT_MOC_LITERAL(4, 47, 16),
QT_MOC_LITERAL(5, 64, 18),
QT_MOC_LITERAL(6, 83, 11)
    },
    "VSCCameraAdd\0CameraTreeUpdated\0\0"
    "floatingAction\0unFloatingAction\0"
    "radioButtonClicked\0applyConfig\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSCCameraAdd[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       3,    0,   40,    2, 0x08,
       4,    0,   41,    2, 0x08,
       5,    0,   42,    2, 0x08,
       6,    0,   43,    2, 0x08,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void VSCCameraAdd::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VSCCameraAdd *_t = static_cast<VSCCameraAdd *>(_o);
        switch (_id) {
        case 0: _t->CameraTreeUpdated(); break;
        case 1: _t->floatingAction(); break;
        case 2: _t->unFloatingAction(); break;
        case 3: _t->radioButtonClicked(); break;
        case 4: _t->applyConfig(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (VSCCameraAdd::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VSCCameraAdd::CameraTreeUpdated)) {
                *result = 0;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject VSCCameraAdd::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_VSCCameraAdd.data,
      qt_meta_data_VSCCameraAdd,  qt_static_metacall, 0, 0}
};


const QMetaObject *VSCCameraAdd::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSCCameraAdd::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VSCCameraAdd.stringdata))
        return static_cast<void*>(const_cast< VSCCameraAdd*>(this));
    return QWidget::qt_metacast(_clname);
}

int VSCCameraAdd::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void VSCCameraAdd::CameraTreeUpdated()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
