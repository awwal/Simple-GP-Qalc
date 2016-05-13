#ifndef EXPORTOPTION_H
#define EXPORTOPTION_H

#include <QDialog>

namespace Ui {
    class ExportOption;
}

class ExportOption : public QDialog {
    Q_OBJECT
public:
    ExportOption(QWidget *parent = 0);
    ~ExportOption();
    int optionPicked;

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ExportOption *ui;


private slots:
    void on_buttonBox_rejected();
    void on_buttonBox_accepted();
    void buttonSelected();
};

#endif // EXPORTOPTION_H
