/****************************************************************************
** Meta object code from reading C++ file 'vscdevicelist.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../main/vscdevicelist.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vscdevicelist.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_VSCDeviceList_t {
    QByteArrayData data[13];
    char stringdata[185];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_VSCDeviceList_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_VSCDeviceList_t qt_meta_stringdata_VSCDeviceList = {
    {
QT_MOC_LITERAL(0, 0, 13),
QT_MOC_LITERAL(1, 14, 19),
QT_MOC_LITERAL(2, 34, 0),
QT_MOC_LITERAL(3, 35, 16),
QT_MOC_LITERAL(4, 52, 13),
QT_MOC_LITERAL(5, 66, 17),
QT_MOC_LITERAL(6, 84, 3),
QT_MOC_LITERAL(7, 88, 19),
QT_MOC_LITERAL(8, 108, 17),
QT_MOC_LITERAL(9, 126, 14),
QT_MOC_LITERAL(10, 141, 11),
QT_MOC_LITERAL(11, 153, 17),
QT_MOC_LITERAL(12, 171, 12)
    },
    "VSCDeviceList\0SurveillanceClicked\0\0"
    "CameraAddClicked\0SearchClicked\0"
    "CameraEditClicked\0nId\0CameraDeleteClicked\0"
    "SurveillanceClick\0CameraAddClick\0"
    "SearchClick\0CameraTreeUpdated\0"
    "UpdateOnline\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSCDeviceList[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x05,
       3,    0,   65,    2, 0x05,
       4,    0,   66,    2, 0x05,
       5,    1,   67,    2, 0x05,
       7,    1,   70,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       8,    0,   73,    2, 0x0a,
       9,    0,   74,    2, 0x0a,
      10,    0,   75,    2, 0x0a,
      11,    0,   76,    2, 0x0a,
      12,    0,   77,    2, 0x0a,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void VSCDeviceList::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VSCDeviceList *_t = static_cast<VSCDeviceList *>(_o);
        switch (_id) {
        case 0: _t->SurveillanceClicked(); break;
        case 1: _t->CameraAddClicked(); break;
        case 2: _t->SearchClicked(); break;
        case 3: _t->CameraEditClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->CameraDeleteClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->SurveillanceClick(); break;
        case 6: _t->CameraAddClick(); break;
        case 7: _t->SearchClick(); break;
        case 8: _t->CameraTreeUpdated(); break;
        case 9: _t->UpdateOnline(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (VSCDeviceList::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VSCDeviceList::SurveillanceClicked)) {
                *result = 0;
            }
        }
        {
            typedef void (VSCDeviceList::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VSCDeviceList::CameraAddClicked)) {
                *result = 1;
            }
        }
        {
            typedef void (VSCDeviceList::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VSCDeviceList::SearchClicked)) {
                *result = 2;
            }
        }
        {
            typedef void (VSCDeviceList::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VSCDeviceList::CameraEditClicked)) {
                *result = 3;
            }
        }
        {
            typedef void (VSCDeviceList::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VSCDeviceList::CameraDeleteClicked)) {
                *result = 4;
            }
        }
    }
}

const QMetaObject VSCDeviceList::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_VSCDeviceList.data,
      qt_meta_data_VSCDeviceList,  qt_static_metacall, 0, 0}
};


const QMetaObject *VSCDeviceList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSCDeviceList::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VSCDeviceList.stringdata))
        return static_cast<void*>(const_cast< VSCDeviceList*>(this));
    return QWidget::qt_metacast(_clname);
}

int VSCDeviceList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void VSCDeviceList::SurveillanceClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void VSCDeviceList::CameraAddClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void VSCDeviceList::SearchClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void VSCDeviceList::CameraEditClicked(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void VSCDeviceList::CameraDeleteClicked(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
