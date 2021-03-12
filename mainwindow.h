#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_BEGIN_NAMESPACE

class QTextEdit;
class QTreeWidgetItem;

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_released();

    void on_pushButton_4_pressed();

    void showFont(QTreeWidgetItem *item);

    void on_pushButton_2_released();

    void on_pushButton_4_released();

    void on_pushButton_6_released();

    void on_pushButton_5_released();

    void on_pushButton_7_released();

    void on_pushButton_7_pressed();

private:
    Ui::MainWindow *ui;

    void setupFontTree();

    QFont font;
};
#endif // MAINWINDOW_H
