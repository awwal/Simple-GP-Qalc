#ifndef GP_H
#define GP_H

#include <QtGui/QWidget>
#include <QMap>
#include <QPair>
#include <QTextStream>
#include <QVariant>
#include<QMessageBox>
#include<QFileDialog>
#include <QColor>
#include <QPrinter>
#include <QPainter>
#include "exportoption.h"
#include "QTextDocument"

#include "QPrintDialog"

class QRegExp;
typedef QMap<QString, QPair<int,int> > strPairMap_t;
typedef strPairMap_t::iterator strPairMap_pt;

enum Mode {editMode,navMode,addMode};


namespace Ui
{
    class gp;
}

class gp : public QWidget
{
    Q_OBJECT

public:
    gp(QWidget *parent = 0);
    ~gp();

private:
    Ui::gp *ui;
    int cu,cg;
    int tnu;
    int tcp;
    int no_of_courses;
    double gpa;
    QString cn,cnPrevious;
    QString currFile;
    Mode currentMode;
    strPairMap_t gpMap;
    int rowEdited;
    bool saveFile(const QString &fileName);
    void updateTable(int& rowNo, const QString& cname, int& cunit, int& cgrade);
    void tcp_tnu_gpaText(QString& tcpText, QString& tnuText, QString& gpaText);
    void exportToPdf(void);
    void exportToText(void);
    void processText(QString& );
    void enterValues(QString& cname, int cu, int cg);
    ExportOption exportOption;


public slots:

    void on_courseGrade_valueChanged();
    void on_courseUnit_valueChanged();
    void updateLcd();
    void update_tnu_tcp(int&cu,int&cg);
    void display_tnu_tcp_gpa(int& tnu,int& tcp);
    void clear_all();
    void set_all_toZero();
    void setMode(Mode newMode);


private slots:

    void on_pbOpen_clicked();
    void on_saveBtn_clicked();
    void on_pbExport_clicked();
    void on_pbSaveEdit_clicked();
    void on_pbEdit_clicked();
    void on_pbClear_clicked();
    void on_pbNext_clicked();
    void on_pbPrev_clicked();
    void on_pbRemove_clicked();
    void on_pbLoad_clicked();
    void on_pbSaveAs_clicked();
    void on_pbQuit_clicked();
    void on_pbAdd_clicked();

};

#endif // GP_H
