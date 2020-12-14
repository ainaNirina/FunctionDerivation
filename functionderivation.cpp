#include "functionderivation.h"
#include "ui_functionderivation.h"

FunctionDerivation::FunctionDerivation(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FunctionDerivation)
{
    ui->setupUi(this);
    m_derive.clear();
    alreadyDerivate   = false;

    ROperand.push_back("");

    sumSoFar.push_back(QStringList(""));
    factorSoFar.push_back(QStringList(""));
    DeriveFactorSoFar.push_back("");
    DeriveSumSoFar.push_back("");
    pendingAdditive.push_back("");
    pendingMultiplicative.push_back("");
    pendingOperation.push_back("");

    connect(ui->pushButton0,SIGNAL(clicked()),this,SLOT(ButtonClicked()));
    connect(ui->pushButton1,SIGNAL(clicked()),this,SLOT(ButtonClicked()));
    connect(ui->pushButton2,SIGNAL(clicked()),this,SLOT(ButtonClicked()));
    connect(ui->pushButton3,SIGNAL(clicked()),this,SLOT(ButtonClicked()));
    connect(ui->pushButton4,SIGNAL(clicked()),this,SLOT(ButtonClicked()));
    connect(ui->pushButton5,SIGNAL(clicked()),this,SLOT(ButtonClicked()));
    connect(ui->pushButton6,SIGNAL(clicked()),this,SLOT(ButtonClicked()));
    connect(ui->pushButton7,SIGNAL(clicked()),this,SLOT(ButtonClicked()));
    connect(ui->pushButton8,SIGNAL(clicked()),this,SLOT(ButtonClicked()));
    connect(ui->pushButton9,SIGNAL(clicked()),this,SLOT(ButtonClicked()));
    connect(ui->pushButtonLn,SIGNAL(clicked()),this,SLOT(specialOperatorClicked()));
    connect(ui->pushButtonRoot,SIGNAL(clicked()),this,SLOT(specialOperatorClicked()));
    connect(ui->pushButtonExp,SIGNAL(clicked()),this,SLOT(specialOperatorClicked()));
    connect(ui->pushButtonCos,SIGNAL(clicked()),this,SLOT(specialOperatorClicked()));
    connect(ui->pushButtonSin,SIGNAL(clicked()),this,SLOT(specialOperatorClicked()));
    connect(ui->pushButtonTan,SIGNAL(clicked()),this,SLOT(specialOperatorClicked()));
    connect(ui->pushButtonEqual,SIGNAL(clicked()),this,SLOT(Equal()));
    connect(ui->pushButtonX1,SIGNAL(clicked()),this,SLOT(ButtonXclicked()));
    connect(ui->pushButtonX2,SIGNAL(clicked()),this,SLOT(ButtonXclicked()));
    connect(ui->pushButtonPlus,SIGNAL(clicked()),this,SLOT(operatorClicked()));
    connect(ui->pushButtonMinus,SIGNAL(clicked()),this,SLOT(operatorClicked()));
    connect(ui->pushButtonFois,SIGNAL(clicked()),this,SLOT(operatorClicked()));
    connect(ui->pushButtonDivision,SIGNAL(clicked()),this,SLOT(operatorClicked()));
    connect(ui->pushButtonLB,SIGNAL(clicked()),this,SLOT(operatorClicked()));
    connect(ui->pushButtonRB,SIGNAL(clicked()),this,SLOT(operatorClicked()));
    connect(ui->pushButtonClear,SIGNAL(clicked()),this,SLOT(Clear()));
    connect(ui->pushButtonClearAll,SIGNAL(clicked()),this,SLOT(clearAll()));
}


void FunctionDerivation::ButtonClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());

    if(clickedButton->text() == "0")
    {
        if(ui->label->toPlainText() == "0")
        {
            m_code = "0";
        }
        else
        {
            m_code += "0";
            ui->label->setText(m_code);

        }
    }
    else
    {

        if(ui->checkBox->isChecked())
           {
            m_code +="<sup>"+clickedButton->text()+"</sup>";

           }
        else
        {
            m_code += clickedButton->text();

        }
        ui->label->setText(m_code);
     }


}



