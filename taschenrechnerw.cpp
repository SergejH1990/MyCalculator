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
    trackButton=false;
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
      }


     ui->Ausgabe->setText(QString::number(this->LCDZahl,'g',15));

}




//Dezimalzeichen in Zahl einfügen

void TaschenrechnerW::on_dezi_released()
{
    QRegExp rx("[.]");
    if(-1==rx.indexIn(ui->Ausgabe->text()))
        ui->Ausgabe->setText(ui->Ausgabe->text()+".");

}

void TaschenrechnerW::ausgabeManipulation()
{
    QPushButton *button=(QPushButton*)sender();

       if(button->text()=="-/+"){

            this->LCDZahl=-1*(ui->Ausgabe->text()).toDouble();
            ui->Ausgabe->setText(QString::number(this->LCDZahl,'g',15));
        }

       if(button->text()=="Del"){

            this->LCDZahl=0;
            this->ersteZahl=0;
            ui->Ausgabe->setText(QString::number(this->LCDZahl,'g',15));
            ui->plus->setChecked(false);
            ui->minus->setChecked(false);
            ui->mal->setChecked(false);
            ui->teil->setChecked(false);
        }


}

void TaschenrechnerW::istGleich(){



    if(ui->plus->isChecked()){
          this->ergebnis=this->ersteZahl+this->LCDZahl;
          ui->Ausgabe->setText(QString::number(this->ergebnis,'g',15));

          ui->plus->setChecked(false);
    }

    else if(ui->minus->isChecked()){
        this->ergebnis=this->ersteZahl-this->LCDZahl;
        ui->Ausgabe->setText(QString::number(this->ergebnis,'g',15));
        ui->minus->setChecked(false);

    }

    else if(ui->mal->isChecked()){
        this->ergebnis=this->ersteZahl*this->LCDZahl;
        ui->Ausgabe->setText(QString::number(this->ergebnis,'g',15));
        ui->mal->setChecked(false);

    }

    else if(ui->teil->isChecked()){
        this->ergebnis=this->ersteZahl/this->LCDZahl;
        ui->Ausgabe->setText(QString::number(this->ergebnis,'g',15));
        ui->teil->setChecked(false);

    }

    this->trackButton=false;


}


void TaschenrechnerW::operationen()
{
    QPushButton *button=(QPushButton*)sender();

    this->ersteZahl=(ui->Ausgabe->text()).toDouble();
    this->LCDZahl=0;
    ui->Ausgabe->setText(QString::number(this->LCDZahl,'g',15));

    button->setChecked(true);



}







