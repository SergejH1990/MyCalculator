#include "taschenrechnerw.h"
#include "ui_taschenrechnerw.h"
#include <QVector>
#include <QtMath>
#include <QDebug>
#include <QRegExp>
#include <QMessageBox>


//Konstruktor
TaschenrechnerW::TaschenrechnerW(QWidget *parent): QMainWindow(parent)
    , ui(new Ui::TaschenrechnerW)
{
    screenNumber=0;
    firstOperatorNumber=0;
    secondOperatorNumber=0;
    trackfirstInput=false;
    trackOperationButton="";
    trackTwoCLicksOperation="";
    operationResult=0;


    ui->setupUi(this);


    //Nummernbuttons Slots

    connect(ui->eins,SIGNAL(released()),this,SLOT(num_pressed()));
    connect(ui->zwei,SIGNAL(released()),this,SLOT(num_pressed()));
    connect(ui->drei,SIGNAL(released()),this,SLOT(num_pressed()));
    connect(ui->vier,SIGNAL(released()),this,SLOT(num_pressed()));
    connect(ui->fuenf,SIGNAL(released()),this,SLOT(num_pressed()));
    connect(ui->sechs,SIGNAL(released()),this,SLOT(num_pressed()));
    connect(ui->sieben,SIGNAL(released()),this,SLOT(num_pressed()));
    connect(ui->acht,SIGNAL(released()),this,SLOT(num_pressed()));
    connect(ui->neun,SIGNAL(released()),this,SLOT(num_pressed()));
    connect(ui->nulli,SIGNAL(released()),this,SLOT(num_pressed()));

    //Ausgabenmodifikationen

    connect(ui->Vorzeichen,SIGNAL(released()),this,SLOT(singleNUmberOutputManipulation()));
    connect(ui->del,SIGNAL(released()),this,SLOT(singleNUmberOutputManipulation()));
    connect(ui->dezi,SIGNAL(released()),this,SLOT(singleNUmberOutputManipulation()));

    connect(ui->gleich,SIGNAL(released()),this,SLOT(equalButton()));

    //mathematische Operationen

    connect(ui->plus,SIGNAL(released()),this,SLOT(mathematicalOperations()));
    connect(ui->minus,SIGNAL(released()),this,SLOT(mathematicalOperations()));
    connect(ui->mal,SIGNAL(released()),this,SLOT(mathematicalOperations()));
    connect(ui->teil,SIGNAL(released()),this,SLOT(mathematicalOperations()));

    ui->minus->setCheckable(true);
    ui->plus->setCheckable(true);
    ui->mal->setCheckable(true);
    ui->teil->setCheckable(true);


}

TaschenrechnerW::~TaschenrechnerW()
{
    delete ui;
}


//Die Eingabe einer Nummer und Ausgabe auf der Anzeige

void TaschenrechnerW::num_pressed()
{
     QPushButton *button=(QPushButton*)sender();



     if((ui->plus->isChecked()||ui->minus->isChecked()||ui->mal->isChecked()||ui->teil->isChecked())&&(!this->trackfirstInput)){
         this->screenNumber=button->text().toDouble();
         this->trackfirstInput=true;
         this->trackTwoCLicksOperation="";
     }
     else{
        this->screenNumber=(ui->Ausgabe->text()+button->text()).toDouble();

      }


     ui->Ausgabe->setText(QString::number(this->screenNumber,'g',15));

}


//Vorzeichenwechsel, Reset des Taschenrechners und Fließpunktzahl schreiben

void TaschenrechnerW::singleNUmberOutputManipulation()
{
    QPushButton *button=(QPushButton*)sender();

       if(button->text()=="-/+"){

            this->screenNumber=-1*(ui->Ausgabe->text()).toDouble();
            ui->Ausgabe->setText(QString::number(this->screenNumber,'g',15));
        }
        else if(button->text()=="Del"){

           this->screenNumber=0;
           this->firstOperatorNumber=0;
           this->secondOperatorNumber=0;
           this->trackfirstInput=false;
           this->trackOperationButton="";
           this->trackTwoCLicksOperation="";
           this->operationResult=0;
            ui->Ausgabe->setText(QString::number(this->screenNumber,'g',15));
            ui->plus->setChecked(false);
            ui->minus->setChecked(false);
            ui->mal->setChecked(false);
            ui->teil->setChecked(false);
        }
       else if(button->text()=="."){

           QRegExp rx("[.]");
           if(-1==rx.indexIn(ui->Ausgabe->text()))
           ui->Ausgabe->setText(ui->Ausgabe->text()+".");

       }


}


//Ausführung des Gleichheitsknopfes

void TaschenrechnerW::equalButton(){

    this->secondOperatorNumber=this->screenNumber;

    if(ui->plus->isChecked()){
          this->operationResult=this->firstOperatorNumber+this->secondOperatorNumber;

    }

    else if(ui->minus->isChecked()){
        this->operationResult=this->firstOperatorNumber-this->secondOperatorNumber;


    }

    else if(ui->mal->isChecked()){
        this->operationResult=this->firstOperatorNumber*this->secondOperatorNumber;


    }

    else if(ui->teil->isChecked()){

        if(this->secondOperatorNumber!=0)
        this->operationResult=this->firstOperatorNumber/this->secondOperatorNumber;
        else
        {
        this->Box.setText("Division through zero not allowed");
        this->Box.exec();
        }


    }

    ui->Ausgabe->setText(QString::number(this->operationResult,'g',15));
    this->trackfirstInput=false;
    this->trackOperationButton="";
    this->trackTwoCLicksOperation="";
    ui->plus->setChecked(false);
    ui->minus->setChecked(false);
    ui->mal->setChecked(false);
    ui->teil->setChecked(false);


}

//Ausführung der mathematischen Operationenknöpfe

void TaschenrechnerW::mathematicalOperations()
{
    QPushButton *button=(QPushButton*)sender();



    if(this->trackOperationButton==""){

        this->firstOperatorNumber=(ui->Ausgabe->text()).toDouble();


    }
    else if (this->trackOperationButton!=this->trackTwoCLicksOperation){

        this->secondOperatorNumber=this->screenNumber;
        switch (this->MATH_OPERATIONS_LIST.indexOf(trackOperationButton)) {
        case 0:
            this->operationResult=this->firstOperatorNumber+this->secondOperatorNumber;
            break;
        case 1:
            this->operationResult=this->firstOperatorNumber-this->secondOperatorNumber;
            break;
        case 2:
            this->operationResult=this->firstOperatorNumber*this->secondOperatorNumber;

            break;
        case 3:
            if(this->secondOperatorNumber!=0)
            this->operationResult=this->firstOperatorNumber/this->secondOperatorNumber;
            else
           {
                this->Box.setText("Division through zero not allowed");
                this->Box.exec();
           }
            break;
         }

        ui->Ausgabe->setText(QString::number(this->operationResult,'g',15));
        this->firstOperatorNumber=this->operationResult;




    }
    this->trackOperationButton=this->trackTwoCLicksOperation+button->text();
    button->setChecked(true);
    this->trackfirstInput=false;
    this->trackTwoCLicksOperation=button->text();




}








