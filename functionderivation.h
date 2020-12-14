#ifndef FUNCTIONDERIVATION_H
#define FUNCTIONDERIVATION_H

#include <QMainWindow>

namespace Ui {
class FunctionDerivation;
}

class FunctionDerivation : public QMainWindow
{
    Q_OBJECT

public:
    explicit FunctionDerivation(QWidget *parent = 0);
    QString Derivate(QString &terme);
    QString DerivateFunction(QString const& termeDerive);
    void Derive1(QString terme, QString &pendingOperator);
    void DerivateOperation(QString &terme,QString &pendingOperator);
    void answer();
    void additiveDerivation();
    void multiplicativeDerivation();
    void powerOperation(QString &terme);   
    bool containsFraction(QString str,int n);
    void clear();
    void leftBracket();
    void rightBracket();
    void derivateExp(QString &exp);
    ~FunctionDerivation();

public slots:
    void ButtonClicked();
    void Equal();
    void operatorClicked();
    void specialOperatorClicked();
    void ButtonXclicked();
    void Clear();
    void clearAll();

private:
    Ui::FunctionDerivation *ui;
    QVector <QStringList> sumSoFar;
    QStringList ROperand;
    QVector <QString> DeriveSumSoFar;
    QVector <QStringList> factorSoFar;
    QVector <QString> DeriveFactorSoFar;
    QVector <QString> pendingMultiplicative;
    QVector <QString> pendingAdditive;
    QVector <QString> pendingOperation;
    QString m_code;
    QString m_derive;
    bool alreadyDerivate;

};

bool containsOperator(QString str);
#endif // FUNCTIONDERIVATION_H