void FunctionDerivation::ButtonXclicked()
{       
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    m_code += clickedButton->text();
    ui->label->setText(m_code);

}

void FunctionDerivation::operatorClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    m_code += clickedButton->text();
    ui->label->setText(m_code);
}

void FunctionDerivation::specialOperatorClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    m_code += clickedButton->text()+"(";
    ui->label->setText(m_code);
}

void FunctionDerivation::leftBracket()
{

    sumSoFar.push_back(QStringList(""));
    factorSoFar.push_back(QStringList(""));
    DeriveFactorSoFar.push_back("");
    DeriveSumSoFar.push_back("");
    pendingAdditive.push_back("");
    pendingMultiplicative.push_back("");
    pendingOperation.push_back("");

}

void FunctionDerivation::rightBracket()
{

    answer();

    factorSoFar[factorSoFar.size()-1].clear();
    sumSoFar[sumSoFar.size()-1].clear();
    sumSoFar.pop_back();
    factorSoFar.pop_back();
    DeriveFactorSoFar.pop_back();
    DeriveSumSoFar.pop_back();
    pendingAdditive.pop_back();
    pendingMultiplicative.pop_back();
    pendingOperation.pop_back();

    if((ui->lineEdit->text().contains(tr("+")) ||  ui->lineEdit->text().contains(tr("-"))) &&
        ui->lineEdit->text().at(0) != tr("("))
    {
        ui->lineEdit->setText(ui->lineEdit->text().prepend("("));
        ui->lineEdit->setText(ui->lineEdit->text().append(")"));
    }
    alreadyDerivate = true;

}

void FunctionDerivation::Clear()
{
    if(m_code .endsWith(tr("ln(")))
    {
        m_code.remove(m_code.size()-3,3);
    }
    else if(m_code .endsWith(tr("cos(")) || m_code.endsWith(tr("sin(")))
    {
        m_code.remove(m_code.size()-4,4);
    }
    else if(m_code .endsWith(tr("e(")) || m_code.endsWith(tr("√(")))
    {
        m_code.remove(m_code.size()-2,2);
    }
    else if(m_code .endsWith(tr(">")))
    {
        m_code.remove(m_code.lastIndexOf("<"),6);
        m_code.remove(m_code.lastIndexOf("<"),m_code.size()-m_code.lastIndexOf("<"));
    }
    else
        m_code.remove(m_code.size()-1,1);

    ui->label->setHtml(m_code);
}

void FunctionDerivation::clearAll()
{
    m_code.clear();
    m_derive.clear();
    factorSoFar[factorSoFar.size()-1].clear();
    sumSoFar[sumSoFar.size()-1].clear();
    sumSoFar.clear();
    factorSoFar.clear();
    DeriveFactorSoFar.clear();
    DeriveSumSoFar.clear();
    pendingOperation.clear();
    ui->label->setText(m_code);
    alreadyDerivate = false;

    sumSoFar.push_back(QStringList(""));
    factorSoFar.push_back(QStringList(""));
    DeriveFactorSoFar.push_back("");
    DeriveSumSoFar.push_back("");
    pendingAdditive.push_back("");
    pendingMultiplicative.push_back("");
    pendingOperation.push_back("");
}

QString FunctionDerivation::Derivate(QString &termeADerivee)
{
    if(termeADerivee.contains("x"))
    {

        if(termeADerivee.contains("sup"))
        {
            termeADerivee.remove("<");
            termeADerivee.remove(">");
            termeADerivee.remove("sup");
            termeADerivee.remove("/");

            QString *a = new QString ;
            *a = termeADerivee;
            double *power =  new double;
            *power = a->remove(0,a->indexOf("x")+1).toDouble();
            QString *terme1 = new QString;
            *terme1 = termeADerivee.left(termeADerivee.indexOf("x"));
            double *coefficient = new double;

            if(terme1->isEmpty())
            {
                *coefficient = 1;
            }
            else
                *coefficient = terme1->toDouble();

            double *n = new double;
            *n = *coefficient * (*power);
            *power = *power - 1;

            if(*power == 1)
                termeADerivee = QString::number(*n)+"x";
            else if(*power == 0)
                termeADerivee = QString::number(*n);
            else
                termeADerivee = QString::number(*n)+"x<sup>" + QString::number(*power) +"</sup>";

            delete a; delete terme1; delete n;
            delete power; delete coefficient;

              return termeADerivee;
        }

        else
        {
            if(!termeADerivee.left(termeADerivee.indexOf("x")).isEmpty())
            {
                return (termeADerivee.left(termeADerivee.indexOf("x")));
            }

            else
                return "1";
        }

    }
    else
        return "0";

}

