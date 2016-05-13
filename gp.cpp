#include "gp.h"
#include "ui_gp.h"
#include "QDebug"

gp::gp(QWidget *parent)
    : QWidget(parent), ui(new Ui::gp),cu(0),cg(0),tnu(0),tcp(0),no_of_courses(0),rowEdited(-1)
{

    ui->setupUi(this);


    connect(ui->courseUnit,SIGNAL(valueChanged(int)),
            this,SLOT(on_courseUnit_valueChanged()));

    connect(ui->courseGrade,SIGNAL(valueChanged(int)),
            this,SLOT(on_courseGrade_valueChanged()));

    connect(ui->pbQuit,SIGNAL(clicked()),this,SLOT(close()));

    connect(ui->cnLineEdit,SIGNAL(returnPressed()),this,SLOT(on_pbAdd_clicked()));

    //connect(ui->courseGrade,SIGNAL(editingFinished()),this,SLOT(on_pbAdd_clicked()));
    setWindowTitle("SIMPLE GP QALC                untitled.cgp");//5 tabs away
    setMode(addMode);

}

gp::~gp()
{
    delete ui;
}
void gp:: setMode(Mode newMode)
{
    //first set current mode to this mode
    currentMode=newMode;
    int number = gpMap.size();
    switch(currentMode){
    case addMode:
        ui->pbSaveEdit->hide();        
        ui->pbNext->setEnabled(true);
        ui->pbPrev->setEnabled(true);        
        ui->pbAdd->setEnabled(true);

        ui->saveBtn->setEnabled(number>=1);
        ui->pbSaveAs->setEnabled(number>=1);
        ui->pbEdit->setEnabled(number>=1);
        ui->pbRemove->setEnabled(number>=1);
        ui->pbExport->setEnabled(number>=1);

        ui->table->setSortingEnabled(false);
        break;


    case navMode:

        ui->pbAdd->setEnabled(true);
        ui->pbEdit->setEnabled(true);
        ui->pbRemove->setEnabled(true);
        ui->pbSaveEdit->hide();
        ui->pbPrev->setEnabled(true);
        ui->pbNext->setEnabled(true);


        ui->saveBtn->setEnabled(true);
        ui->pbClear->setEnabled(true);
        ui->pbExport->setEnabled(true);
        ui->pbSaveAs->setEnabled(true);
        ui->pbLoad->setEnabled(true);

        //ui->table->setSortingEnabled(true);
        break;
    case editMode:
        ui->pbAdd->setEnabled(false);
        ui->pbEdit->setEnabled(false);
        ui->pbRemove->setEnabled(false);
        ui->pbSaveEdit->show();
        ui->pbPrev->setEnabled(false);
        ui->pbNext->setEnabled(false);


        ui->saveBtn->setEnabled(false);
        ui->pbClear->setEnabled(false);
        ui->pbExport->setEnabled(false);
        ui->pbSaveAs->setEnabled(false);
        ui->pbLoad->setEnabled(false);

        ui->table->setSortingEnabled(false);

        break;
    }

}


void gp::on_pbAdd_clicked()
{
    QString cNameEntered;

    // this->setWindowModified(true);
    cNameEntered=ui->cnLineEdit->text();
    //validate user Input
    if(cNameEntered==""){
        QMessageBox::information(this,"Error !","Course Name not entered");
        return;
    }
    // to do ; check if a number was entered.

    //check if course name is not already used
    if(!gpMap.contains(cNameEntered)){
        cn=cNameEntered;
        cnPrevious=cn;

        QPair<int,int> cu_cgPair;
        cu_cgPair.first=cu;
        cu_cgPair.second=cg;
        gpMap.insert(cn,cu_cgPair);
        no_of_courses++;
        update_tnu_tcp(cu,cg);

        int rowNo=ui->table->rowCount();        
        updateTable(rowNo,cNameEntered,cu,cg);


        ui->cnLineEdit->setFocus(Qt::OtherFocusReason);
        ui->cnLineEdit->cursorBackward(true,cnPrevious.length());


        setMode(navMode);
    }
    else QMessageBox::information(this," Error ","This name has been used already, try again");
}
void gp::update_tnu_tcp(int&cuIn,int&cgIn){
    tnu+=cuIn;
    tcp+=(cuIn*cgIn);
    display_tnu_tcp_gpa(tnu,tcp);
}

