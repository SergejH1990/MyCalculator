#include "taschenrechnerw.h"
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>


//Konstruktor
TaschenrechnerW::TaschenrechnerW(QWidget *parent): QMainWindow(parent),
calculatorDisplay(new QLabel),
Box(),
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
isOperationStarted(false),
screenNumber(),
firstOperatorNumber(),
trackOperationButton(MathOperationList::None)
{
	setMinimumSize(100, 300);

	// Create number buttons
	for (int buttonNumber = 0; buttonNumber < (int)numberButtons.size(); buttonNumber++)
	{
		numberButtons[buttonNumber] = new QPushButton();
		numberButtons[buttonNumber]->setText(QString::number(buttonNumber));
		connect(numberButtons[buttonNumber], &QPushButton::clicked, this, [this, buttonNumber](){
			emit NumberButtonPressed(buttonNumber);
		});
	}

	connect(this, &TaschenrechnerW::NumberButtonPressed, this, &TaschenrechnerW::OnNumberButtonPressed);
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

	QWidget* const calculatorWidget = new QWidget;
	calculatorWidget->setLayout(verticalLayout);
	setCentralWidget(calculatorWidget);

	//Initialize label
	calculatorDisplay->setText("0");
	calculatorDisplay->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

	//connecting output modifications
	connect(signChangeButton, &QPushButton::clicked, this, &TaschenrechnerW::SingleOutputOperation);
	connect(deleteButton, &QPushButton::clicked, this, &TaschenrechnerW::SingleOutputOperation);
	connect(commaButton, &QPushButton::clicked, this, &TaschenrechnerW::SingleOutputOperation);
	connect(equalButton, &QPushButton::clicked, this, &TaschenrechnerW::EvaluateResult);

	//connecting mathematical Operations
	connect(plusButton, &QPushButton::clicked, this, &TaschenrechnerW::MathematicalOperation);
	connect(minusButton, &QPushButton::clicked, this, &TaschenrechnerW::MathematicalOperation);
	connect(multiplyButton, &QPushButton::clicked, this, &TaschenrechnerW::MathematicalOperation);
	connect(divideButton, &QPushButton::clicked, this, &TaschenrechnerW::MathematicalOperation);
}

TaschenrechnerW::~TaschenrechnerW()
{
}

void TaschenrechnerW::OnNumberButtonPressed(const int number)
{
	QPushButton* const button = numberButtons[number];

	if(trackOperationButton != MathOperationList::None && isOperationStarted)
	{
		screenNumber = button->text().toDouble();
		isOperationStarted = false;
	}
	else
	{
		screenNumber = (calculatorDisplay->text() + button->text()).toDouble();
	}

	calculatorDisplay->setText(QString::number(screenNumber,'g',15));
}

void TaschenrechnerW::SingleOutputOperation()
{
	QPushButton* button = (QPushButton*)sender();

	if(button->text() == "+/-")
	{
		screenNumber = -1 * screenNumber;
		calculatorDisplay->setText(QString::number(screenNumber,'g',15));
	}
	else if(button->text() == "Del")
	{
		calculatorDisplay->setText(QString::number(0,'g',15));
		screenNumber = 0.0;
		firstOperatorNumber = {};
		trackOperationButton = MathOperationList::None;
	}
	else if(button->text() == "." && calculatorDisplay->text().indexOf(".") == -1)
	{
		calculatorDisplay->setText(calculatorDisplay->text() + ".");
	}
}

void TaschenrechnerW::EvaluateResult()
{
	if (!firstOperatorNumber.has_value())
	{
		return;
	}

	const double firstOperationNumber = firstOperatorNumber.value();
	double operationResult = firstOperationNumber;
	if(trackOperationButton == MathOperationList::Plus)
	{
		operationResult = firstOperationNumber + screenNumber;
	}
	else if(trackOperationButton == MathOperationList::Minus)
	{
		operationResult = firstOperationNumber - screenNumber;
	}
	else if(trackOperationButton == MathOperationList::Multiply)
	{
		operationResult = firstOperationNumber * screenNumber;
	}
	else if(trackOperationButton == MathOperationList::Divide)
	{
		if(screenNumber != 0)
		{
			operationResult = firstOperationNumber / screenNumber;
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
	trackOperationButton = MathOperationList::None;
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

	Box.setText("No matching mathematical operations found");
	Box.exec();
	return MathOperationList::None;
}

void TaschenrechnerW::MathematicalOperation()
{
	QPushButton* button = (QPushButton*)sender();

	const double firstOperationNumber = firstOperatorNumber.has_value() ? firstOperatorNumber.value() : screenNumber;
	double operationResult  = 0.0;
	switch (trackOperationButton)
	{
	case MathOperationList::None:
		operationResult = firstOperationNumber;
		break;
	case MathOperationList::Plus:{
		if (!firstOperatorNumber.has_value())
		{
			return;
		}

		operationResult = firstOperationNumber + screenNumber;
		calculatorDisplay->setText(QString::number(operationResult,'g',15));
		break;
		}
	case MathOperationList::Minus:{
		if (!firstOperatorNumber.has_value())
		{
			return;
		}

		operationResult = firstOperationNumber - screenNumber;
		calculatorDisplay->setText(QString::number(operationResult,'g',15));
		firstOperatorNumber = operationResult;
		break;
		}
	case MathOperationList::Multiply:{
		if (!firstOperatorNumber.has_value())
		{
			return;
		}

		operationResult = firstOperationNumber * screenNumber;
		calculatorDisplay->setText(QString::number(operationResult,'g',15));
		break;
		}
	case MathOperationList::Divide:{
		if (!firstOperatorNumber.has_value())
		{
			return;
		}

		if(screenNumber != 0)
		{
			operationResult = firstOperationNumber / screenNumber;
			calculatorDisplay->setText(QString::number(operationResult,'g',15));
		}
		else
		{
			Box.setText("Division through zero not allowed");
			Box.exec();
			return;
		}
		break;
		}
	}

	isOperationStarted = true;
	firstOperatorNumber = operationResult;
	trackOperationButton = GetEnumValueFromString(button->text());
}
