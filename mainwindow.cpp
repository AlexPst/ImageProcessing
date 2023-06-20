
#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::openFileDialog);
    connect(ui->horizontalSlider, &QSlider::valueChanged, this, &MainWindow::blurImage);

}

void MainWindow::processNewImage(QString sourceFile, int blurValue)
{
    ui->label->setPixmap(QPixmap::fromImage(bluredImage(QImage(sourceFile), blurValue).scaled(ui->label->width(), ui->label->height(), Qt::KeepAspectRatio)));
}

void MainWindow::openFileDialog()
{
    imageSourcePath = QFileDialog::getOpenFileName(nullptr, "Open image for blur", "", "image files(*.jpg)");

   if(QFileInfo::exists(imageSourcePath))
    {
        processNewImage(imageSourcePath, ui->horizontalSlider->value());
    }
}


void MainWindow::blurImage()
{
    //int val = ui->horizontalSlider->value();
    if(QFileInfo::exists(imageSourcePath))
    {
        processNewImage(imageSourcePath, ui->horizontalSlider->value());
       //processNewImage(imageSourcePath, val);
    }else
    {
        ui->label->setText("Image path is not set. Please press \"Open image\" button.");
    }
}

QImage MainWindow::bluredImage(QImage imageSource, int blurVal)
{

    if(imageSource.isNull()){return QImage();}
    QGraphicsScene scene;
    QGraphicsPixmapItem item;
    item.setPixmap(QPixmap::fromImage(imageSource));
    auto* blur = new QGraphicsBlurEffect;
    blur->setBlurRadius(blurVal);
    item.setGraphicsEffect(blur);
    scene.addItem(&item);
    QImage result(imageSource.size(), QImage::Format_ARGB32);
    result.fill(Qt::transparent);
    QPainter painter(&result);
    scene.render(&painter, QRectF(), QRectF(0,0, imageSource.width(), imageSource.height()));
    return result;
}

QString MainWindow::getImageSourcePath()
{
    return imageSourcePath;
}

MainWindow::~MainWindow()
{
    delete ui;
}