void gp::display_tnu_tcp_gpa(int& tnu,int&tcp){
    if(tnu==0)gpa=0.0;
    else gpa=tcp/(double)tnu;

    //convert this numeric value to strings
    QString tcpText, tnuText, gpaText;
    tcp_tnu_gpaText( tcpText,  tnuText, gpaText);


    //set them to their lineEdits
    ui->tnulineEdit->setText(tnuText);
    ui->tcplineEdit->setText(tcpText);
    ui->gpaLineEdit->setText(gpaText);


    updateLcd();

}



void gp::on_courseUnit_valueChanged()
{
    cu=ui->courseUnit->value();

}

void gp::on_courseGrade_valueChanged()
{
    cg=ui->courseGrade->value();
}

void gp::on_pbQuit_clicked()
{

}

void gp::on_saveBtn_clicked()
{

    if (currFile.isEmpty()) {
        return on_pbSaveAs_clicked();
    } else {
        saveFile(currFile);
    }

}

void gp::on_pbSaveAs_clicked()
{

    QString fileSaveName= QFileDialog::getSaveFileName(this,"Save GP",QDir::homePath()+"/untitled.cgp","Grade Point Calc(*.cgp);;All Files(*)");

    //check if filename is empty
    if(fileSaveName.isEmpty()) return;
    else{
        saveFile(fileSaveName);
    }
}
bool gp::saveFile(const QString &fileName)

{
    QFile file(fileName);
    //try to open in writeonly (since we are saving)
    if(!file.open(QIODevice::WriteOnly)){
        //can't open inform user
        QMessageBox::information(this,"Error in Saving",file.errorString());
        return false;
    }
    QDataStream output(&file);
    output.setVersion(QDataStream::Qt_4_5);
    output<<gpMap;


    currFile = fileName;
    //setWindowModified(false);
    QString shownName = currFile;
    if (currFile.isEmpty())
        shownName = "untitled.cgp";
    //setWindowFilePath(shownName);
    this->setWindowTitle(shownName);
    return true;
}



void gp::updateTable(int& rowNo,const QString& cname, int& cunit, int& cgrade){


    // ui->table->setSortingEnabled(false);


    QString cuText = QString::number(cunit,10);
    QString cgText= QString::number(cgrade,10);

    ui->table->insertRow(rowNo);

    QTableWidgetItem *itemCol0 = new QTableWidgetItem(cname,0);
    itemCol0->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    ui->table->setItem(rowNo,0, itemCol0);


    QTableWidgetItem *itemCol1 = new QTableWidgetItem(cuText,0);
    itemCol1->setTextAlignment(Qt::AlignCenter);
    ui->table->setItem(rowNo,1, itemCol1);

    QTableWidgetItem *itemCol2 = new QTableWidgetItem(cgText,0);
    itemCol2->setTextAlignment(Qt::AlignCenter);
    ui->table->setItem(rowNo,2, itemCol2);

    //  ui->table->setSortingEnabled(true);

}

void gp::on_pbRemove_clicked()
{
    QString cnPresent;
    cnPresent=ui->cnLineEdit->text();
    if(currentMode==addMode || currentMode==navMode){
        if(gpMap.contains(cnPresent)){
            strPairMap_pt p = gpMap.find(cnPresent);
            int cuPresent=-(p.value().first);  //subtract that course unit from it
            int cgPrsent=(p.value().second);

            if(gpMap.size()==1){
                gpMap.remove(cnPresent);
                no_of_courses--;
                on_pbClear_clicked();
                return;
            }
            on_pbNext_clicked();
            gpMap.remove(cnPresent);//remove b4 updating, cos show text() would show cn (that was to be remved)
            //*there may be a beta way for this*/
                    QTableWidgetItem* editItem = ui->table->findItems(cnPresent,Qt::MatchFixedString).takeFirst();
            ui->table->removeRow(ui->table->row(editItem));

            no_of_courses--;
            update_tnu_tcp(cuPresent,cgPrsent);
            setMode(navMode);

        }
        else {
            QMessageBox::information(this,"Error !","Course Name doesn't exist");
            strPairMap_pt p = gpMap.find(cnPrevious);
            ui->cnLineEdit->setText(p.key());
            ui->courseUnit->setValue((p.value()).first);
            ui->courseGrade->setValue((p.value()).second);
        }
    }
    if(currentMode==editMode){

        if(gpMap.contains(cnPresent)){
            strPairMap_pt p = gpMap.find(cnPresent);
            int cuPresent=-(p.value().first);  //subtract that course unit from it
            int cgPresent=(p.value().second);

            gpMap.remove(cnPresent);

            QTableWidgetItem* editItem = ui->table->findItems(cnPresent,Qt::MatchFixedString).takeFirst();
            editItem->setTextColor( QColor("Red"));
            //
            rowEdited=ui->table->row(editItem);
            no_of_courses--;
            update_tnu_tcp(cuPresent,cgPresent);
        }
        else {
            QMessageBox::information(this,"Editing Error !","Course Name doesn't exist");
            setMode(addMode);
        }

    }
}



