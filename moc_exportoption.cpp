/****************************************************************************
** Meta object code from reading C++ file 'exportoption.h'
**
** Created: Mon Feb 22 01:08:20 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "exportoption.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'exportoption.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ExportOption[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x08,
      38,   13,   13,   13, 0x08,
      62,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ExportOption[] = {
    "ExportOption\0\0on_buttonBox_rejected()\0"
    "on_buttonBox_accepted()\0buttonSelected()\0"
};

const QMetaObject ExportOption::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ExportOption,
      qt_meta_data_ExportOption, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ExportOption::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ExportOption::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ExportOption::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ExportOption))
        return static_cast<void*>(const_cast< ExportOption*>(this));
    return QDialog::qt_metacast(_clname);
}

int ExportOption::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_buttonBox_rejected(); break;
        case 1: on_buttonBox_accepted(); break;
        case 2: buttonSelected(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
