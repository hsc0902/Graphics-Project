#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QColorDialog>
#include <QFileDialog>
#include "myscene.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_shape1_toggled(bool checked);

    void on_shape2_toggled(bool checked);

    void on_shape3_toggled(bool checked);

    void on_shape4_toggled(bool checked);

    void on_fill_toggled(bool checked);

    void on_color_clicked();

    void on_cut_toggled(bool checked);

    void on_shape5_toggled(bool checked);

    void on_save_clicked();

private:
    Ui::MainWindow *ui;

private:
    Myscene scene;

};

#endif // MAINWINDOW_H
