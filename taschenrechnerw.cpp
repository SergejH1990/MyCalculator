#include "taschenrechnerw.h"
#include <QVector>
#include <QtMath>
#include <QDebug>
#include <QRegExp>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>


//Konstruktor
TaschenrechnerW::TaschenrechnerW(QWidget *parent): QMainWindow(parent),
taschenrechnerWidget(new QWidget),
taschenrechnerAnzeige(new QLabel),
verticalLayout(new QVBoxLayout),
buttonRow1(new QHBoxLayout),
buttonRow2(new QHBoxLayout),
buttonRow3(new QHBoxLayout),
buttonRow4(new QHBoxLayout),
numberButtons(),
plusButton(new QPushButton),
minusButton(new QPushButton),
multiplyButton(new QPushButton),
divideButton(new QPushButton),
signChangeButton(new QPushButton),
equalButton(new QPushButton),
screenNumber(0.0),
firstOperatorNumber(0.0),
secondOperatorNumber(0.0),
trackfirstInput(false),
operationResult(0.0),
trackOperationButton(),
trackTwoCLicksOperation(),
Box()
{
    //Set text of buttons
    for (int buttonNumber=0; buttonNumber < (int)numberButtons.size(); buttonNumber++)
    {
        numberButtons[buttonNumber] = new QPushButton();
        numberButtons[buttonNumber]->setText(QString::number(buttonNumber));
        connect(numberButtons[buttonNumber],&QPushButton::released, this, &TaschenrechnerW::num_pressed);
    }

    plusButton->setText("+");
    minusButton->setText("-");
    multiplyButton->setText("*");
    divideButton->setText("/");
    signChangeButton->setText("+/-");
    equalButton->setText("=");

    //Layout of buttons and label
    verticalLayout->addWidget(taschenrechnerAnzeige);
    verticalLayout->addLayout(buttonRow1);
    verticalLayout->addLayout(buttonRow2);
    verticalLayout->addLayout(buttonRow3);
    verticalLayout->addLayout(buttonRow4);

    buttonRow1->addWidget(numberButtons[1]);
    buttonRow1->addWidget(numberButtons[2]);
    buttonRow1->addWidget(numberButtons[3]);
    buttonRow1->addWidget(plusButton);
    buttonRow2->addWidget(numberButtons[4]);
    buttonRow2->addWidget(numberButtons[5]);
    buttonRow2->addWidget(numberButtons[6]);
    buttonRow2->addWidget(minusButton);
    buttonRow3->addWidget(numberButtons[7]);
    buttonRow3->addWidget(numberButtons[8]);
    buttonRow3->addWidget(numberButtons[9]);
    buttonRow3->addWidget(multiplyButton);
    buttonRow4->addWidget(signChangeButton);
    buttonRow4->addWidget(numberButtons[0]);
    buttonRow4->addWidget(equalButton);
    buttonRow4->addWidget(divideButton);

    taschenrechnerWidget->setLayout(verticalLayout);
    setCentralWidget(taschenrechnerWidget);

    //Initialize label
    taschenrechnerAnzeige->setText("0");
    taschenrechnerAnzeige->setAlignment(Qt::AlignRight);
    taschenrechnerAnzeige->setStyleSheet("QLabel{font-size: 20px; background: yellow;}");

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
     /*if((ui->plus->isChecked()||ui->minus->isChecked()||ui->mal->isChecked()||ui->teil->isChecked())&&(!this->trackfirstInput))
     {
         this->screenNumber=button->text().toDouble();
         this->trackfirstInput=true;
         this->trackTwoCLicksOperation="";
     }
     else
     {
        this->LCDZahl=(ui->Ausgabe->text()+button->text()).toDouble();
     }

     ui->Ausgabe->setText(QString::number(this->LCDZahl,'g',15));*/
}



void TaschenrechnerW::singleNUmberOutputManipulation()
{
/*
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

       }*/
}


//Ausführung des Gleichheitsknopfes

void TaschenrechnerW::evaluateResult(){

    /*this->zweiteZahl=this->LCDZahl;

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
    ui->teil->setChecked(false);*/
}

//Ausführung der mathematischen Operationenknöpfe

void TaschenrechnerW::mathematicalOperations()
{
    /*if(this->operation==""){

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
    this->operation2=button->text();*/
}