void gp::on_pbPrev_clicked()
{
    QString cnPresent;
    cnPresent=ui->cnLineEdit->text();
    //if we don't have that name, display previous
    if(!gpMap.contains(cnPresent)){
        strPairMap_pt p = gpMap.find(cnPrevious);
        if(p==gpMap.end())return;

        ui->cnLineEdit->setText(p.key());
        ui->courseUnit->setValue((p.value()).first);
        ui->courseGrade->setValue((p.value()).second);
        cnPrevious=p.key();

        return;
    }
    /*so its present*/
    strPairMap_pt p = gpMap.find(cnPresent);
    /*if (p == gpMap.begin()){

        QMessageBox::information(this,"Alert !","You've reached the end");
        return;
    }*/
    if(p==gpMap.begin())p=gpMap.end();
    p--;
    ui->cnLineEdit->setText(p.key());
    ui->courseUnit->setValue((p.value()).first);
    ui->courseGrade->setValue((p.value()).second);

    //find better way
    QTableWidgetItem* thisItem = ui->table->findItems(p.key(),Qt::MatchFixedString).takeFirst();
    thisItem->setTextColor(QColor("Blue"));

    if(cnPrevious!=NULL){

        QTableWidgetItem* prevItem = ui->table->findItems(cnPrevious,Qt::MatchFixedString).takeFirst();
        prevItem->setTextColor(QColor("Black"));
    }

    cnPrevious=p.key();
}

void gp::on_pbNext_clicked()
{
    QString cnPresent;
    cnPresent=ui->cnLineEdit->text();
    //if we don't have that name, display previous
    if(!gpMap.contains(cnPresent)){
        strPairMap_pt p = gpMap.find(cnPrevious);
        if(p==gpMap.end())return;
        ui->cnLineEdit->setText(p.key());
        ui->courseUnit->setValue((p.value()).first);
        ui->courseGrade->setValue((p.value()).second);
        cnPrevious=p.key();
        return;
    }
    strPairMap_pt p = gpMap.find(cnPresent);

    if(p!=gpMap.end())
        p++;
    /* if(p==gpMap.end()){

        QMessageBox::information(this,"Alert !","You've reached the end");
        return;
    }*/
    if(p==gpMap.end())p=gpMap.begin();
    ui->cnLineEdit->setText(p.key());
    ui->courseUnit->setValue((p.value()).first);
    ui->courseGrade->setValue((p.value()).second);
    //find better way
    QTableWidgetItem* thisItem = ui->table->findItems(p.key(),Qt::MatchFixedString).takeFirst();
    thisItem->setTextColor(QColor("Blue"));

    if(cnPrevious!=NULL){

        QTableWidgetItem* prevItem = ui->table->findItems(cnPrevious,Qt::MatchFixedString).takeFirst();
        prevItem->setTextColor(QColor("Black"));
    }


    cnPrevious=p.key();
}
void gp::set_all_toZero()
{
    cu=0;cg=0;tnu=0;tcp=0;gpa=0.0;
    no_of_courses=0;
    gpMap.clear();
    cn="";

}
void gp::clear_all()
{
    set_all_toZero();
    ui->cnLineEdit->clear();
    ui->gpaLineEdit->clear();
    ui->tcplineEdit->clear();
    ui->tnulineEdit->clear();
    ui->courseUnit->setValue(0);
    ui->courseGrade->setValue(0);
    ui->lnCounter->display(0);

    int rowCount=ui->table->rowCount();
    for(int i=rowCount;i>=0;i--){

        ui->table->removeRow(i);
        for(int j=0;j<3;j++)
            ui->table->removeCellWidget(i,j);
    }


}
void gp::on_pbClear_clicked()
{
    set_all_toZero();
    clear_all();
    setMode(addMode);
}

void gp::on_pbEdit_clicked()
{
    setMode(editMode);
    on_pbRemove_clicked();
}


