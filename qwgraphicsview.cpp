
#include "qwgraphicsview.h"
#include <QMouseEvent>
#include <QDebug>
#include <QGraphicsItem>

QWGraphicsView::QWGraphicsView(QWidget *parent)
    : QGraphicsView{parent}
{
    constexpr int longitude = 180*60;
//    constexpr int longitude = 180*60*60;
    constexpr int latitude = 90*60;
    QRectF rect(-longitude, -latitude, longitude*2, latitude*2);
    /**
     * When observing a scene using an untransformed view,
     * one unit on the scene is represented by one pixel on the screen.
     */
    QGraphicsScene *scene = new QGraphicsScene(rect);
    /**
     * The view does not take ownership of scene.
     * @todo delete scene
     */
    this->setScene(scene);
    for (int i = 0; i < longitude; ++i) {
        for (int j = 0; j < latitude; ++j) {
//            度
            if((i%60 == 0) && (j %60 == 0))
            {
                constexpr int R = 10;
                QGraphicsItem *item = scene->addEllipse(QRectF(-R, -R, R*2, R*2));
                QGraphicsTextItem *textItem = new QGraphicsTextItem(QString("%1,%2").arg(i/60).arg(j/60));
                textItem->setParentItem(item);
                const int w = textItem->boundingRect().width();
                const int h = textItem->boundingRect().height();
                textItem->setPos(-w/2, -h/2);
                item->setPos(i, j);
//                qDebug() << textItem->toPlainText();
            }
        }
    }
}



void QWGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    const QPoint p1 = event->pos();
    emit mouseMovePoint(p1);
    QGraphicsView::mouseMoveEvent(event);
}


void QWGraphicsView::mousePressEvent(QMouseEvent *event)
{
    const QPoint p1 = event->pos();
    emit mouseClicked(p1);
    QGraphicsView::mousePressEvent(event);
}
