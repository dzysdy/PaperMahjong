/****************************************************************************
** Meta object code from reading C++ file 'MahjongJudgment.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../MahjongJudgment.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MahjongJudgment.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MahjongJudgment_t {
    QByteArrayData data[15];
    char stringdata0[197];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MahjongJudgment_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MahjongJudgment_t qt_meta_stringdata_MahjongJudgment = {
    {
QT_MOC_LITERAL(0, 0, 15), // "MahjongJudgment"
QT_MOC_LITERAL(1, 16, 10), // "updateTime"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 3), // "sec"
QT_MOC_LITERAL(4, 32, 9), // "firstStep"
QT_MOC_LITERAL(5, 42, 22), // "QList<PlayerOperation>"
QT_MOC_LITERAL(6, 65, 10), // "operations"
QT_MOC_LITERAL(7, 76, 10), // "secondStep"
QT_MOC_LITERAL(8, 87, 14), // "makeHappyGroup"
QT_MOC_LITERAL(9, 102, 7), // "onTimer"
QT_MOC_LITERAL(10, 110, 20), // "onFirstStepCompleted"
QT_MOC_LITERAL(11, 131, 15), // "PlayerOperation"
QT_MOC_LITERAL(12, 147, 9), // "operation"
QT_MOC_LITERAL(13, 157, 21), // "onSecondStepCompleted"
QT_MOC_LITERAL(14, 179, 17) // "onMakedHappyGroup"

    },
    "MahjongJudgment\0updateTime\0\0sec\0"
    "firstStep\0QList<PlayerOperation>\0"
    "operations\0secondStep\0makeHappyGroup\0"
    "onTimer\0onFirstStepCompleted\0"
    "PlayerOperation\0operation\0"
    "onSecondStepCompleted\0onMakedHappyGroup"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MahjongJudgment[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    1,   57,    2, 0x06 /* Public */,
       7,    1,   60,    2, 0x06 /* Public */,
       8,    0,   63,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   64,    2, 0x0a /* Public */,
      10,    1,   65,    2, 0x0a /* Public */,
      13,    1,   68,    2, 0x0a /* Public */,
      14,    0,   71,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::UInt,    3,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,

       0        // eod
};

void MahjongJudgment::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MahjongJudgment *_t = static_cast<MahjongJudgment *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateTime((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 1: _t->firstStep((*reinterpret_cast< QList<PlayerOperation>(*)>(_a[1]))); break;
        case 2: _t->secondStep((*reinterpret_cast< QList<PlayerOperation>(*)>(_a[1]))); break;
        case 3: _t->makeHappyGroup(); break;
        case 4: _t->onTimer(); break;
        case 5: _t->onFirstStepCompleted((*reinterpret_cast< PlayerOperation(*)>(_a[1]))); break;
        case 6: _t->onSecondStepCompleted((*reinterpret_cast< PlayerOperation(*)>(_a[1]))); break;
        case 7: _t->onMakedHappyGroup(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MahjongJudgment::*_t)(unsigned  );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MahjongJudgment::updateTime)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MahjongJudgment::*_t)(QList<PlayerOperation> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MahjongJudgment::firstStep)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (MahjongJudgment::*_t)(QList<PlayerOperation> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MahjongJudgment::secondStep)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (MahjongJudgment::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MahjongJudgment::makeHappyGroup)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject MahjongJudgment::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MahjongJudgment.data,
      qt_meta_data_MahjongJudgment,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MahjongJudgment::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MahjongJudgment::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MahjongJudgment.stringdata0))
        return static_cast<void*>(const_cast< MahjongJudgment*>(this));
    return QObject::qt_metacast(_clname);
}

int MahjongJudgment::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void MahjongJudgment::updateTime(unsigned  _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MahjongJudgment::firstStep(QList<PlayerOperation> _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MahjongJudgment::secondStep(QList<PlayerOperation> _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MahjongJudgment::makeHappyGroup()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
