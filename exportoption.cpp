#include "exportoption.h"
#include "ui_exportoption.h"

ExportOption::ExportOption(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExportOption)
{
    ui->setupUi(this);
    ui->buttonGroup->setId(ui->radioButton1,1);
    ui->buttonGroup->setId(ui->radioButton2,2);
    connect(ui->buttonGroup,SIGNAL(buttonClicked(int)),this,SLOT( buttonSelected()));
    optionPicked=-1;



}

ExportOption::~ExportOption()
{
    delete ui;
}

void ExportOption::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void ExportOption::buttonSelected(){
     optionPicked = ui->buttonGroup->checkedId();
}

void ExportOption::on_buttonBox_accepted()
{
   // this->close();
}

void ExportOption::on_buttonBox_rejected()
{
    optionPicked=-1;
   // this->close();
}