void FunctionDerivation::Derive1(QString terme, QString &pendingOperator)
{
    int n = sumSoFar.size()-1;

    if(terme.right(terme.size()-terme.lastIndexOf(")")).contains("sup"))
        if(terme.at(terme.lastIndexOf(")")+1) == '<')
        {
            powerOperation(terme);
        }

    if(pendingOperator == tr("+"))
    {
        DeriveSumSoFar[n] += "+"+m_derive;
        sumSoFar[n][0] += "+"+terme;        
    }

    else if(pendingOperator == tr("-"))
    {
        QString a = m_derive;

        DeriveSumSoFar[n] += "-("+m_derive+")";
        sumSoFar[n][0] += "-("+terme+")";
    }
    else if(pendingOperator == tr("|"))
    {

        QString *a = new QString;
        *a = terme;

        if(terme.endsWith(">"))
        {
            a->append(")");
            a->prepend("(");
        }
        if(!factorSoFar[n][0].contains(tr("x")))
        {
            DeriveFactorSoFar[n] = "-("+m_derive+")×"+factorSoFar[n][0]+"|"+*a+"<sup>2</sup>";
        }
        else
        {
            if(factorSoFar[n][0].contains('+') || factorSoFar[n][0].contains('-'))
            {

                DeriveFactorSoFar[n] = "(("+DeriveFactorSoFar[n]+")×"+terme+""+"-"+
                                       factorSoFar[n][0]+"×("+m_derive+"))|"+*a+"<sup>2</sup>";
            }
            else
                DeriveFactorSoFar[n] = "("+DeriveFactorSoFar[n]+"×"+terme+"-"+""+
                                       factorSoFar[n][0]+"×("+m_derive+"))"+"|"+*a+"<sup>2</sup>";
        }

        delete a;
        factorSoFar[n][0] = factorSoFar[n][0] +"|"+terme;

    }
    else if(pendingOperator == tr("×"))
    {
        if(DeriveFactorSoFar[DeriveFactorSoFar.size()-1] == "0")
        {
            DeriveFactorSoFar[DeriveFactorSoFar.size()-1] = factorSoFar[n][0]+"×("+m_derive+")";
            factorSoFar[DeriveFactorSoFar.size()-1][0] = factorSoFar[n][0]+"×"+terme;
            return;
        }
        QString *b = new QString;
        *b = pendingAdditive[n];
        if(pendingAdditive[n] == "-")
            *b = "-";
        else
            *b = "+";
        QString *a = new QString;
        *a = terme;
        if(factorSoFar[n][0].contains('+') || factorSoFar[n][0].contains('-'))
        {
            DeriveFactorSoFar[n] = "("+DeriveFactorSoFar[n]+")×"+*a+*b+factorSoFar[n][0]+"×("+m_derive+")";
        }
        else
            DeriveFactorSoFar[n] = DeriveFactorSoFar[n]+"×"+*a+*b+factorSoFar[n][0]+"×("+m_derive+")";
        factorSoFar[n][0] = factorSoFar[n][0] +"×"+*a;

        delete a;
        delete b;
        a=0;
        b=0;

    }

}

