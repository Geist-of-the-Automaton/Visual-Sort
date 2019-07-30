#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include <iostream>
#include <fstream>
#include <QImage>
#include <QKeyEvent>
#include <time.h>
#include <chrono>
#include <string>;
using std::string;
using std::cout;
using std::endl;
using namespace std::chrono;
using std::chrono::milliseconds;
const int len = 300;
const string names[] = {"Selection Sort", "Bubble Sort", "Franken Sort", "Shaker Sort"};


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);

    void reset(int f);
    Ui::MainWindow *ui;
    QTimer *redraw;
    QTimer *sortr;
    int arr[len];
    int pos, focus, other;
    long long l, m, n;
    int compares, cycles;
    int currSort;
    int nextSort;



public slots:
    //=================BASED ON 100 LENGTH ARRAYS==============
    void frankenSort();     //       1.5 sec
    void selectionSort();   //       2.8 sec
    void bubbleSort();   //       2.8 sec
    void shakerSort();      //       2.1 sec
    //=============DIVIDE BY 60 TO GET NON-GUI TIMES===========
};

#endif // MAINWINDOW_H
