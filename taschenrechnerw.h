#ifndef TASCHENRECHNERW_H
#define TASCHENRECHNERW_H

#include <QMainWindow>
#include <QMessageBox>

class TaschenrechnerW : public QMainWindow
{
    Q_OBJECT
public:
    TaschenrechnerW(QWidget *parent = nullptr);
    ~TaschenrechnerW();

protected:
    class QLabel* taschenrechnerAnzeige;
    class QPushButton* numberButton0;
    class QPushButton* numberButton1;
    class QPushButton* numberButton2;
    class QPushButton* numberButton3;
    class QPushButton* numberButton4;
    class QPushButton* numberButton5;
    class QPushButton* numberButton6;
    class QPushButton* numberButton7;
    class QPushButton* numberButton8;
    class QPushButton* numberButton9;

    void num_pressed();
    void singleNUmberOutputManipulation();
    void mathematicalOperations();
    void equalButton();

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
