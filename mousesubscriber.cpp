#include "mousesubscriber.h"
#include <QMouseEvent>
#include "qwgraphicsview.h"
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QRect>

void PointMaker::on_mousePressEvent(QMouseEvent *event, QWGraphicsView *view)
{
    if(nullptr == view)
    {
        return;
    }
    if(QGraphicsScene * scene = view->scene())
    {
        const QPoint p1 = event->pos();
        constexpr int R = 10;
        if(item_)
        {
            scene->removeItem(item_);
            delete item_;
        }
        QGraphicsItem *item = scene->addEllipse(QRectF(-R, -R, R*2, R*2));
        constexpr int r = 1;
        QGraphicsEllipseItem * c = new QGraphicsEllipseItem(QRectF(-r, -r, r*2, r*2), item);
        item->setPos(view->mapToScene(p1));
        item_ = item;
    }
}


void LineMaker::on_mouseMoveEvent(QMouseEvent *event, QWGraphicsView *view)
{
    if(nullptr == view)
    {
        return;
    }
    if(QGraphicsScene * scene = view->scene())
    {
        const QPoint p1 = event->pos();
        const QPointF p2 = view->mapToScene(p1);
        if(item1_ && nullptr == item2_)
        {
            QLineF line(item1_->pos(), p2);
            QGraphicsLineItem *item = scene->addLine(line);
            if(line_)
            {
                scene->removeItem(line_);
                delete line_;   line_= nullptr;
            }
            line_ = item;
        }
    }
}

void LineMaker::on_mousePressEvent(QMouseEvent *event, QWGraphicsView *view)
{
    if(nullptr == view)
    {
        return;
    }
    if(QGraphicsScene * scene = view->scene())
    {
        const QPoint p1 = event->pos();
        constexpr int R = 10;
        if(item1_ && item2_)
        {
            scene->removeItem(item1_);
            scene->removeItem(item2_);
            delete item1_;  item1_ = nullptr;
            delete item2_;  item2_ = nullptr;
            if(line_)
            {
                scene->removeItem(line_);
                delete line_;   line_= nullptr;
            }
        }
        QGraphicsItem *item = scene->addEllipse(QRectF(-R, -R, R*2, R*2));
        constexpr int r = 1;
        QGraphicsEllipseItem * c = new QGraphicsEllipseItem(QRectF(-r, -r, r*2, r*2), item);
        item->setPos(view->mapToScene(p1));
        if(nullptr == item1_)
            item1_ = item;
        else if(nullptr == item2_)
        {
            item2_ = item;
            QLineF line(item1_->pos(), item2_->pos());
            QGraphicsLineItem *lineItem = scene->addLine(line);
            if(line_)
            {
                scene->removeItem(line_);
                delete line_;   line_= nullptr;
            }
            line_ = lineItem;
        }
    }
}
