
#include "qwgraphicsview.h"
#include <QMouseEvent>
#include <QDebug>
#include <QGraphicsItem>

QWGraphicsView::QWGraphicsView(QWidget *parent)
    : QGraphicsView{parent}
{
    constexpr int longitude = 180*60;
    constexpr int latitude = 90*60;
    QRectF rect(-longitude, -latitude, longitude*2, latitude*2);
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
                QGraphicsItem *item = scene->addEllipse(QRectF(-5, -5, 10, 10));
                QGraphicsItem *textItem = new QGraphicsTextItem(QString("%1,%2").arg(i/60).arg(j/60));
                textItem->setParentItem(item);
                item->setPos(i, j);
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
