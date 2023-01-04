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



void TaschenrechnerW::ausgabeManipulation()
{
    QPushButton *button=(QPushButton*)sender();

        //Vorzeichenwechsel

       if(button->text()=="-/+"){

            this->LCDZahl=-1*(ui->Ausgabe->text()).toDouble();
            ui->Ausgabe->setText(QString::number(this->LCDZahl,'g',15));
        }

       //Reset des Taschenrechners

        else if(button->text()=="Del"){

            this->LCDZahl=0;
            this->ersteZahl=0;
            this->zweiteZahl=0;
            this->ergebnis=0;
            this->operation="";
            this->operation2="";
            ui->Ausgabe->setText(QString::number(this->LCDZahl,'g',15));
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

void TaschenrechnerW::istGleich(){

    this->zweiteZahl=this->LCDZahl;

    if(ui->plus->isChecked()){
          this->ergebnis=this->ersteZahl+this->zweiteZahl;

    }

    else if(ui->minus->isChecked()){
        this->ergebnis=this->ersteZahl-this->zweiteZahl;


    }

    else if(ui->mal->isChecked()){
        this->ergebnis=this->ersteZahl*this->zweiteZahl;


    }

    else if(ui->teil->isChecked()){

        if(this->zweiteZahl!=0)
        this->ergebnis=this->ersteZahl/this->zweiteZahl;
        else
        {
        this->Box.setText("Division through zero not allowed");
        this->Box.exec();
        }


    }

    ui->Ausgabe->setText(QString::number(this->ergebnis,'g',15));
    this->trackButton=false;
    this->operation="";
    this->operation2="";
    ui->plus->setChecked(false);
    ui->minus->setChecked(false);
    ui->mal->setChecked(false);
    ui->teil->setChecked(false);


}

//Ausführung der mathematischen Operationenknöpfe

void TaschenrechnerW::operationen()
{
    QPushButton *button=(QPushButton*)sender();



    if(this->operation==""){

        this->ersteZahl=(ui->Ausgabe->text()).toDouble();


    }
    else if (this->operation!=this->operation2){

        this->zweiteZahl=this->LCDZahl;
        switch (this->Mathe.indexOf(operation)) {
        case 0:
            this->ergebnis=this->ersteZahl+this->zweiteZahl;
            break;
        case 1:
            this->ergebnis=this->ersteZahl-this->zweiteZahl;
            break;
        case 2:
            this->ergebnis=this->ersteZahl*this->zweiteZahl;

            break;
        case 3:
            if(this->zweiteZahl!=0)
            this->ergebnis=this->ersteZahl/this->zweiteZahl;
            else
           {
                this->Box.setText("Division through zero not allowed");
                this->Box.exec();
           }
            break;
         }

        ui->Ausgabe->setText(QString::number(this->ergebnis,'g',15));
        this->ersteZahl=this->ergebnis;




    }
    this->operation=this->operation2+button->text();
    button->setChecked(true);
    this->trackButton=false;
    this->operation2=button->text();




}