void FunctionDerivation::DerivateOperation(QString &terme,QString &pendingOperator)
{
    int n = sumSoFar.size()-1;

  if(pendingOperator == tr("+"))
  {
      sumSoFar[n][0] += "+"+terme;
      DeriveSumSoFar[n] += "+"+Derivate(terme);

  }
  else if(pendingOperator == tr("-"))
  {
      sumSoFar[n][0] += "-"+terme;
      DeriveSumSoFar[n] += "-"+Derivate(terme);
  }
  else if(pendingOperator == tr("|"))
  {
      if(!terme.contains("x"))
      {
          DeriveFactorSoFar[n] += "|"+terme;
          factorSoFar[n][0] = factorSoFar[n][0] +"|"+terme;
      }
      else if(!factorSoFar[n][0].contains('x'))
      {
          QString a = terme;
          DeriveFactorSoFar[n] = "-("+factorSoFar[n][0]+"×"+Derivate(terme)+")|("+a+")<sup>2</sup>";
          factorSoFar[n][0] = factorSoFar[n][0] +"/"+a;
      }
      else
      {       
        QString *a = new QString;
        *a= terme;
        if(factorSoFar[n][0].contains('+') || factorSoFar[n][0].contains('-'))
        {            
          DeriveFactorSoFar[n] = "(("+DeriveFactorSoFar[n]+")×"+*a+"-"+
                                 factorSoFar[n][0]+"×"+Derivate(terme)+")" + "|("+*a+")<sup>2</sup>";
        }

        else
          DeriveFactorSoFar[n] = "("+DeriveFactorSoFar[n]+"×"+*a+""+"-"+
                                 factorSoFar[n][0]+"×"+Derivate(terme)+")" + "|("+*a+")<sup>2</sup>";
      factorSoFar[n][0] = factorSoFar[n][0] +"|"+*a;
      delete a;
      a=0;
      }

  }
  else if(pendingOperator == tr("×"))
  {
      if(DeriveFactorSoFar[n] == "0")
      {
          DeriveFactorSoFar[n] = factorSoFar[n][0]+"×"+Derivate(terme);
          if(!terme.contains("x"))
          {
              DeriveFactorSoFar[n] = "0";
          }
          factorSoFar[n][0] = factorSoFar[n][0] +"×"+terme;
          return;
      }
      if(!terme.contains("x"))
      {
          DeriveFactorSoFar[n] = DeriveFactorSoFar[n]+"×"+terme;
          factorSoFar[n][0] =  factorSoFar[n][0] +"×"+terme;
          return;
      }
      QString *b = new QString;
      *b = pendingAdditive[n];
      if(pendingAdditive[n] == "-")
          *b = "-";
      else
          *b = "+";
      QString *a = new QString;
      *a = terme;
      if(factorSoFar[n][0].contains('+') || factorSoFar[n][0].contains('-'))
      {          
          DeriveFactorSoFar[n] = "("+DeriveFactorSoFar[n]+")×"+*a+*b+factorSoFar[n][0]+"×"+Derivate(terme);
      }
      else
          DeriveFactorSoFar[n] = DeriveFactorSoFar[n]+"×"+*a+*b+factorSoFar[n][0]+"×"+Derivate(terme);
      factorSoFar[n][0] = factorSoFar[n][0] +"×"+*a;
      delete b;
      delete a;
      b=0;
      a=0;

  }
}

void FunctionDerivation::Equal()
{

    QString *a = new QString;
    *a = m_code;
    int n = ui->derivationDegreeSpinBox->text().toInt();
    switch(n)
    {
    case 0:
        ui->label->setText(ui->label->toHtml()+ "= " +m_code);
        break;
    default:
    {
        for(int i=0; i<n; i++)
        {
            derivateExp(*a);
            *a = m_derive;
            if(m_derive.at(0) == tr("0"))
                m_derive.remove(0,2);
        }
        ui->label->setText(ui->label->toHtml()+ "= " +m_derive);
        break;
    }
    }

    delete a;
    a = 0;
}

