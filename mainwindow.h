
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsBlurEffect>
#include <QGraphicsPixmapItem>
#include <QPainter>

#include <QDir>
#include <QFileDialog>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    QImage bluredImage(QImage source, int blurVal);
    void openFileDialog();
    void processNewImage(QString sourceFile, int blurValue);
    void blurImage();

    QString getImageSourcePath();

    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QFileDialog *fileDialog;
    QString imageSourcePath = "";
    int blurValue;
};

#endif // MAINWINDOW_H
