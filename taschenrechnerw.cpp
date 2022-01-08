#include "taschenrechnerw.h"
#include "ui_taschenrechnerw.h"
#include <QVector>
#include <QtMath>
#include <QDebug>
#include <QRegExp>


//Konstruktor
TaschenrechnerW::TaschenrechnerW(QWidget *parent): QMainWindow(parent)
    , ui(new Ui::TaschenrechnerW)
{
    LCDZahl=0;
    ersteZahl=0;
    zweiteZahl=0;
    trackButton=false;
    operation="";
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


//Die Eingabe einer Nummer eines Buttons und Ausgabe auf der Anzeige

void TaschenrechnerW::num_pressed()
{
     QPushButton *button=(QPushButton*)sender();



     if((ui->plus->isChecked()||ui->minus->isChecked()||ui->mal->isChecked()||ui->teil->isChecked())&&(!this->trackButton)){
         this->LCDZahl=button->text().toDouble();
         this->trackButton=true;
     }
     else{
        this->LCDZahl=(ui->Ausgabe->text()+button->text()).toDouble();
        this->trackButton=false;
      }


     ui->Ausgabe->setText(QString::number(this->LCDZahl,'g',15));

}



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


void TaschenrechnerW::istGleich(){

    this->zweiteZahl=ui->Ausgabe->text().toDouble();

    if(ui->plus->isChecked()){
          this->ergebnis=this->ersteZahl+this->zweiteZahl;
          ui->plus->setChecked(false);
    }

    else if(ui->minus->isChecked()){
        this->ergebnis=this->ersteZahl-this->zweiteZahl;
        ui->minus->setChecked(false);

    }

    else if(ui->mal->isChecked()){
        this->ergebnis=this->ersteZahl*this->zweiteZahl;
        ui->mal->setChecked(false);

    }

    else if(ui->teil->isChecked()){
        this->ergebnis=this->ersteZahl/this->zweiteZahl;;
        ui->teil->setChecked(false);

    }

    ui->Ausgabe->setText(QString::number(this->ergebnis,'g',15));
    this->trackButton=false;


}


void TaschenrechnerW::operationen()
{
    QPushButton *button=(QPushButton*)sender();
    QString operation="";
    QStringList Mathe;
    Mathe<<"+"<<"-"<<"x"<<"/";

    if(this->trackButton==false){

        this->ersteZahl=(ui->Ausgabe->text()).toDouble();

    }
    else{
        this->zweiteZahl=ui->Ausgabe->text().toDouble();
        switch (Mathe.indexOf(operation)) {
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
            this->ergebnis=this->ersteZahl/this->zweiteZahl;
            break;
         }

        ui->Ausgabe->setText(QString::number(this->ergebnis,'g',15));
        this->ersteZahl=this->ergebnis;
        this->trackButton=false;



    }
    operation=button->text();
    button->setChecked(true);




}








