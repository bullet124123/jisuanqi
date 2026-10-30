#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 数字按钮绑定
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
    //运算符
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

void MainWindow::onNumberClicked()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if(isNewNum){
        ui->label_display->setText(btn->text());
        isNewNum = false;
    }else{
        ui->label_display->setText(ui->label_display->text() + btn->text());
    }
}

void MainWindow::onOpClicked()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    num1 = ui->label_display->text().toDouble();
    op = btn->text();
    isNewNum = true;
}

void MainWindow::onDotClicked()
{
    QString s = ui->label_display->text();
    if(!s.contains(".")){
        ui->label_display->setText(s + ".");
        isNewNum = false;
    }
}

void MainWindow::onEqClicked()
{
    double num2 = ui->label_display->text().toDouble();
    double res = 0;
    if(op == "+") res = num1 + num2;
    else if(op == "-") res = num1 - num2;
    else if(op == "*") res = num1 * num2;
    else if(op == "/") res = num1 / num2;

    ui->label_display->setText(QString::number(res));
    isNewNum = true;
}

void MainWindow::onClearClicked()
{
    ui->label_display->setText("");
    num1 = 0;
    op = "";
    isNewNum = true;
}

void MainWindow::onBackClicked()
{
    QString s = ui->label_display->text();
    s.chop(1);
    ui->label_display->setText(s);
}
