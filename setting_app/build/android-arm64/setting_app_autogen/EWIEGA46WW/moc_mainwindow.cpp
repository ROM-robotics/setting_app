/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.3. It"
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
struct qt_meta_tag_ZN10MainWindowE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN10MainWindowE = QtMocHelpers::stringData(
    "MainWindow",
    "onModeToggleClicked",
    "",
    "onRefreshWifiClicked",
    "onConnectionStatusChanged",
    "connected",
    "onWifiStatusReceived",
    "ssid",
    "status",
    "ipAddress",
    "onWifiNetworksScanned",
    "networks",
    "onWifiNetworkChanged",
    "success",
    "message",
    "onNetworkError",
    "error",
    "showVirtualKeyboard",
    "hideVirtualKeyboard",
    "onKeyboardKeyPressed",
    "key",
    "updateConnectionIndicator"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN10MainWindowE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   80,    2, 0x08,    1 /* Private */,
       3,    0,   81,    2, 0x08,    2 /* Private */,
       4,    1,   82,    2, 0x08,    3 /* Private */,
       6,    3,   85,    2, 0x08,    5 /* Private */,
      10,    1,   92,    2, 0x08,    9 /* Private */,
      12,    2,   95,    2, 0x08,   11 /* Private */,
      15,    1,  100,    2, 0x08,   14 /* Private */,
      17,    0,  103,    2, 0x08,   16 /* Private */,
      18,    0,  104,    2, 0x08,   17 /* Private */,
      19,    1,  105,    2, 0x08,   18 /* Private */,
      21,    0,  108,    2, 0x08,   20 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    7,    8,    9,
    QMetaType::Void, QMetaType::QStringList,   11,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,   13,   14,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   20,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_ZN10MainWindowE.offsetsAndSizes,
    qt_meta_data_ZN10MainWindowE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN10MainWindowE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'onModeToggleClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onRefreshWifiClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onConnectionStatusChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'onWifiStatusReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'onWifiNetworksScanned'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QStringList &, std::false_type>,
        // method 'onWifiNetworkChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'onNetworkError'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'showVirtualKeyboard'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'hideVirtualKeyboard'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onKeyboardKeyPressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'updateConnectionIndicator'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MainWindow *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->onModeToggleClicked(); break;
        case 1: _t->onRefreshWifiClicked(); break;
        case 2: _t->onConnectionStatusChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 3: _t->onWifiStatusReceived((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3]))); break;
        case 4: _t->onWifiNetworksScanned((*reinterpret_cast< std::add_pointer_t<QStringList>>(_a[1]))); break;
        case 5: _t->onWifiNetworkChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 6: _t->onNetworkError((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->showVirtualKeyboard(); break;
        case 8: _t->hideVirtualKeyboard(); break;
        case 9: _t->onKeyboardKeyPressed((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 10: _t->updateConnectionIndicator(); break;
        default: ;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN10MainWindowE.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
