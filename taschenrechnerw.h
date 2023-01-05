#ifndef TASCHENRECHNERW_H
#define TASCHENRECHNERW_H

#include <QMainWindow>
#include <QMessageBox>
#include <array>

class TaschenrechnerW : public QMainWindow
{
    Q_OBJECT
public:
    TaschenrechnerW(QWidget *parent = nullptr);
    ~TaschenrechnerW();

protected:
    class QWidget* taschenrechnerWidget;
    class QLabel* taschenrechnerAnzeige;
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

    void num_pressed();
    void singleNUmberOutputManipulation();
    void mathematicalOperations();
    void evaluateResult();

    double screenNumber;
    double firstOperatorNumber;
    double secondOperatorNumber;
    bool trackfirstInput;
    double operationResult;
    QString trackOperationButton;
    QString trackTwoCLicksOperation;
    QMessageBox Box;
    const QStringList MATH_OPERATIONS_LIST={"+","-","x","/"};

};
#endif // TASCHENRECHNERW_H