void gp::on_pbSaveEdit_clicked()
{

    //ui->table->sortItems(0,Qt::AscendingOrder);
    ui->table->removeRow(rowEdited);

    on_pbAdd_clicked();
    setMode(addMode);

}
void gp::updateLcd(){
    ui->lnCounter->display(no_of_courses);
}

void gp::on_pbExport_clicked()
{

    ExportOption exportOption(this);
    exportOption.exec();
    if(exportOption.optionPicked==-1)return;
    else if(exportOption.optionPicked==1){
        exportToPdf();
    }
    else if(exportOption.optionPicked==2){
        exportToText();
    }


}

void gp::exportToText(void)
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("Export as Text file.."),"", tr("TXT files (*.txt)"));
    if (fileName.isEmpty())
        return;

    //    QString path( fileName );
    //    QFileInfo pathInfo(path);
    //    if(pathInfo.suffix()!="txt"){
    //
    //    }


    if (fileName.mid(fileName.size()-4,4) != ".txt")
        fileName = fileName + ".txt";
    QFile data(fileName);
    if (data.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream out(&data);
        QString tcpText, tnuText, gpaText;
        tcp_tnu_gpaText( tcpText,  tnuText, gpaText);        
        out<< qSetFieldWidth(30) << left <<"#COURSE NAMES"<< qSetFieldWidth(10) << left <<"UNIT"<<qSetFieldWidth(10) << left<<"GRADE"<<endl;





        strPairMap_pt p;

        for(p=gpMap.begin();p!=gpMap.end();++p)
        {
            out<<qSetFieldWidth(0)<<'\n';
            out<< qSetFieldWidth(30)<<left<<p.key()<<qSetFieldWidth(10)<<left<<p.value().first<<qSetFieldWidth(10)<< left<<p.value().second<<endl;
        }
        out<<qSetFieldWidth(0)<<endl<<endl;
        out<<qSetFieldWidth(20)<<left<<"#TOTAL UNITS"<<qSetFieldWidth(15)<<left<<"TOTAL POINTS"<<qSetFieldWidth(15) << left<<" GPA "<<endl;
        out<<qSetFieldWidth(0)<<endl;
        out<<"#"<<qSetFieldWidth(20)<<left<<tnuText<<qSetFieldWidth(15)<<left<<tcpText<<qSetFieldWidth(15)<<left<<gpaText<<endl;

    }

}

void gp::tcp_tnu_gpaText(QString& tcpText, QString& tnuText, QString& gpaText){
    tcpText = QString::number(tcp,10);
    tnuText = QString::number(tnu,10);
    QTextStream gpStream(&gpaText);
    gpStream.setRealNumberPrecision(3);
    gpStream<<gpa;
}

void gp::exportToPdf()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("Export as Pdf.."),"", tr("PDF files (*.pdf)"));
    if (fileName.isEmpty())
        return;
    if (fileName.mid(fileName.size()-4,4) != ".pdf")
        fileName = fileName + ".pdf";  
    QString html;
    html+=" <table border=\"1\" cellpadding=\"10\"  > <tr align=\"center\">     <th>COURSE NAME</th>      <th>UNIT</th>      <th>GRADE</th>     </tr>";
    strPairMap_pt p;
    short toggle=0;
    for(p=gpMap.begin();p!=gpMap.end();++p)
    {
        QString courseName =p.key();// Qt::escape(p.key());
        QString unit = QString::number(p.value().first,10);
        QString grade = QString::number(p.value().second,10);
        if(toggle^=1){
            html+="<tr bgcolor=\"lightgray\" > <td align=\"left\" >"+courseName+"</td>"
                  +"<td align=\"center\">"+unit+"</td>"
                  +"<td align=\"center\">"+grade+"</td> </tr>";
        }
        else{
            html+="<tr> <td align=\"left\" >"+courseName+"</td>"
                  +"<td align=\"center\">"+unit+"</td>"
                  +"<td align=\"center\">"+grade+"</td> </tr>";
        }
    }
    html+="<tr > <td align=\"center\" >TOTAL UNITS</td>"
          +QString("<td align=\"center\">TOTAL POINTS</td>")
          +QString("<td align=\"center\">GP</td> </tr>");
    QString tcpText, tnuText, gpaText;
    tcp_tnu_gpaText( tcpText,  tnuText, gpaText);
    html+="<tr > <td align=\"center\" >"+tnuText+"</td>"
          +"<td align=\"center\">"+tcpText+"</td>"
          +"<td align=\"center\">"+gpaText+"</td> </tr>";
    html+=" </table>\n<br>\n ";
    //qDebug()<<html;
    QPrinter printer;

    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    printer.setFullPage(true);
    printer.setOrientation(QPrinter::Portrait);
    printer.setPaperSize(QPrinter::A4);    
    QTextDocument textDocument;
    textDocument.setHtml(html);
    textDocument.print(&printer);



}