void FunctionDerivation::additiveDerivation()
{

  QString expression = ui->lineEdit->text();

  int n = sumSoFar.size()-1;


  if(pendingAdditive[n].isEmpty() && pendingMultiplicative[n].isEmpty())
  {
      if(alreadyDerivate)
      {
          alreadyDerivate = false;
          if(!pendingOperation[n].isEmpty())
          {

              sumSoFar[n][0] = pendingOperation[n]+expression;
              DeriveSumSoFar[n] = DerivateFunction(expression);
              pendingOperation[n].clear();
          }
          else if(expression.right(expression.size()-expression.lastIndexOf(")")).contains("sup"))
          {
              if(expression.at(expression.lastIndexOf(")")+1) == '<')
              {
              powerOperation(expression);
              sumSoFar[n][0] = expression;
              DeriveSumSoFar[n] = m_derive;
              }
          }
          else
          {
           sumSoFar[n][0] = expression;
           DeriveSumSoFar[n] = m_derive;
          }
      }
      else
      {
      sumSoFar[n][0] = expression;
      DeriveSumSoFar[n] = Derivate(expression);
      }
  }

  else
  {
  if(!pendingMultiplicative[n].isEmpty())
  {
      if(alreadyDerivate)
      {
          alreadyDerivate = false;
        if(!pendingOperation[n].isEmpty())
        {
            m_derive = DerivateFunction(expression);
            expression = pendingOperation[n]+expression;
        }

        Derive1(expression,pendingMultiplicative[n]);

      }
      else
         DerivateOperation(expression,pendingMultiplicative[n]);
         m_derive = DeriveFactorSoFar[n];
         pendingMultiplicative[n].clear();

       if(!pendingAdditive[n].isEmpty())
       {
           m_derive = DeriveSumSoFar[n] +pendingAdditive[n]+DeriveFactorSoFar[n];
           sumSoFar[n][0] = factorSoFar[n][0];
           DeriveSumSoFar[n] = m_derive;
           pendingAdditive[n].clear();
       }
       else
       {
           DeriveSumSoFar[n] = m_derive;
           sumSoFar[n][0] = factorSoFar[n][0];
       }
  }
  if(!pendingAdditive[n].isEmpty())
  {
      if(alreadyDerivate)
      {
          alreadyDerivate = false;
          if(!pendingOperation[n].isEmpty())
          {
              m_derive = DerivateFunction(expression);
              expression = pendingOperation[n]+expression;
              pendingOperation[n].clear();
          }

          Derive1(expression,pendingAdditive[n]);

      }
      else
      DerivateOperation(expression,pendingAdditive[n]);
      m_derive = DeriveSumSoFar[n];
  }
  }

}

void FunctionDerivation::multiplicativeDerivation()
{

    QString expression = ui->lineEdit->text();

    int m = factorSoFar.size()-1;

    if(!pendingMultiplicative[m].isEmpty())
    {
        if(alreadyDerivate)
        {
            alreadyDerivate = false;
            if(!pendingOperation[m].isEmpty())
            {
                expression = pendingOperation[m]+expression;
                m_derive = DerivateFunction(expression);
                pendingOperation[m].clear();
            }
            else
            factorSoFar[m][0] = expression;

            Derive1(expression,pendingMultiplicative[m]);
        }
        else

        {
            factorSoFar[m][0] = expression;
            DerivateOperation(expression,pendingMultiplicative[m]);
        }
        m_derive = DeriveFactorSoFar[m];

    }
    else
    {
        if(alreadyDerivate)
        {
            alreadyDerivate = false;
             if(!pendingOperation[m].isEmpty())
             {
                 factorSoFar[m][0] = pendingOperation[m]+expression;
                 DeriveFactorSoFar[m] = DerivateFunction(expression);
                 pendingOperation[m].clear();
             }
             else if(expression.right(expression.size()-expression.lastIndexOf(")")).contains("sup"))
             {
                 if(expression.at(expression.lastIndexOf(")")+1) == '<')
                 {
                 powerOperation(expression);
                 factorSoFar[m][0] = expression;
                 DeriveFactorSoFar[m] = m_derive;
                 }
             }
             else
             {
             factorSoFar[m][0] = expression;
             DeriveFactorSoFar[m] = m_derive;
             }
        }
        else
        {
        factorSoFar[m][0] = expression;
        DeriveFactorSoFar[m] = Derivate(expression);
        }
    }

}

