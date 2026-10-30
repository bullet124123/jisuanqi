#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btn_0,&QPushButton::clicked,this,&MainWindow::onNumberClicked);
    connect(ui->btn_1,&QPushButton::clicked,this,&MainWindow::onNumberClicked);
    connect(ui->btn_2,&QPushButton::clicked,this,&MainWindow::onNumberClicked);
    connect(ui->btn_3,&QPushButton::clicked,this,&MainWindow::onNumberClicked);
    connect(ui->btn_4,&QPushButton::clicked,this,&MainWindow::onNumberClicked);
    connect(ui->btn_5,&QPushButton::clicked,this,&MainWindow::onNumberClicked);
    connect(ui->btn_6,&QPushButton::clicked,this,&MainWindow::onNumberClicked);
    connect(ui->btn_7,&QPushButton::clicked,this,&MainWindow::onNumberClicked);
    connect(ui->btn_8,&QPushButton::clicked,this,&MainWindow::onNumberClicked);
    connect(ui->btn_9,&QPushButton::clicked,this,&MainWindow::onNumberClicked);

    connect(ui->btn_add,&QPushButton::clicked,this,&MainWindow::onOpClicked);
    connect(ui->btn_sub,&QPushButton::clicked,this,&MainWindow::onOpClicked);
    connect(ui->btn_mul,&QPushButton::clicked,this,&MainWindow::onOpClicked);
    connect(ui->btn_div,&QPushButton::clicked,this,&MainWindow::onOpClicked);

    connect(ui->btn_dot,&QPushButton::clicked,this,&MainWindow::onDotClicked);
    connect(ui->btn_eq,&QPushButton::clicked,this,&MainWindow::onEqClicked);
    connect(ui->btn_clear,&QPushButton::clicked,this,&MainWindow::onClearClicked);
    connect(ui->btn_back,&QPushButton::clicked,this,&MainWindow::onBackClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleInput(QString ch)
{
    if(ch >= "0" && ch <= "9"){
        if(isNewNum){
            ui->label_display->setText(ch);
            isNewNum = false;
        }else{
            ui->label_display->setText(ui->label_display->text() + ch);
        }
    }else if(ch == "."){
        QString s = ui->label_display->text();
        if(!s.contains(".")){
            ui->label_display->setText(s + ".");
            isNewNum = false;
        }
    }else if(ch == "+" || ch == "-" || ch == "*" || ch == "/"){
        num1 = ui->label_display->text().toDouble();
        op = ch;
        isNewNum = true;
    }else if(ch == "="){
        double num2 = ui->label_display->text().toDouble();
        double res = 0;
        if(op == "+") res = num1 + num2;
        else if(op == "-") res = num1 - num2;
        else if(op == "*") res = num1 * num2;
        else if(op == "/") res = num1 / num2;
        ui->label_display->setText(QString::number(res));
        isNewNum = true;
    }else if(ch == "C"){
        ui->label_display->setText("");
        num1 = 0;
        op = "";
        isNewNum = true;
    }else if(ch == "Back"){
        QString s = ui->label_display->text();
        s.chop(1);
        ui->label_display->setText(s);
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    QString keyText = event->text();
    if(keyText >= "0" && keyText <= "9" || keyText == "." || keyText == "+" || keyText == "-" || keyText == "*" || keyText == "/"){
        handleInput(keyText);
    }else if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return){
        handleInput("=");
    }else if(event->key() == Qt::Key_Backspace){
        handleInput("Back");
    }else if(event->key() == Qt::Key_C){
        handleInput("C");
    }
}

void MainWindow::onNumberClicked()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    handleInput(btn->text());
}
void MainWindow::onOpClicked()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    handleInput(btn->text());
}
void MainWindow::onDotClicked(){ handleInput("."); }
void MainWindow::onEqClicked(){ handleInput("="); }
void MainWindow::onClearClicked(){ handleInput("C"); }
void MainWindow::onBackClicked(){ handleInput("Back"); }
