#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scene.setSceneRect(0, 0, 1260, 540);
    ui->graphicsView->setScene(&scene);
    ui->graphicsView->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_shape1_toggled(bool checked)
{
    if(checked)
    {
        mode_index=1;
        shape_index=1;
    }
    else
    {
        shape_index=0;
        mode_index=0;
    }
}

void MainWindow::on_shape2_toggled(bool checked)
{
    if(checked)
    {
        mode_index=1;
        shape_index=2;
    }
    else
    {
        mode_index=0;
        shape_index=0;
    }
}

void MainWindow::on_shape3_toggled(bool checked)
{
    if(checked)
    {
        mode_index=1;
        shape_index=3;
    }
    else
    {
        mode_index=0;
        shape_index=0;
    }
}

void MainWindow::on_shape4_toggled(bool checked)
{
    if(checked)
    {
        mode_index=1;
        shape_index=4;
    }
    else
    {
        mode_index=0;
        shape_index=0;
    }
}

void MainWindow::on_shape5_toggled(bool checked)
{
    if(checked)
    {
        mode_index=1;
        shape_index=5;
    }
    else
    {
        mode_index=0;
        shape_index=0;
    }
}

void MainWindow::on_fill_toggled(bool checked)
{
    if(checked)
        fill_index=1;
    else
        fill_index=0;
}

void MainWindow::on_cut_toggled(bool checked)
{
    if(checked)
        cut_index=1;
    else
        cut_index=0;
}

void MainWindow::on_color_clicked()
{
    QColor color = QColorDialog::getColor(Qt::red,this,tr("color"),QColorDialog::ShowAlphaChannel);
    pen_total.setColor(color);
}

void MainWindow::on_save_clicked()
{
    QString fileName;
    fileName = QFileDialog::getSaveFileName(this, tr("保存文件"), "", tr("Image Files (*.png *.jpg *.bmp)"));
    if (!fileName.isNull()) {
        qDebug()<<"START";
        QImage Save=QImage(1260,540, QImage::Format_RGB32);
        Save.fill(Qt::white);
        QPainter painter;
        painter.begin(&Save);
        scene.render(&painter);
        painter.end();
        Save.save(fileName);
        qDebug()<<"END";
    }
}
