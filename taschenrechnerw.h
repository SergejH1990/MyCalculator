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
	void pressedNumberButton(const int number);

protected:
    enum class MathOperationList
    {
        None,
        Plus,
        Minus,
        Multiply,
        Divide
    };

    class QWidget* calculatorWidget;
    class QLabel* calculatorDisplay;
    class QVBoxLayout* verticalLayout;
    class QHBoxLayout* buttonRow0;
    class QHBoxLayout* buttonRow1;
    class QHBoxLayout* buttonRow2;
    class QHBoxLayout* buttonRow3;
    class QHBoxLayout* buttonRow4;
    std::array<class QPushButton*, 10> numberButtons;
    class QPushButton* plusButton;
    class QPushButton* minusButton;
    class QPushButton* multiplyButton;
    class QPushButton* divideButton;
    class QPushButton* signChangeButton;
    class QPushButton* equalButton;
    class QPushButton* deleteButton;
    class QPushButton* commaButton;

	void numberButtonPressed(const int number);
    void singleOutputManipulation();
    void mathematicalOperation();
    void evaluateResult();
    void resetButtons();
    MathOperationList GetEnumValueFromString(const QString& buttonName);

    double screenNumber;
	std::optional<double> firstOperatorNumber;
	bool isSecondInputNumber;
    MathOperationList trackOperationButton;
    QMessageBox Box;
};
#endif // TASCHENRECHNERW_H
