#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>
#include <QPainter>

static int times = 0;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::paintEvent(QPaintEvent *event)
{
    /**
     * 窗口初始化，会调用两次！@todo
     * 在单一屏幕内拖拽、移动窗口不会重绘；在多个屏幕之间移动时会重绘。
     * 缩放窗口过程中会多次重绘，缩放过程越慢越多：点击窗口右上角最小化不会重绘；点击窗口最大化会重绘 3次
     * 在 windows 任务栏点击图标收缩窗口或 Alt+Tab 切换窗口时会重绘@todo；点击窗口右上角最小化不会重绘；
*/
    qDebug() << ++ times;

    const int W = this->width();
    const int H = this->height();
    /**
     * 画笔实际上是对窗口（定义了逻辑坐标系）操作的，
     * 但大多时候窗口对用户是透明的：因为默认视口区域等于设备区域，默认窗口区域也等于设备区域。
*/
    QPainter painter(this);
    const QRect rect(W/4, H/4, W/2, H/2);
    qDebug() << painter.viewport() << painter.window();
    painter.drawEllipse(rect);
//    启用坐标转换，（更改了视口区域）但窗口大小未作调整。所以物理坐标和逻辑坐标不再 1:1
    painter.setViewport(rect);
    qDebug() << painter.viewport() << painter.window();
    painter.drawEllipse(rect);
//    painter.scale(0.8, 0.8);
//    painter.drawEllipse(rect);
//    painter.scale(0.8, 0.8);
//    painter.drawEllipse(rect);
}
