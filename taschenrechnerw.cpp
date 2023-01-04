#include "taschenrechnerw.h"
#include <QVector>
#include <QtMath>
#include <QDebug>
#include <QRegExp>
#include <QPushButton>
#include <QLabel>


//Konstruktor
TaschenrechnerW::TaschenrechnerW(QWidget *parent): QMainWindow(parent),
screenNumber(0.0),
firstOperatorNumber(0.0),
secondOperatorNumber(0.0),
operationResult(0.0),
trackfirstInput(false),
trackOperationButton(),
trackTwoCLicksOperation(),
taschenrechnerAnzeige(new QLabel),
numberButton0(new QPushButton),
numberButton1(new QPushButton),
numberButton2(new QPushButton),
numberButton3(new QPushButton),
numberButton4(new QPushButton),
numberButton5(new QPushButton),
numberButton6(new QPushButton),
numberButton7(new QPushButton),
numberButton8(new QPushButton),
numberButton9(new QPushButton),
Box()
{
    //Nummernbuttons Slots

    connect(numberButton1, &QPushButton::released, this, &TaschenrechnerW::num_pressed);

    //Ausgabenmodifikationen

    //connect(ui->Vorzeichen,SIGNAL(released()),this,SLOT(singleNUmberOutputManipulation()));
    //connect(ui->gleich,SIGNAL(released()),this,SLOT(equalButton()));

    //mathematische Operationen

    //connect(ui->plus,SIGNAL(released()),this,SLOT(mathematicalOperations()));

    //ui->minus->setCheckable(true);
}

TaschenrechnerW::~TaschenrechnerW()
{
}

//Die Eingabe einer Nummer und Ausgabe auf der Anzeige

void TaschenrechnerW::num_pressed()
{
     QPushButton *button=(QPushButton*)sender();

     if((ui->plus->isChecked()||ui->minus->isChecked()||ui->mal->isChecked()||ui->teil->isChecked())&&(!this->trackfirstInput))
     {
         this->screenNumber=button->text().toDouble();
         this->trackfirstInput=true;
         this->trackTwoCLicksOperation="";
     }
     else
     {
        this->LCDZahl=(ui->Ausgabe->text()+button->text()).toDouble();
     }

     ui->Ausgabe->setText(QString::number(this->LCDZahl,'g',15));
}



void TaschenrechnerW::singleNUmberOutputManipulation()
{
    QPushButton *button=(QPushButton*)sender();

        //Vorzeichenwechsel

       if(button->text()=="-/+"){

            this->screenNumber=-1*(ui->Ausgabe->text()).toDouble();
            ui->Ausgabe->setText(QString::number(this->screenNumber,'g',15));
        }

       //Reset des Taschenrechners

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

       //Fließpunktzahl schreiben

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








