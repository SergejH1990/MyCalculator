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
calculatorWidget(new QWidget),
calculatorDisplay(new QLabel),
verticalLayout(new QVBoxLayout),
buttonRow0(new QHBoxLayout),
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
deleteButton(new QPushButton),
commaButton(new QPushButton),
screenNumber(0.0),
firstOperatorNumber(0.0),
secondOperatorNumber(0.0),
trackfirstInput(false),
operationResult(0.0),
trackOperationButton(MathOperationList::None),
Box()
{
    //Set text of buttons
    for (int buttonNumber=0; buttonNumber < (int)numberButtons.size(); buttonNumber++)
    {
        numberButtons[buttonNumber] = new QPushButton();
        numberButtons[buttonNumber]->setText(QString::number(buttonNumber));
        connect(numberButtons[buttonNumber], &QPushButton::released, this, &TaschenrechnerW::numberButtonPressed);
    }

    plusButton->setText("+");
    minusButton->setText("-");
    multiplyButton->setText("*");
    divideButton->setText("/");
    signChangeButton->setText("+/-");
    equalButton->setText("=");
    deleteButton->setText("Del");
    commaButton->setText(".");

    //Layout of buttons and label
    verticalLayout->addWidget(calculatorDisplay);
    verticalLayout->addLayout(buttonRow0);
    verticalLayout->addLayout(buttonRow1);
    verticalLayout->addLayout(buttonRow2);
    verticalLayout->addLayout(buttonRow3);
    verticalLayout->addLayout(buttonRow4);
    verticalLayout->setSpacing(0);

    buttonRow0->addWidget(deleteButton);
    buttonRow0->addWidget(commaButton);
    buttonRow0->setSpacing(0);
    buttonRow1->addWidget(numberButtons[1]);
    buttonRow1->addWidget(numberButtons[2]);
    buttonRow1->addWidget(numberButtons[3]);
    buttonRow1->addWidget(plusButton);
    buttonRow1->setSpacing(0);
    buttonRow2->addWidget(numberButtons[4]);
    buttonRow2->addWidget(numberButtons[5]);
    buttonRow2->addWidget(numberButtons[6]);
    buttonRow2->addWidget(minusButton);
    buttonRow2->setSpacing(0);
    buttonRow3->addWidget(numberButtons[7]);
    buttonRow3->addWidget(numberButtons[8]);
    buttonRow3->addWidget(numberButtons[9]);
    buttonRow3->addWidget(multiplyButton);
    buttonRow3->setSpacing(0);
    buttonRow4->addWidget(signChangeButton);
    buttonRow4->addWidget(numberButtons[0]);
    buttonRow4->addWidget(equalButton);
    buttonRow4->addWidget(divideButton);
    buttonRow4->setSpacing(0);

    calculatorWidget->setLayout(verticalLayout);
    setCentralWidget(calculatorWidget);

    //Initialize label
    calculatorDisplay->setText("0");
    calculatorDisplay->setAlignment(Qt::AlignRight);
    calculatorDisplay->setStyleSheet("QLabel{font-size: 20px; background: yellow;}");

    //Ausgabenmodifikationen

    connect(signChangeButton, &QPushButton::released, this, &TaschenrechnerW::singleOutputManipulation);
    connect(deleteButton, &QPushButton::released, this, &TaschenrechnerW::singleOutputManipulation);
    connect(commaButton, &QPushButton::released, this, &TaschenrechnerW::singleOutputManipulation);

    //mathematische Operationen
    connect(plusButton, &QPushButton::released, this, &TaschenrechnerW::mathematicalOperation);
    connect(minusButton, &QPushButton::released, this, &TaschenrechnerW::mathematicalOperation);
    connect(multiplyButton, &QPushButton::released, this, &TaschenrechnerW::mathematicalOperation);
    connect(divideButton, &QPushButton::released, this, &TaschenrechnerW::mathematicalOperation);

    connect(equalButton, &QPushButton::released, this, &TaschenrechnerW::evaluateResult);

    plusButton->setCheckable(true);
    minusButton->setCheckable(true);
    multiplyButton->setCheckable(true);
    divideButton->setCheckable(true);
}

TaschenrechnerW::~TaschenrechnerW()
{
}

void TaschenrechnerW::numberButtonPressed()
{
    QPushButton* button = (QPushButton*)sender();

    if((plusButton->isChecked() || minusButton->isChecked() || multiplyButton->isChecked() || divideButton->isChecked()) && !trackfirstInput)
    {
         screenNumber = button->text().toDouble();
         trackfirstInput = true;
     }
     else
     {
        screenNumber = (calculatorDisplay->text() + button->text()).toDouble();
     }

     calculatorDisplay->setText(QString::number(screenNumber,'g',15));
}

