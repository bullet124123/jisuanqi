#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void handleInput(QString ch);
protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void onNumberClicked();
    void onOpClicked();
    void onDotClicked();
    void onEqClicked();
    void onClearClicked();
    void onBackClicked();

private:
    Ui::MainWindow *ui;
    double num1 = 0;
    QString op;
    bool isNewNum = true;
    bool hasError = false;
};
#endif // MAINWINDOW_H
