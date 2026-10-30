#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mainWindow)
{
    ui->setupUi(this);
    num1 = 0;
    op = "";
    isNewNum = true;
    m_bufSecond = "";
    m_error = false;
    setDisp("");

    // 窗口整体背景：浅灰，按钮不会看不见
    this->setStyleSheet(R"(
        QMainWindow{
            background-color:#dcdcdc;
        }
    )");

    // 显示屏：深色显示区，保留计算器感
    ui->lab_display->setStyleSheet(R"(
        QLabel {
            font-family: "Microsoft YaHei";
            font-size: 48px;
            color: #ffffff;
            background-color: #121212;
            border: 1px solid #888888;
            border-radius:10px;
            padding:16px 14px;
            qproperty-alignment: AlignRight | AlignVCenter;
        }
    )");

    // 数字按钮：深灰底，黑字
    QString numBtnStyle = R"(
        QPushButton{
            font-size:20px;
            font-weight:600;
            color:#111111;
            background-color:#444444;
            border: 1px solid rgba(0,0,0,0.15);
            border-radius:8px;
            min-height:55px;
        }
        QPushButton:pressed{
            background-color:#606060;
        }
    )";

    // 普通功能按钮：中灰底，黑字
    QString funcBtnStyle = R"(
        QPushButton{
            font-size:18px;
            font-weight:600;
            color:#111111;
            background-color:#585858;
            border: 1px solid rgba(0,0,0,0.15);
            border-radius:8px;
            min-height:55px;
        }
        QPushButton:pressed{
            background-color:#707070;
        }
    )";

    // 运算符按钮：橙底，黑字
    QString opBtnStyle = R"(
        QPushButton{
            font-size:22px;
            font-weight:600;
            color:#111111;
            background-color:#ff9500;
            border: 1px solid rgba(0,0,0,0.15);
            border-radius:8px;
            min-height:55px;
        }
        QPushButton:pressed{
            background-color:#ffb042;
        }
    )";

    // 等于按钮：蓝底，黑字
    QString eqBtnStyle = R"(
        QPushButton{
            font-size:24px;
            font-weight:600;
            color:#111111;
            background-color:#007aff;
            border: 1px solid rgba(0,0,0,0.15);
            border-radius:8px;
            min-height:55px;
        }
        QPushButton:pressed{
            background-color:#4097ff;
        }
    )";

    // 清除按钮：红底，黑字
    QString clearBtnStyle = R"(
        QPushButton{
            font-size:18px;
            font-weight:600;
            color:#111111;
            background-color:#d33030;
            border: 1px solid rgba(0,0,0,0.15);
            border-radius:8px;
            min-height:55px;
        }
        QPushButton:pressed{
            background-color:#f05454;
        }
    )";

    QList<QPushButton*> numBtns = {
        ui->btn_0,ui->btn_1,ui->btn_2,ui->btn_3,ui->btn_4,
        ui->btn_5,ui->btn_6,ui->btn_7,ui->btn_8,ui->btn_9,
        ui->btn_dot,ui->btn_negate
    };

    QList<QPushButton*> funcBtns = {
        ui->btn_percent,ui->btn_ce,ui->btn_back,
        ui->btn_reciprocal,ui->btn_square,ui->btn_sqrt
    };

    QList<QPushButton*> opBtns = {
        ui->btn_add,ui->btn_sub,ui->btn_mul,ui->btn_div
    };

    for(auto btn : numBtns) btn->setStyleSheet(numBtnStyle);
    for(auto btn : funcBtns) btn->setStyleSheet(funcBtnStyle);
    for(auto btn : opBtns) btn->setStyleSheet(opBtnStyle);
    ui->btn_eq->setStyleSheet(eqBtnStyle);
    ui->btn_clear->setStyleSheet(clearBtnStyle);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setDisp(const QString &text)
{
    ui->lineEdit->setText(text);
}

QString MainWindow::dispText() const
{
    return ui->lineEdit->text();
}

bool MainWindow::isErrorState() const
{
    return m_error;
}

double MainWindow::doCalculate(double a, double b, const QString &opr, bool &ok)
{
    ok = true;
    double res = 0;
    if(opr == "+") res = a + b;
    else if(opr == "-") res = a - b;
    else if(opr == "*") res = a * b;
    else if(opr == "/")
    {
        if(fabs(b) < 1e-9)
        {
            ok = false;
            return 0;
        }
        res = a / b;
    }
    return res;
}

void MainWindow::inputNumber(const QString &num)
{
    if(m_error)
    {
        clearAll();
    }
    if(op.isEmpty())
    {
        if(isNewNum)
        {
            setDisp(num);
            isNewNum = false;
        }
        else
        {
            setDisp(dispText() + num);
        }
    }
    else
    {
        if(isNewNum)
        {
            m_bufSecond = num;
            isNewNum = false;
        }
        else
        {
            m_bufSecond = m_bufSecond + num;
        }
    }
}

