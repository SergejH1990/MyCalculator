#ifndef TASCHENRECHNERW_H
#define TASCHENRECHNERW_H

#include <QMainWindow>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class TaschenrechnerW; }
QT_END_NAMESPACE

class TaschenrechnerW : public QMainWindow
{
    Q_OBJECT

public:
    TaschenrechnerW(QWidget *parent = nullptr);

    ~TaschenrechnerW();

private:
    double screenNumber;
    double firstOperatorNumber;
    double secondOperatorNumber;
    bool trackfirstInput;
    double operationResult;
    QString trackOperationButton;
    QString trackTwoCLicksOperation;
    QMessageBox Box;
    const QStringList MATH_OPERATIONS_LIST={"+","-","x","/"};

private:
    Ui::TaschenrechnerW *ui;

private slots:
    void num_pressed();
    void singleNUmberOutputManipulation();
    void mathematicalOperations();
    void equalButton();

};
#endif // TASCHENRECHNERW_H
