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
    LCDZahl=0;
    ersteZahl=0;
    zweiteZahl=0;
    trackButton=false;
    operation="";
    operation2="";
    ergebnis=0;


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

    connect(ui->Vorzeichen,SIGNAL(released()),this,SLOT(ausgabeManipulation()));
    connect(ui->del,SIGNAL(released()),this,SLOT(ausgabeManipulation()));
    connect(ui->dezi,SIGNAL(released()),this,SLOT(ausgabeManipulation()));

    connect(ui->gleich,SIGNAL(released()),this,SLOT(istGleich()));

    //mathematische Operationen

    connect(ui->plus,SIGNAL(released()),this,SLOT(operationen()));
    connect(ui->minus,SIGNAL(released()),this,SLOT(operationen()));
    connect(ui->mal,SIGNAL(released()),this,SLOT(operationen()));
    connect(ui->teil,SIGNAL(released()),this,SLOT(operationen()));

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



     if((ui->plus->isChecked()||ui->minus->isChecked()||ui->mal->isChecked()||ui->teil->isChecked())&&(!this->trackButton)){
         this->LCDZahl=button->text().toDouble();
         this->trackButton=true;
         this->operation2="";
     }
     else{
        this->LCDZahl=(ui->Ausgabe->text()+button->text()).toDouble();

      }


     ui->Ausgabe->setText(QString::number(this->LCDZahl,'g',15));

}


//Vorzeichenwechsel, Reset des Taschenrechners und Fließpunktzahl schreiben

void TaschenrechnerW::ausgabeManipulation()
{
    QPushButton *button=(QPushButton*)sender();

       if(button->text()=="-/+"){

            this->LCDZahl=-1*(ui->Ausgabe->text()).toDouble();
            ui->Ausgabe->setText(QString::number(this->LCDZahl,'g',15));
        }
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








