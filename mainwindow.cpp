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
    //setGeometry(0,0, len, len);
    setMaximumHeight(len);
    setMinimumHeight(len);
    setMaximumWidth(len);
    setMinimumWidth(len);
    currSort = 0;
    nextSort = 0;
    redraw = new QTimer(this);
    connect(redraw, SIGNAL(timeout()), this, SLOT(repaint()));
    redraw->start();
    sortr = new QTimer(this);
    reset(1);
    connect(sortr, SIGNAL(timeout()), this, SLOT(selectionSort()));
    sortr->start();
    auto tim = duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch());
    m = tim.count();
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
    ++cycles;
    ++focus;
    if (focus == len - pos) {
        if (pos + 2 == focus) {
            auto tim = duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch());
            n = tim.count();
            if (l > 2*(n - m))
                l = (n - m);
            else
                l = (l + (n - m)) / 2;
            cout << l << "  " << compares <<  "   " << cycles << endl;
            reset(1);
            tim = duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch());
            m = tim.count();
        } else {
            ++pos;
            focus = pos + 1;
        }
    }
}

void MainWindow::shakerSort() {
    compares += 2;
    ++cycles;
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
                auto tim = duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch());
                n = tim.count();
                if (l > 2*(n - m))
                    l = (n - m);
                else
                    l = (l + (n - m)) / 2;
                cout << l << "  " << compares <<  "   " << cycles << endl;
                reset(0);
                tim = duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch());
                m = tim.count();
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
                auto tim = duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch());
                n = tim.count();
                if (l > 2*(n - m))
                    l = (n - m);
                else
                    l = (l + (n - m)) / 2;
                cout << l << "  " << compares <<  "   " << cycles << endl;
                reset(0);
                tim = duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch());
                m = tim.count();
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
    ++cycles;
    ++focus;
    if (focus == len) {
        if (pos + 2 == focus) {
            auto tim = duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch());
            n = tim.count();
            if (l > 2*(n - m))
                l = (n - m);
            else
                l = (l + (n - m)) / 2;
            cout << l << "  " << compares <<  "   " << cycles << endl;
            reset(1);
            tim = duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch());
            m = tim.count();
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
    ++cycles;
    if (focus == (len - 1) - other) {
        if (pos) {
            focus = 0;
            pos = 0;
            ++other;
        } else {
            auto tim = duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch());
            n = tim.count();
            if (l > 2*(n - m))
                l = (n - m);
            else
                l = (l + (n - m)) / 2;
            cout << l << "  " << compares <<  "   " << cycles << endl;
            reset(0);
            tim = duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch());
            m = tim.count();
        }
    }
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QImage qi(size(), QImage::Format_ARGB32_Premultiplied);
    for (int i = 0; i < len; ++i)
        for (int y = 0; y < arr[i]; ++y)
            qi.setPixel(i, (len - y) - 1, i == focus ? 0xFFFF0000 : 0xFF00AA00);
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
    pos = 0;
    focus = f;
    other = 0;
    compares = cycles = 0;
    int loc;
    for (int i = 0; i < len; ++i) {
        loc = rand() % len;
        int temp = arr[i];
        arr[i] = arr[loc];
        arr[loc] = temp;
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    sortr->stop();
    delete sortr;
    sortr = new QTimer(this);
    if (event->key() == Qt::Key_1) {
        connect(sortr, SIGNAL(timeout()), this, SLOT(selectionSort()));
        reset(1);
        currSort = 0;
    }
    else if (event->key() == Qt::Key_2) {
        connect(sortr, SIGNAL(timeout()), this, SLOT(bubbleSort()));
        reset(0);
        currSort = 1;
    }
    else if (event->key() == Qt::Key_3) {
        connect(sortr, SIGNAL(timeout()), this, SLOT(frankenSort()));
        reset(1);
        currSort = 2;
    }
    else if (event->key() == Qt::Key_4) {
        connect(sortr, SIGNAL(timeout()), this, SLOT(shakerSort()));
        reset(0);
        currSort = 3;
    }
    auto tim = duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch());
    m = tim.count();
    sortr->start();
}

MainWindow::~MainWindow()
{
    delete redraw;
    delete sortr;
    delete ui;
}