void MainWindow::inputDot()
{
    if(m_error)
    {
        clearAll();
    }
    if(op.isEmpty())
    {
        if(isNewNum)
        {
            setDisp(".");
            isNewNum = false;
        }
        else if(!dispText().contains('.'))
        {
            setDisp(dispText() + ".");
        }
        else
        {
            // 重复小数点
            setDisp("异常输入");
            m_error = true;
            return;
        }
    }
    else
    {
        if(isNewNum)
        {
            m_bufSecond = ".";
            isNewNum = false;
        }
        else if(!m_bufSecond.contains('.'))
        {
            m_bufSecond = m_bufSecond + ".";
        }
        else
        {
            setDisp("异常输入");
            m_error = true;
            return;
        }
    }
}

void MainWindow::inputOp(const QString &opr)
{
    if(m_error)
    {
        clearAll();
        return;
    }
    if(op.isEmpty())
    {
        if(dispText().isEmpty())
        {
            setDisp("异常输入");
            m_error = true;
            return;
        }
        num1 = dispText().toDouble();
        op = opr;
        isNewNum = true;
        m_bufSecond = "";
    }
    else
    {
        if(m_bufSecond.isEmpty())
        {
            // 连续运算符
            setDisp("异常输入");
            m_error = true;
            return;
        }
        bool ok;
        double num2 = m_bufSecond.toDouble();
        double res = doCalculate(num1, num2, op, ok);
        if(!ok)
        {
            setDisp("除零错误");
            m_error = true;
            op = "";
            isNewNum = true;
            m_bufSecond = "";
            return;
        }
        setDisp(QString::number(res));
        num1 = res;
        op = opr;
        isNewNum = true;
        m_bufSecond = "";
    }
}

void MainWindow::calcEqual()
{
    if(m_error) return;
    if(op.isEmpty() || m_bufSecond.isEmpty())
    {
        setDisp("异常输入");
        m_error = true;
        return;
    }
    bool ok;
    double num2 = m_bufSecond.toDouble();
    double res = doCalculate(num1, num2, op, ok);
    if(!ok)
    {
        setDisp("除零错误");
        m_error = true;
        op = "";
        isNewNum = true;
        m_bufSecond = "";
        return;
    }
    setDisp(QString::number(res));
    num1 = res;
    op = "";
    isNewNum = true;
    m_bufSecond = "";
}

void MainWindow::clearAll()
{
    setDisp("");
    num1 = 0;
    op = "";
    isNewNum = true;
    m_bufSecond = "";
    m_error = false;
}

void MainWindow::clearEntry()
{
    if(m_error)
    {
        clearAll();
        return;
    }
    if(op.isEmpty())
    {
        setDisp("");
    }
    else
    {
        m_bufSecond = "";
    }
    isNewNum = true;
}

void MainWindow::backspace()
{
    if(m_error)
    {
        clearAll();
        return;
    }
    if(op.isEmpty())
    {
        QString str = dispText();
        if(str.size() <= 1)
        {
            setDisp("");
            isNewNum = true;
        }
        else
        {
            str.chop(1);
            setDisp(str);
        }
    }
    else
    {
        if(m_bufSecond.size() <=1)
        {
            m_bufSecond = "";
            isNewNum = true;
        }
        else
        {
            m_bufSecond.chop(1);
        }
    }
}

void MainWindow::negate()
{
    if(m_error) return;
    if(op.isEmpty())
    {
        if(dispText().isEmpty())
        {
            setDisp("异常输入");
            m_error = true;
            return;
        }
        if(dispText().startsWith("-"))
            setDisp(dispText().mid(1));
        else
            setDisp("-" + dispText());
    }
    else
    {
        if(m_bufSecond.isEmpty())
        {
            setDisp("异常输入");
            m_error = true;
            return;
        }
        if(m_bufSecond.startsWith("-"))
            m_bufSecond = m_bufSecond.mid(1);
        else
            m_bufSecond = "-" + m_bufSecond;
    }
}

void MainWindow::percent()
{
    if(m_error) return;
    if(op.isEmpty())
    {
        if(dispText().isEmpty())
        {
            setDisp("异常输入");
            m_error = true;
            return;
        }
        double val = dispText().toDouble();
        setDisp(QString::number(val /100.0));
        isNewNum = true;
    }
    else
    {
        if(m_bufSecond.isEmpty())
        {
            setDisp("异常输入");
            m_error = true;
            return;
        }
        double val = m_bufSecond.toDouble();
        m_bufSecond = QString::number(val /100.0);
    }
}