void TaschenrechnerW::singleOutputManipulation()
{
    QPushButton* button = (QPushButton*)sender();

    if(button->text() == "+/-")
    {
        screenNumber = -1 * calculatorDisplay->text().toDouble();
        calculatorDisplay->setText(QString::number(screenNumber,'g',15));
    }
    else if(button->text() == "Del")
    {
        screenNumber = 0;
        firstOperatorNumber = 0;
        secondOperatorNumber = 0;
        operationResult = 0;
        calculatorDisplay->setText(QString::number(screenNumber,'g',15));
        resetButtons();
    }
    else if(button->text() == ".")
    {
        QRegExp rx("[.]");

        if(-1 == rx.indexIn(calculatorDisplay->text()))
        {
            calculatorDisplay->setText(calculatorDisplay->text() + ".");
        }
    }
}

void TaschenrechnerW::evaluateResult()
{
    secondOperatorNumber = screenNumber;

    if(trackOperationButton == MathOperationList::Plus)
    {
        operationResult = firstOperatorNumber + secondOperatorNumber;
    }
    else if(trackOperationButton == MathOperationList::Minus)
    {
        operationResult = firstOperatorNumber - secondOperatorNumber;
    }
    else if(trackOperationButton == MathOperationList::Multiply)
    {
        operationResult = firstOperatorNumber * secondOperatorNumber;
    }
    else if(trackOperationButton == MathOperationList::Divide)
    {
        if(secondOperatorNumber != 0)
        {
            operationResult = firstOperatorNumber / secondOperatorNumber;
        }
        else
        {
            Box.setText("Division through zero not allowed");
            Box.exec();
            return;
        }
    }

    calculatorDisplay->setText(QString::number(operationResult,'g',15));
    firstOperatorNumber = operationResult;
    resetButtons();
}

void TaschenrechnerW::resetButtons()
{
    trackfirstInput = false;
    trackOperationButton = MathOperationList::None;
    plusButton->setChecked(false);
    minusButton->setChecked(false);
    multiplyButton->setChecked(false);
    divideButton->setChecked(false);
}

TaschenrechnerW::MathOperationList TaschenrechnerW::GetEnumValueFromString(const QString &buttonName)
{
    if (buttonName == "+")
        return MathOperationList::Plus;
    else if (buttonName == "-")
        return MathOperationList::Minus;
    else if (buttonName == "*")
        return MathOperationList::Multiply;
    else if (buttonName == "/")
        return MathOperationList::Divide;
    else
    {
        Box.setText("No matching mathematical operations found");
        Box.exec();
        return MathOperationList::None;
    }
}

void TaschenrechnerW::mathematicalOperation()
{
    QPushButton* button = (QPushButton*)sender();

    switch (trackOperationButton)
    {
    case MathOperationList::None:
        firstOperatorNumber = calculatorDisplay->text().toDouble();
        break;
    case MathOperationList::Plus:
        secondOperatorNumber = screenNumber;
        operationResult = firstOperatorNumber + secondOperatorNumber;
        calculatorDisplay->setText(QString::number(operationResult,'g',15));
        firstOperatorNumber = operationResult;
        break;
    case MathOperationList::Minus:
        secondOperatorNumber = screenNumber;
        operationResult = firstOperatorNumber - secondOperatorNumber;
        calculatorDisplay->setText(QString::number(operationResult,'g',15));
        firstOperatorNumber = operationResult;
        break;
    case MathOperationList::Multiply:
        secondOperatorNumber = screenNumber;
        operationResult = firstOperatorNumber * secondOperatorNumber;
        calculatorDisplay->setText(QString::number(operationResult,'g',15));
        firstOperatorNumber = operationResult;
        break;
    case MathOperationList::Divide:
        secondOperatorNumber = screenNumber;
        if(secondOperatorNumber != 0)
        {
            operationResult = firstOperatorNumber / secondOperatorNumber;
            calculatorDisplay->setText(QString::number(operationResult,'g',15));
            firstOperatorNumber = operationResult;
        }
        else
        {
            Box.setText("Division through zero not allowed");
            Box.exec();
            return;
        }
        break;
     }

    trackOperationButton = GetEnumValueFromString(button->text());
    button->setChecked(true);
    trackfirstInput = false;
}
