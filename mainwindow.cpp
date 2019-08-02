#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    delete ui->mainToolBar;
    for (int i = 0; i < len; ++i)
        arr[i] = i;
    setMaximumHeight(len);
    setMinimumHeight(len);
    setMaximumWidth(len);
    setMinimumWidth(len);
    currSort = 0;
    redraw = new QTimer(this);
    connect(redraw, SIGNAL(timeout()), this, SLOT(repaint()));
    redraw->start();
    sortr = new QTimer(this);
    reset(1);
    connect(sortr, SIGNAL(timeout()), this, SLOT(selectionSort()));
    sortr->start();
    reset(1);
}

void MainWindow::frankenSort() {
    if (arr[pos] > arr[focus]) {
        int temp = arr[pos];
        arr[pos] = arr[focus];
        arr[focus] = temp;
    }
    if (arr[focus - 1] > arr[focus]) {
        int temp = arr[focus - 1];
        arr[focus - 1] = arr[focus];
        arr[focus] = temp;
    }
    compares += 2;
    ++focus;
    if (focus == len - pos) {
        if (pos + 2 == focus) {
            reset(1);
        } else {
            ++pos;
            focus = pos + 1;
        }
    }
}

void MainWindow::shakerSort() {
    compares += 2;
    if (other < 0) {
        if (arr[focus] < arr[focus - 1]) {
            int temp = arr[focus];
            arr[focus] = arr[focus  - 1];
            arr[focus - 1] = temp;
            pos = 1;
        }
        --focus;
        if (focus == 0 - (other / 2)) {
            if (pos) {
                pos = 0;
                --other;
                other = -other;
            } else {
                reset(0);
            }
        }
    }
    else {
        if (arr[focus] > arr[focus + 1]) {
            int temp = arr[focus];
            arr[focus] = arr[focus + 1];
            arr[focus + 1] = temp;
            pos = 1;
        }
        ++focus;
        if (focus == (len - 1) - (other / 2)) {
            if (pos) {
                pos = 0;
                ++other;
                other = -other;
                --focus;
            } else {
                reset(0);
            }
        }
    }
}

void MainWindow::selectionSort() {
    if (arr[pos] > arr[focus]) {
        int temp = arr[pos];
        arr[pos] = arr[focus];
        arr[focus] = temp;
    }
    ++compares;
    ++focus;
    if (focus == len) {
        if (pos + 2 == focus) {
            reset(1);
        } else {
            ++pos;
            focus = pos + 1;
        }
    }
}

void MainWindow::doubleSort() {
    if (arr[pos] > arr[focus]) {
        int temp = arr[pos];
        arr[pos] = arr[focus];
        arr[focus] = temp;
    }
    if (arr[len - (pos + 1)] < arr[focus]) {
        int temp = arr[len - (pos + 1)];
        arr[len - (pos + 1)] = arr[focus];
        arr[focus] = temp;
        if (arr[pos] > arr[focus]) {
            int temp = arr[pos];
            arr[pos] = arr[focus];
            arr[focus] = temp;
        }
    }
    compares += 2;
    ++focus;
    if (focus == len - (pos + 1)) {
        if (pos == (len / 2) - 2) {
            reset(1);
        } else {
            ++pos;
            focus = pos + 1;
        }
    }
}

void MainWindow::bubbleSort() {
    if (arr[focus] > arr[focus + 1]) {
        int temp = arr[focus];
        arr[focus] = arr[focus + 1];
        arr[focus + 1] = temp;
        pos = 1;
    }
    ++focus;
    ++compares;
    if (focus == (len - 1) - other) {
        if (pos) {
            focus = 0;
            pos = 0;
            ++other;
        } else {
            reset(0);
        }
    }
}

void MainWindow::insertSort() {
    for (int j = pos; j < focus; ++j) {
        compares += 2;
        if (arr[focus] < arr[j]) {
            int temp = arr[focus];
            for (int i = focus - 1; i >= j; --i) {
                arr[i + 1] = arr[i];
                ++compares;
            }
            arr[j] = temp;
            break;
        }
    }
    ++focus;
    if (focus == len) {
        reset(1);
    }
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QImage qi(size(), QImage::Format_ARGB32_Premultiplied);
    for (int i = 0; i < len; ++i)
        for (int y = 0; y < arr[i]; ++y)
            qi.setPixel(i, (len - y) - 1, i == focus ? 0xFFFFBB00 : 0xFF009900);
    QPainter qp(this);
    qp.drawImage(0,0, qi);
    QColor color (0, 0, 0);
    qp.setPen(color);
    QFont fon = qp.font();
    fon.setPointSize(12);
    qp.setFont(fon);
    qp.drawText(QPoint(12,12), names[currSort].data());
}

void MainWindow::reset(int f) {
    cout << compares << endl;
    pos = 0;
    focus = f;
    other = 0;
    compares = 0;
    int loc;
    for (int i = 0; i < len; ++i) {
        loc = rand() % len;
        int temp = arr[i];
        arr[i] = arr[loc];
        arr[loc] = temp;
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    int key = event->key();
    if (key < Qt::Key_1 || key > Qt::Key_6)
        return;
    sortr->stop();
    delete sortr;
    sortr = new QTimer(this);
    if (key == Qt::Key_1) {
        connect(sortr, SIGNAL(timeout()), this, SLOT(selectionSort()));
        reset(1);
        currSort = 0;
    }
    else if (key == Qt::Key_2) {
        connect(sortr, SIGNAL(timeout()), this, SLOT(bubbleSort()));
        reset(0);
        currSort = 1;
    }
    else if (key == Qt::Key_3) {
        connect(sortr, SIGNAL(timeout()), this, SLOT(frankenSort()));
        reset(1);
        currSort = 2;
    }
    else if (key == Qt::Key_4) {
        connect(sortr, SIGNAL(timeout()), this, SLOT(shakerSort()));
        reset(0);
        currSort = 3;
    }
    else if (key == Qt::Key_5) {
        connect(sortr, SIGNAL(timeout()), this, SLOT(doubleSort()));
        reset(1);
        currSort = 4;
    }
    else if (key == Qt::Key_6) {
        connect(sortr, SIGNAL(timeout()), this, SLOT(insertSort()));
        reset(1);
        currSort = 5;
    }
    sortr->start();
}

MainWindow::~MainWindow()
{
    delete redraw;
    delete sortr;
    delete ui;
}
