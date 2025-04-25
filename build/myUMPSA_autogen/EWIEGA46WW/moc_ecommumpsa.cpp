/****************************************************************************
** Meta object code from reading C++ file 'ecommumpsa.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../ecommumpsa.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ecommumpsa.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN10EcommUMPSAE_t {};
} // unnamed namespace

template <> constexpr inline auto EcommUMPSA::qt_create_metaobjectdata<qt_meta_tag_ZN10EcommUMPSAE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "EcommUMPSA",
        "attendantFound",
        "",
        "time",
        "attendantNotFound",
        "checkInSignal",
        "QNetworkReply*",
        "reply",
        "checkOutSignal",
        "onCookiesSlot",
        "onLoginSlot",
        "onAttedanceSlot",
        "savetofile",
        "QString&",
        "responseText",
        "onSslError",
        "r",
        "QList<QSslError>",
        "l"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'attendantFound'
        QtMocHelpers::SignalData<void(QString)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 3 },
        }}),
        // Signal 'attendantNotFound'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'checkInSignal'
        QtMocHelpers::SignalData<void(QNetworkReply *)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 6, 7 },
        }}),
        // Signal 'checkOutSignal'
        QtMocHelpers::SignalData<void(QNetworkReply *)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 6, 7 },
        }}),
        // Slot 'onCookiesSlot'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onLoginSlot'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onAttedanceSlot'
        QtMocHelpers::SlotData<void()>(11, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'savetofile'
        QtMocHelpers::SlotData<void(QString &)>(12, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 13, 14 },
        }}),
        // Slot 'onSslError'
        QtMocHelpers::SlotData<void(QNetworkReply *, QList<QSslError>)>(15, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 6, 16 }, { 0x80000000 | 17, 18 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<EcommUMPSA, qt_meta_tag_ZN10EcommUMPSAE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject EcommUMPSA::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10EcommUMPSAE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10EcommUMPSAE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10EcommUMPSAE_t>.metaTypes,
    nullptr
} };

void EcommUMPSA::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<EcommUMPSA *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->attendantFound((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->attendantNotFound(); break;
        case 2: _t->checkInSignal((*reinterpret_cast< std::add_pointer_t<QNetworkReply*>>(_a[1]))); break;
        case 3: _t->checkOutSignal((*reinterpret_cast< std::add_pointer_t<QNetworkReply*>>(_a[1]))); break;
        case 4: _t->onCookiesSlot(); break;
        case 5: _t->onLoginSlot(); break;
        case 6: _t->onAttedanceSlot(); break;
        case 7: _t->savetofile((*reinterpret_cast< std::add_pointer_t<QString&>>(_a[1]))); break;
        case 8: _t->onSslError((*reinterpret_cast< std::add_pointer_t<QNetworkReply*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QList<QSslError>>>(_a[2]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<QSslError> >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (EcommUMPSA::*)(QString )>(_a, &EcommUMPSA::attendantFound, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (EcommUMPSA::*)()>(_a, &EcommUMPSA::attendantNotFound, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (EcommUMPSA::*)(QNetworkReply * )>(_a, &EcommUMPSA::checkInSignal, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (EcommUMPSA::*)(QNetworkReply * )>(_a, &EcommUMPSA::checkOutSignal, 3))
            return;
    }
}

const QMetaObject *EcommUMPSA::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EcommUMPSA::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10EcommUMPSAE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int EcommUMPSA::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void EcommUMPSA::attendantFound(QString _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void EcommUMPSA::attendantNotFound()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void EcommUMPSA::checkInSignal(QNetworkReply * _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void EcommUMPSA::checkOutSignal(QNetworkReply * _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}
QT_WARNING_POP