void FunctionDerivation::answer()
{
    QString expression = ui->lineEdit->text();

    int n = sumSoFar.size()-1;


if(!pendingMultiplicative[n].isEmpty() || !pendingAdditive[n].isEmpty() )
{
    if(!pendingMultiplicative[n].isEmpty())
    {
        if(alreadyDerivate)

        {
            alreadyDerivate = false;
            if(!pendingOperation[n].isEmpty())
            {
                m_derive = DerivateFunction(expression);
                expression = pendingOperation[n]+expression;
                pendingOperation[n].clear();
            }

            Derive1(expression,pendingMultiplicative[n]);

        }
        else
            DerivateOperation(expression,pendingMultiplicative[n]);

        expression = factorSoFar[n][0];
        pendingMultiplicative[n].clear();
        m_derive = DeriveFactorSoFar[n];

        if(!pendingAdditive[n].isEmpty())
        {
            expression = sumSoFar[n][0]+pendingAdditive[n]+factorSoFar[n][0];
            m_derive = DeriveSumSoFar[n]+pendingAdditive[n]+DeriveFactorSoFar[n];
            pendingAdditive[n].clear();
        }
    }

    if(!pendingAdditive[n].isEmpty())
    {
        if(alreadyDerivate)
        {
            alreadyDerivate = false;
            if(!pendingOperation[n].isEmpty())
            {
               m_derive = DerivateFunction(expression);
               expression = pendingOperation[n]+expression;
            }

            Derive1(expression,pendingAdditive[n]);
        }
        else
            DerivateOperation(expression,pendingAdditive[n]);

        expression =sumSoFar[n][0];
        pendingAdditive[n].clear();
        m_derive = DeriveSumSoFar[n];
    }
}
 else
      {
       if(alreadyDerivate)
       {          
           alreadyDerivate = false;
           if(!pendingOperation[n].isEmpty())
           {
               if(n>0)
               {
                    if(!pendingOperation[n-1].isEmpty())

                    {
                        m_derive = DerivateFunction(expression);
                        expression = "("+pendingOperation[n]+expression+")";
                    }
                    else
                    {
                        m_derive = DerivateFunction(expression);
                        expression = "("+pendingOperation[n]+expression+")";
                    }
               }

               else
               {
                    m_derive = DerivateFunction(expression);
                    expression = "("+pendingOperation[n]+expression+")";
               }
           }
           else if(expression.right(expression.size()-expression.lastIndexOf(")")).contains("sup"))
           {
               if(expression.at(expression.lastIndexOf(")")+1) == '<')
               {
                   powerOperation(expression);
               }
           }

       }
       else
       {
           QString *a = new QString;
           *a = expression;
           m_derive = Derivate(*a);
           delete a;
           a = 0;
       }
  }

  ui->lineEdit->setText(expression);

}

QString FunctionDerivation::DerivateFunction(QString const& termeDerive)
{

    QString *a = new QString;
    *a = termeDerive;
    int n = pendingOperation.size()-1;
    if(a->right(a->size()-a->lastIndexOf(")")).contains("sup"))
    {
        if(a->at(a->lastIndexOf(")")+1) == '<')
        {
            a->append(")");
            a->prepend("(");
        }
    }
    if(pendingOperation.at(n) == "ln")
    {
        *a = "("+m_derive+")|"+ *a;
    }
    else if(pendingOperation.at(n) == "e")
    {
        *a = "("+m_derive+")×e"+ *a;
    }
    else if(pendingOperation.at(n) == "cos")
    {
        *a = "-("+m_derive+")×sin"+*a;
    }
    else if(pendingOperation.at(n) == "sin")
    {
        *a = "("+m_derive+")×cos"+ *a;
    }
    else if(pendingOperation.at(n) == "tan")
    {
        *a = "("+m_derive+")|(cos"+*a+")<sup>2</sup>";
    }
    else if(pendingOperation.at(n) == "√")
    {
        *a ="("+ m_derive+")|"+"2√"+ *a;
    }

    m_derive.remove(")");
    m_derive.remove("(");

    return *a;
    delete a;
    a=0;
}

void FunctionDerivation::powerOperation(QString &terme)
{
    QString a = terme;
    a.remove("<");
    a.remove("/");
    a.remove("sup");
    a.remove(">");
    a.remove("(");
    double puissance = a.right(-a.indexOf(")")+a.size()-1).toDouble();
    a = terme;
    a = a.left(a.indexOf(")")+1);

    puissance--;

    if(puissance == 1)
        m_derive = "2*("+m_derive+")×"+a;
    else if(puissance == 0)
        m_derive = m_derive;
    else
        m_derive = QString::number(puissance+1)+"×("+m_derive+")×"+
                a+"<sup>" + QString::number(puissance) +"</sup>";
}

