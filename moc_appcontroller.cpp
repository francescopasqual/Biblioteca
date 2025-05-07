/****************************************************************************
** Meta object code from reading C++ file 'appcontroller.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "appcontroller.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'appcontroller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_AppController_t {
    uint offsetsAndSizes[34];
    char stringdata0[14];
    char stringdata1[19];
    char stringdata2[1];
    char stringdata3[9];
    char stringdata4[9];
    char stringdata5[19];
    char stringdata6[6];
    char stringdata7[23];
    char stringdata8[13];
    char stringdata9[22];
    char stringdata10[6];
    char stringdata11[13];
    char stringdata12[29];
    char stringdata13[18];
    char stringdata14[5];
    char stringdata15[18];
    char stringdata16[25];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_AppController_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_AppController_t qt_meta_stringdata_AppController = {
    {
        QT_MOC_LITERAL(0, 13),  // "AppController"
        QT_MOC_LITERAL(14, 18),  // "handleLoginRequest"
        QT_MOC_LITERAL(33, 0),  // ""
        QT_MOC_LITERAL(34, 8),  // "username"
        QT_MOC_LITERAL(43, 8),  // "password"
        QT_MOC_LITERAL(52, 18),  // "handleGlobalSearch"
        QT_MOC_LITERAL(71, 5),  // "query"
        QT_MOC_LITERAL(77, 22),  // "handleCategorySelected"
        QT_MOC_LITERAL(100, 12),  // "categoryName"
        QT_MOC_LITERAL(113, 21),  // "handleItemListClicked"
        QT_MOC_LITERAL(135, 5),  // "Item*"
        QT_MOC_LITERAL(141, 12),  // "selectedItem"
        QT_MOC_LITERAL(154, 28),  // "handleReturnToCatalogRequest"
        QT_MOC_LITERAL(183, 17),  // "handleLoanRequest"
        QT_MOC_LITERAL(201, 4),  // "item"
        QT_MOC_LITERAL(206, 17),  // "handleKeepRequest"
        QT_MOC_LITERAL(224, 24)   // "handleExitDetailsRequest"
    },
    "AppController",
    "handleLoginRequest",
    "",
    "username",
    "password",
    "handleGlobalSearch",
    "query",
    "handleCategorySelected",
    "categoryName",
    "handleItemListClicked",
    "Item*",
    "selectedItem",
    "handleReturnToCatalogRequest",
    "handleLoanRequest",
    "item",
    "handleKeepRequest",
    "handleExitDetailsRequest"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_AppController[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   62,    2, 0x08,    1 /* Private */,
       5,    1,   67,    2, 0x08,    4 /* Private */,
       7,    1,   70,    2, 0x08,    6 /* Private */,
       9,    1,   73,    2, 0x08,    8 /* Private */,
      12,    0,   76,    2, 0x08,   10 /* Private */,
      13,    1,   77,    2, 0x08,   11 /* Private */,
      15,    1,   80,    2, 0x08,   13 /* Private */,
      16,    0,   83,    2, 0x08,   15 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   14,
    QMetaType::Void, 0x80000000 | 10,   14,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject AppController::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_AppController.offsetsAndSizes,
    qt_meta_data_AppController,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_AppController_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<AppController, std::true_type>,
        // method 'handleLoginRequest'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'handleGlobalSearch'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'handleCategorySelected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'handleItemListClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Item *, std::false_type>,
        // method 'handleReturnToCatalogRequest'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleLoanRequest'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Item *, std::false_type>,
        // method 'handleKeepRequest'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Item *, std::false_type>,
        // method 'handleExitDetailsRequest'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void AppController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AppController *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->handleLoginRequest((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 1: _t->handleGlobalSearch((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->handleCategorySelected((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->handleItemListClicked((*reinterpret_cast< std::add_pointer_t<Item*>>(_a[1]))); break;
        case 4: _t->handleReturnToCatalogRequest(); break;
        case 5: _t->handleLoanRequest((*reinterpret_cast< std::add_pointer_t<Item*>>(_a[1]))); break;
        case 6: _t->handleKeepRequest((*reinterpret_cast< std::add_pointer_t<Item*>>(_a[1]))); break;
        case 7: _t->handleExitDetailsRequest(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Item* >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Item* >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Item* >(); break;
            }
            break;
        }
    }
}

const QMetaObject *AppController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AppController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AppController.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int AppController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
