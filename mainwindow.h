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
const string names[] = {"Selection Sort", "Bubble Sort", "Franken Sort", "Shaker Sort", "Double Selection Sort", "Insertion Sort"};


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
    int compares;
    int currSort;



public slots:
    void frankenSort();
    void selectionSort();
    void bubbleSort();
    void shakerSort();
    void doubleSort();
    void insertSort();
};

#endif // MAINWINDOW_H