void FunctionDerivation::derivateExp(QString &exp)
{
    if(exp.isEmpty())
    {
        answer();
        return;
    }

    int n = sumSoFar.size()-1;
    if(exp.at(0) == tr("("))
    {
        leftBracket();
        exp.remove(0,1);
    }
    else if(exp.at(0) == tr("l"))
    {
        leftBracket();
        pendingOperation[n] = "ln";
        exp.remove(0,3);
    }
    else if(exp.at(0) == tr("e"))
    {
        leftBracket();
        pendingOperation[n] = "e";
        exp.remove(0,2);
    }
    else if(exp.at(0) == tr("s"))
    {
        leftBracket();
        pendingOperation[n] = "sin";
        exp.remove(0,4);
    }
    else if(exp.at(0) == tr("c"))
    {
        leftBracket();
        pendingOperation[n] = "cos";
        exp.remove(0,4);
    }
    else if(exp.at(0) == tr("t"))
    {
        leftBracket();
        pendingOperation[n] = "tan";
        exp.remove(0,4);
    }
    else if(exp.at(0) == tr("√"))
    {
        leftBracket();
        pendingOperation[n] = "√";
        exp.remove(0,2);
    }
    else if(exp.contains("+") && !containsOperator(exp.left(exp.indexOf("+"))))
    {
        if(exp.at(0) == tr("<"))
        {
            ui->lineEdit->setText(ui->lineEdit->text()+exp.left(exp.indexOf("+")));
        }
        else if(!alreadyDerivate)
            ui->lineEdit->setText(exp.left(exp.indexOf("+")));
        exp.remove(0,exp.indexOf("+")+1);
        additiveDerivation();
        pendingAdditive[n] = "+";
    }
    else if(exp.contains("-") && !containsOperator(exp.left(exp.indexOf("-"))))
    {
        if(exp.at(0) == tr("<"))
        {
            ui->lineEdit->setText(ui->lineEdit->text()+exp.left(exp.indexOf("-")));
        }
        else if(!alreadyDerivate)
            ui->lineEdit->setText(exp.left(exp.indexOf("-")));
        exp.remove(0,exp.indexOf("-")+1);
        additiveDerivation();
        pendingAdditive[n] = "-";
    }
    else if(exp.contains("×") && !containsOperator(exp.left(exp.indexOf("×"))))
    {

        if(exp.at(0) == tr("<"))
        {
            ui->lineEdit->setText(ui->lineEdit->text()+exp.left(exp.indexOf("×")));
        }
        else if(!alreadyDerivate)
            ui->lineEdit->setText(exp.left(exp.indexOf("×")));
        exp.remove(0,exp.indexOf("×")+1);
        multiplicativeDerivation();
        pendingMultiplicative[n] = "×";
    }
    else if(exp.contains("|") &&  !containsOperator(exp.left(exp.indexOf("|"))))
    {
        if(exp.at(0) == tr("<"))
        {
            ui->lineEdit->setText(ui->lineEdit->text()+exp.left(exp.indexOf("|")));
        }
        else if(!alreadyDerivate)
            ui->lineEdit->setText(exp.left(exp.indexOf("|")));
        exp.remove(0,exp.indexOf("|")+1);
        multiplicativeDerivation();
        pendingMultiplicative[n] = "|";
    }
    else if(exp.contains(")") && !containsOperator(exp.left(exp.indexOf(")"))))
    {
        if(exp.at(0) == tr("<"))
        {
            ui->lineEdit->setText(ui->lineEdit->text()+exp.left(exp.indexOf(")")));
        }
        else if(!alreadyDerivate)
            ui->lineEdit->setText(exp.left(exp.indexOf(")")));
        exp.remove(0,exp.indexOf(")")+1);
        rightBracket();
    }
    else
    {
        if(exp.at(0) == tr("<"))
        {
            ui->lineEdit->setText(ui->lineEdit->text()+exp);
        }
        else
            ui->lineEdit->setText(exp);
        answer();
        //exp = m_derive;
        return;
    }

    return derivateExp(exp);
}
bool containsOperator(QString str)
{
    if(str.contains("+") || str.contains(")")  || str.contains("-") || str.contains("×") || str.contains("|"))
    {
       return true;
    }

    return false;
}

FunctionDerivation::~FunctionDerivation()
{
    delete ui;
}
