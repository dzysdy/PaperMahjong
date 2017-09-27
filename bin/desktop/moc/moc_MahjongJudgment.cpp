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
    QByteArrayData data[21];
    char stringdata0[270];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MahjongJudgment_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MahjongJudgment_t qt_meta_stringdata_MahjongJudgment = {
    {
QT_MOC_LITERAL(0, 0, 15), // "MahjongJudgment"
QT_MOC_LITERAL(1, 16, 14), // "makeHappyGroup"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 7), // "balance"
QT_MOC_LITERAL(4, 40, 10), // "deltaMoney"
QT_MOC_LITERAL(5, 51, 10), // "updateTime"
QT_MOC_LITERAL(6, 62, 3), // "sec"
QT_MOC_LITERAL(7, 66, 7), // "onTimer"
QT_MOC_LITERAL(8, 74, 20), // "onFirstStepCompleted"
QT_MOC_LITERAL(9, 95, 9), // "operation"
QT_MOC_LITERAL(10, 105, 21), // "onSecondStepCompleted"
QT_MOC_LITERAL(11, 127, 15), // "PlayerOperation"
QT_MOC_LITERAL(12, 143, 25), // "onMakeHappyGroupCompleted"
QT_MOC_LITERAL(13, 169, 13), // "onWinningHand"
QT_MOC_LITERAL(14, 183, 7), // "Player*"
QT_MOC_LITERAL(15, 191, 6), // "player"
QT_MOC_LITERAL(16, 198, 12), // "onUpdateTime"
QT_MOC_LITERAL(17, 211, 16), // "handleOperations"
QT_MOC_LITERAL(18, 228, 22), // "QList<PlayerOperation>"
QT_MOC_LITERAL(19, 251, 10), // "operations"
QT_MOC_LITERAL(20, 262, 7) // "onDraws"

    },
    "MahjongJudgment\0makeHappyGroup\0\0balance\0"
    "deltaMoney\0updateTime\0sec\0onTimer\0"
    "onFirstStepCompleted\0operation\0"
    "onSecondStepCompleted\0PlayerOperation\0"
    "onMakeHappyGroupCompleted\0onWinningHand\0"
    "Player*\0player\0onUpdateTime\0"
    "handleOperations\0QList<PlayerOperation>\0"
    "operations\0onDraws"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MahjongJudgment[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,
       3,    1,   70,    2, 0x06 /* Public */,
       5,    1,   73,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   76,    2, 0x0a /* Public */,
       8,    1,   77,    2, 0x0a /* Public */,
      10,    1,   80,    2, 0x0a /* Public */,
      12,    0,   83,    2, 0x0a /* Public */,
      13,    1,   84,    2, 0x0a /* Public */,
      16,    1,   87,    2, 0x0a /* Public */,
      17,    1,   90,    2, 0x0a /* Public */,
      20,    0,   93,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::UInt,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, 0x80000000 | 11,    9,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, QMetaType::UInt,    6,
    QMetaType::Void, 0x80000000 | 18,   19,
    QMetaType::Void,

       0        // eod
};

void MahjongJudgment::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MahjongJudgment *_t = static_cast<MahjongJudgment *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->makeHappyGroup(); break;
        case 1: _t->balance((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->updateTime((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 3: _t->onTimer(); break;
        case 4: _t->onFirstStepCompleted((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->onSecondStepCompleted((*reinterpret_cast< PlayerOperation(*)>(_a[1]))); break;
        case 6: _t->onMakeHappyGroupCompleted(); break;
        case 7: _t->onWinningHand((*reinterpret_cast< Player*(*)>(_a[1]))); break;
        case 8: _t->onUpdateTime((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 9: _t->handleOperations((*reinterpret_cast< QList<PlayerOperation>(*)>(_a[1]))); break;
        case 10: _t->onDraws(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Player* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MahjongJudgment::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MahjongJudgment::makeHappyGroup)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MahjongJudgment::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MahjongJudgment::balance)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (MahjongJudgment::*_t)(unsigned  );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MahjongJudgment::updateTime)) {
                *result = 2;
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
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void MahjongJudgment::makeHappyGroup()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void MahjongJudgment::balance(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MahjongJudgment::updateTime(unsigned  _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
