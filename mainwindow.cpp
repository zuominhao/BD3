#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog> // 添加包含 QFileDialog 的头文件
#include <QDir>
#include <QDesktopServices>
#include <windows.h>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, qApp, &QApplication::quit); // 连接关闭按钮的 clicked 信号到 QApplication 的 quit 槽函数

    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::useSVN); // 使用SVN的更新

    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::copyFile);

    connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::overWriteSaveFile);//覆盖存档
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::useSVN()
{

    QString workingCopyPath = "C:\\Users\\JR1\\work\\5G研发部门资料库";// 指定要更新的工作副本路径

    QString commandLine = QString("/command:update /path:\"%1\"").arg(workingCopyPath);// 构建更新命令行参数

    ShellExecute(nullptr, L"open", L"TortoiseProc.exe", commandLine.toStdWString().c_str(), nullptr, SW_SHOW);// 执行 TortoiseSVN 更新命令
}

QString MainWindow::selectFolder()
{
    QString folderPath = QFileDialog::getExistingDirectory(this, "选择文件夹", QDir::homePath());// 打开文件夹选择对话框

    if (!folderPath.isEmpty()) {
        qDebug() << "选择的文件夹路径：" << folderPath;// 如果用户选择了文件夹，则在控制台输出文件夹路径
    }

    return folderPath;
}

void MainWindow::overWriteSaveFile()
{
    QString sourcePath = selectFolder();
    QString targetPath = "C:/Users/JR1/Desktop/1111111111111.docx";

    QFile sourceFile(sourcePath);
    QFile targetFile(targetPath);

    if(sourceFile.exists())
    {
        if(targetFile.exists())
        {
            targetFile.remove();
        }
        QDir().rename(sourcePath, targetPath);
        QMessageBox::information(this, "Move File", "File moved successfully!");
    }
    else
    {
        QMessageBox::warning(this, "Move File", "Source file does not exist!");
    }

}

void MainWindow::copyFile() {
    QString sourceDir = "BD3的存档目录路径"; // 替换为BD3的存档目录路径
    QString destinationDir = "特定位置A的路径"; // 替换为特定位置A的路径

    // 获取BD3存档目录下最新的文件
    QDir dir(sourceDir);
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    dir.setSorting(QDir::Time | QDir::Reversed);
    QStringList filters;
    filters << "*.sav"; // 假设存档文件的扩展名为.sav
    dir.setNameFilters(filters);
    QStringList fileList = dir.entryList();
    if (fileList.isEmpty()) {
        qDebug() << "No BD3 save files found.";
        return;
    }
    QString latestFile = dir.absoluteFilePath(fileList.first());

    // 构建目标路径
    QString fileName = QFileInfo(latestFile).fileName();
    QString destinationPath = QDir(destinationDir).filePath(fileName);

    // 拷贝文件
    if (QFile::copy(latestFile, destinationPath)) {
        qDebug() << "File copied successfully.";
    } else {
        qDebug() << "Failed to copy file.";
    }
}
