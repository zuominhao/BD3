#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots: // 声明私有槽函数
    void useSVN(); // 声明显示成功对话框的函数
    QString selectFolder(); // 添加选择文件夹槽函数的声明
    void overWriteSaveFile();//添加覆盖存档的声明

private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
