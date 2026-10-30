#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class mainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void on_btn_0_clicked();
    void on_btn_1_clicked();
    void on_btn_2_clicked();
    void on_btn_3_clicked();
    void on_btn_4_clicked();
    void on_btn_5_clicked();
    void on_btn_6_clicked();
    void on_btn_7_clicked();
    void on_btn_8_clicked();
    void on_btn_9_clicked();
    void on_btn_dot_clicked();

    void on_btn_add_clicked();
    void on_btn_sub_clicked();
    void on_btn_mul_clicked();
    void on_btn_div_clicked();
    void on_btn_eq_clicked();
    void on_btn_clear_clicked();
    void on_btn_back_clicked();

    void on_btn_percent_clicked();
    void on_btn_ce_clicked();
    void on_btn_negate_clicked();
    void on_btn_reciprocal_clicked();
    void on_btn_square_clicked();
    void on_btn_sqrt_clicked();

private:
    void inputNumber(const QString &num);
    void inputDot();
    void inputOp(const QString &opr);
    void calcEqual();
    double doCalculate(double a, double b, const QString &opr, bool &ok);

    void clearAll();
    void clearEntry();
    void backspace();
    void negate();
    void percent();
    void reciprocal();
    void square();
    void sqrtInput();

    void setDisp(const QString &text);
    QString dispText() const;
    bool isErrorState() const;

    Ui::mainWindow *ui;
    double num1;
    QString op;
    bool isNewNum;
    QString m_bufSecond;
    bool m_error;   // 新增错误标记
};

#endif // MAINWINDOW_H
