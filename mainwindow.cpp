﻿#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>
#include <QPainter>
#include <QLabel>
#include <QGraphicsItem>
#include "mousesubscriber.h"

namespace  {
    static int times = 0;
    constexpr static double ZoomIn = 1.2;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    状态栏标签
    if(QLabel *labViewCord = new QLabel("labViewCord"))
    {
        labViewCord->setMinimumWidth(150);
        ui->statusbar->addWidget(labViewCord);
        if(QLabel *labSceneCord = new QLabel("labSceneCord"))
        {
            labSceneCord->setMinimumWidth(150);
            ui->statusbar->addWidget(labSceneCord);
            connect(ui->graphicsView, &QWGraphicsView::mouseMovePoint, this, [=](const QPoint& p1){
                labViewCord->setText(QString::asprintf("View :%d, %d", p1.x(), p1.y()));
                /**
                 * 场景是空的，坐标转换也是可以的？@todo
                 * 试验结果，此时场景坐标系以视图窗口中心点为远点，左上角(-w/2,-h/2)右下角(w/2,h/2)
                 */
//                assert(nullptr == ui->graphicsView->scene());
                const QPointF pointScene = ui->graphicsView->mapToScene(p1);
                labSceneCord->setText(QString("Scene :%1, %2").arg(pointScene.x()).arg(pointScene.y()));
            });
        }
    }
    if(QLabel *labItemCord = new QLabel("labItemCord"))
    {
        labItemCord->setMinimumWidth(150);
        ui->statusbar->addWidget(labItemCord);
        connect(ui->graphicsView, &QWGraphicsView::mouseClicked, this, [=](const QPoint& p1){
            const QPointF pointScene = ui->graphicsView->mapToScene(p1);
            if(QGraphicsScene *scene = ui->graphicsView->scene())
            {
                if(QGraphicsItem *item = scene->itemAt(pointScene, ui->graphicsView->transform()))
                {
                    const QPointF pointItem = item->mapFromScene(pointScene);
                    labItemCord->setText(QString("Item :%1, %2").arg(pointItem.x()).arg(pointItem.y()));
                }
                else
                {
                    labItemCord->clear();
                }
            }
        });
    }
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
     * 但大多时候窗口对用户是透明的：因为默认 视口区域等于设备区域，默认窗口区域也等于设备区域。
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

void MainWindow::on_btnZoomIn_clicked()
{
    ui->graphicsView->scale(ZoomIn, ZoomIn);
}

void MainWindow::on_btnZoomOut_clicked()
{
    ui->graphicsView->scale(1/ZoomIn, 1/ZoomIn);
}


void MainWindow::on_actionp_triggered()
{
    static PointMaker pointSubscriber;
    ui->graphicsView->setMouseSubscriber(&pointSubscriber);
}


void MainWindow::on_actionl_triggered()
{
    static LineMaker lineSubscriber;
    ui->graphicsView->setMouseSubscriber(&lineSubscriber);
}

