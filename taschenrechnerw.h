#ifndef TASCHENRECHNERW_H
#define TASCHENRECHNERW_H

#include <QMainWindow>
#include <QMessageBox>
#include <array>
#include <optional>

class TaschenrechnerW : public QMainWindow
{
	Q_OBJECT
public:
	TaschenrechnerW(QWidget *parent = nullptr);
	~TaschenrechnerW();

signals:
	void NumberButtonPressed(const int number);

protected:
	enum class MathOperationList
	{
		None,
		Plus,
		Minus,
		Multiply,
		Divide
	};

	void OnNumberButtonPressed(const int number);
	void SingleOutputOperation();
	void MathematicalOperation();
	void EvaluateResult();
	MathOperationList GetEnumValueFromString(const QString& buttonName);

	class QWidget* calculatorWidget;
	class QLabel* calculatorDisplay;
	QMessageBox Box;
	class QVBoxLayout* verticalLayout;

	// Button layouts
	class QHBoxLayout* buttonRow0;
	class QHBoxLayout* buttonRow1;
	class QHBoxLayout* buttonRow2;
	class QHBoxLayout* buttonRow3;
	class QHBoxLayout* buttonRow4;

	// Buttons
	std::array<class QPushButton*, 10> numberButtons;
	class QPushButton* plusButton;
	class QPushButton* minusButton;
	class QPushButton* multiplyButton;
	class QPushButton* divideButton;
	class QPushButton* signChangeButton;
	class QPushButton* equalButton;
	class QPushButton* deleteButton;
	class QPushButton* commaButton;

	bool isOperationStarted;
	double screenNumber;
	std::optional<double> firstOperatorNumber;
	MathOperationList trackOperationButton;
};
#endif // TASCHENRECHNERW_H
