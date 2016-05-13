/****************************************************************************
** Meta object code from reading C++ file 'gp.h'
**
** Created: Mon Feb 22 01:08:18 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "gp.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_gp[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       4,    3,    3,    3, 0x0a,
      34,    3,    3,    3, 0x0a,
      63,    3,    3,    3, 0x0a,
      81,   75,    3,    3, 0x0a,
     115,  107,    3,    3, 0x0a,
     146,    3,    3,    3, 0x0a,
     158,    3,    3,    3, 0x0a,
     183,  175,    3,    3, 0x0a,
     197,    3,    3,    3, 0x08,
     218,    3,    3,    3, 0x08,
     240,    3,    3,    3, 0x08,
     264,    3,    3,    3, 0x08,
     284,    3,    3,    3, 0x08,
     305,    3,    3,    3, 0x08,
     325,    3,    3,    3, 0x08,
     345,    3,    3,    3, 0x08,
     367,    3,    3,    3, 0x08,
     387,    3,    3,    3, 0x08,
     409,    3,    3,    3, 0x08,
     429,    3,    3,    3, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_gp[] = {
    "gp\0\0on_courseGrade_valueChanged()\0"
    "on_courseUnit_valueChanged()\0updateLcd()\0"
    "cu,cg\0update_tnu_tcp(int&,int&)\0tnu,tcp\0"
    "display_tnu_tcp_gpa(int&,int&)\0"
    "clear_all()\0set_all_toZero()\0newMode\0"
    "setMode(Mode)\0on_saveBtn_clicked()\0"
    "on_pbExport_clicked()\0on_pbSaveEdit_clicked()\0"
    "on_pbEdit_clicked()\0on_pbClear_clicked()\0"
    "on_pbNext_clicked()\0on_pbPrev_clicked()\0"
    "on_pbRemove_clicked()\0on_pbLoad_clicked()\0"
    "on_pbSaveAs_clicked()\0on_pbQuit_clicked()\0"
    "on_pbAdd_clicked()\0"
};

const QMetaObject gp::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_gp,
      qt_meta_data_gp, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &gp::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *gp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *gp::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_gp))
        return static_cast<void*>(const_cast< gp*>(this));
    return QWidget::qt_metacast(_clname);
}

int gp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_courseGrade_valueChanged(); break;
        case 1: on_courseUnit_valueChanged(); break;
        case 2: updateLcd(); break;
        case 3: update_tnu_tcp((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: display_tnu_tcp_gpa((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: clear_all(); break;
        case 6: set_all_toZero(); break;
        case 7: setMode((*reinterpret_cast< Mode(*)>(_a[1]))); break;
        case 8: on_saveBtn_clicked(); break;
        case 9: on_pbExport_clicked(); break;
        case 10: on_pbSaveEdit_clicked(); break;
        case 11: on_pbEdit_clicked(); break;
        case 12: on_pbClear_clicked(); break;
        case 13: on_pbNext_clicked(); break;
        case 14: on_pbPrev_clicked(); break;
        case 15: on_pbRemove_clicked(); break;
        case 16: on_pbLoad_clicked(); break;
        case 17: on_pbSaveAs_clicked(); break;
        case 18: on_pbQuit_clicked(); break;
        case 19: on_pbAdd_clicked(); break;
        default: ;
        }
        _id -= 20;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