void MainWindow::reciprocal()
{
    if(m_error) return;
    if(op.isEmpty())
    {
        if(dispText().isEmpty())
        {
            setDisp("异常输入");
            m_error = true;
            return;
        }
        double val = dispText().toDouble();
        if(fabs(val) <1e-9)
        {
            setDisp("除零错误");
            m_error = true;
            isNewNum = true;
            return;
        }
        setDisp(QString::number(1.0/val));
        isNewNum = true;
    }
    else
    {
        if(m_bufSecond.isEmpty())
        {
            setDisp("异常输入");
            m_error = true;
            return;
        }
        double val = m_bufSecond.toDouble();
        if(fabs(val) <1e-9)
        {
            setDisp("除零错误");
            m_error = true;
            op = "";
            isNewNum = true;
            m_bufSecond = "";
            return;
        }
        m_bufSecond = QString::number(1.0/val);
    }
}

void MainWindow::square()
{
    if(m_error) return;
    if(op.isEmpty())
    {
        if(dispText().isEmpty())
        {
            setDisp("异常输入");
            m_error = true;
            return;
        }
        double val = dispText().toDouble();
        setDisp(QString::number(val*val));
        isNewNum = true;
    }
    else
    {
        if(m_bufSecond.isEmpty())
        {
            setDisp("异常输入");
            m_error = true;
            return;
        }
        double val = m_bufSecond.toDouble();
        m_bufSecond = QString::number(val*val);
    }
}

void MainWindow::sqrtInput()
{
    if(m_error) return;
    if(op.isEmpty())
    {
        if(dispText().isEmpty())
        {
            setDisp("异常输入");
            m_error = true;
            return;
        }
        double val = dispText().toDouble();
        if(val <0)
        {
            setDisp("无效输入");
            m_error = true;
            isNewNum = true;
            return;
        }
        setDisp(QString::number(sqrt(val)));
        isNewNum = true;
    }
    else
    {
        if(m_bufSecond.isEmpty())
        {
            setDisp("异常输入");
            m_error = true;
            return;
        }
        double val = m_bufSecond.toDouble();
        if(val <0)
        {
            setDisp("无效输入");
            m_error = true;
            op = "";
            isNewNum = true;
            m_bufSecond = "";
            return;
        }
        m_bufSecond = QString::number(sqrt(val));
    }
}

void MainWindow::on_btn_0_clicked(){ inputNumber("0"); }
void MainWindow::on_btn_1_clicked(){ inputNumber("1"); }
void MainWindow::on_btn_2_clicked(){ inputNumber("2"); }
void MainWindow::on_btn_3_clicked(){ inputNumber("3"); }
void MainWindow::on_btn_4_clicked(){ inputNumber("4"); }
void MainWindow::on_btn_5_clicked(){ inputNumber("5"); }
void MainWindow::on_btn_6_clicked(){ inputNumber("6"); }
void MainWindow::on_btn_7_clicked(){ inputNumber("7"); }
void MainWindow::on_btn_8_clicked(){ inputNumber("8"); }
void MainWindow::on_btn_9_clicked(){ inputNumber("9"); }
void MainWindow::on_btn_dot_clicked(){ inputDot(); }

void MainWindow::on_btn_add_clicked(){ inputOp("+"); }
void MainWindow::on_btn_sub_clicked(){ inputOp("-"); }
void MainWindow::on_btn_mul_clicked(){ inputOp("*"); }
void MainWindow::on_btn_div_clicked(){ inputOp("/"); }
void MainWindow::on_btn_eq_clicked(){ calcEqual(); }
void MainWindow::on_btn_clear_clicked(){ clearAll(); }
void MainWindow::on_btn_back_clicked(){ backspace(); }

void MainWindow::on_btn_percent_clicked(){ percent(); }
void MainWindow::on_btn_negate_clicked(){ negate(); }
void MainWindow::on_btn_reciprocal_clicked(){ reciprocal(); }
void MainWindow::on_btn_square_clicked(){ square(); }
void MainWindow::on_btn_sqrt_clicked(){ sqrtInput(); }
void MainWindow::on_btn_ce_clicked(){ clearEntry(); }

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    QString text = event->text();
    if(key >= Qt::Key_0 && key <= Qt::Key_9)
    {
        inputNumber(text);
        return;
    }
    if(key == Qt::Key_Period)
    {
        inputDot();
        return;
    }
    if(key == Qt::Key_Plus)     { inputOp("+"); return; }
    if(key == Qt::Key_Minus)    { inputOp("-"); return; }
    if(key == Qt::Key_Asterisk) { inputOp("*"); return; }
    if(key == Qt::Key_Slash)    { inputOp("/"); return; }

    if(key == Qt::Key_Enter || key == Qt::Key_Return)
    {
        calcEqual();
        return;
    }
    if(key == Qt::Key_Backspace)
    {
        backspace();
        return;
    }
    if(key == Qt::Key_Escape)
    {
        clearAll();
        return;
    }
    QMainWindow::keyPressEvent(event);
}