void gp::on_pbLoad_clicked()
{

    QString fileOpenName= QFileDialog::getOpenFileName(this,"open txt file",QDir::homePath(),"Text(*.txt);;All Files(*)");

    QFile file(fileOpenName);

    if ( file.open( QIODevice::ReadOnly ) ) {
        clear_all();
        QTextStream stream( &file );
        QString line;

        while ( !stream.atEnd() ) {
            line = stream.readLine();
            if(line.startsWith('#'))continue;
            else{
                processText(line);
            }
        }
        file.close();
    }

}

void gp::enterValues(QString& cNameEntered, int cu, int cg){



    if(!gpMap.contains(cNameEntered)){
        cn=cNameEntered;
        cnPrevious=cn;

        QPair<int,int> cu_cgPair;
        cu_cgPair.first=cu;
        cu_cgPair.second=cg;
        gpMap.insert(cn,cu_cgPair);
        no_of_courses++;
        update_tnu_tcp(cu,cg);

        ui->cnLineEdit->setText(cNameEntered);
        ui->courseUnit->setValue(cu);
        ui->courseGrade->setValue(cg);

        int rowNo=ui->table->rowCount();
        updateTable(rowNo,cNameEntered,cu,cg);


        ui->cnLineEdit->setFocus(Qt::OtherFocusReason);
        ui->cnLineEdit->cursorBackward(true,cNameEntered.length());


        setMode(navMode);
    }



}

void gp::processText(QString& line){

    qDebug()<<line;
    QRegExp rx("[\\s]+");   
    QStringList lineList=line.split(rx);
    // qDebug()<<lineList.size();
    if(lineList.size()<3)return;
    QString cuText,cgText,cname;

    cname= lineList.at(0);
    cuText= lineList.at(1);
    cgText= lineList.at(2);

    bool ok;

    enterValues(cname,cuText.toInt(&ok,10),cgText.toInt(&ok,10));

}

void gp::on_pbOpen_clicked()
{

    QString fileOpenName= QFileDialog::getOpenFileName(this,"Load cgp file",QDir::homePath(),"Grade Point Calc(*.cgp);;All Files(*)");
    currFile=fileOpenName;
    QString path( fileOpenName );
    QFileInfo pathInfo(path);


    //check if filename is empty
    if(fileOpenName.isEmpty()) return;
    else{//we create a QFile
        QFile file(fileOpenName);
        if(!file.open(QIODevice::ReadOnly)){
            QMessageBox::information(this,"Error in loading",file.errorString());
            return;
        }
        QString fileName = pathInfo.fileName();
        fileName ="Simple GP Qalc               "+fileName;
        this->setWindowTitle(fileName);
        QDataStream input(&file);
        input.setVersion(QDataStream::Qt_4_5);

        //empty existing contact cu,cg,tnu etc
        clear_all();
        input>>gpMap;
    }
    //check if this new gpMap is empty and notify user, if it is
    if (gpMap.isEmpty()) {
        QMessageBox::information(this, tr("Nothing in file"),
                                 tr("The file you are attempting to open contains nothing."));
    } else {//iterate thru it and set to nav Mode 4 appropriate buttons
        strPairMap_pt p;

        int rowNo =0;
        for(p=gpMap.begin();p!=gpMap.end();++p,rowNo++)
        {
            tnu+=(p.value()).first; //add up the cu
            tcp+=((p.value()).first)*((p.value()).second); //add up cu*cg
            no_of_courses++;

            /*create the table rows*/
            updateTable(rowNo,p.key(),p.value().first,p.value().second);

        }

        //display first info
        p= gpMap.begin();
        cnPrevious=p.key(); //needed,in case Remove or Edit was pressed with an unknown cn in cnLineEdit
        ui->cnLineEdit->setText(p.key());
        ui->courseUnit->setValue((p.value()).first);
        ui->courseGrade->setValue((p.value()).second);

        display_tnu_tcp_gpa(tnu,tcp);
    }
    setMode(addMode);
}
