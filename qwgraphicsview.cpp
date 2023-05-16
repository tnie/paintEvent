
#include "qwgraphicsview.h"
#include <QMouseEvent>
#include <QDebug>
#include <QGraphicsItem>

QWGraphicsView::QWGraphicsView(QWidget *parent)
    : QGraphicsView{parent}
{
    assert(!this->hasMouseTracking());
    assert(!this->viewport()->hasMouseTracking());

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
                QGraphicsSimpleTextItem *textItem = new QGraphicsSimpleTextItem(QString("%1,%2").arg(i/60).arg(j/60));
//                Enable mouse tracking if the item accepts hover events or has a cursor set.
                textItem->setParentItem(item);
                const int w = textItem->boundingRect().width();
                const int h = textItem->boundingRect().height();
                textItem->setPos(-w/2, -h/2);
                item->setPos(i, j);
//                qDebug() << textItem->toPlainText();
            }
        }
    }
    qDebug() << "View hasMouseTracking" << this->hasMouseTracking();
    /**
     * @todo 为什么 viewport 的 mouseTracking 属性就变了呢？
     * @note: QGraphicsTextItem accepts hover events by default.
     */
    qDebug() << "viewport hasMouseTracking" << this->viewport()->hasMouseTracking();
}


/**
 * @brief QWGraphicsView::mouseMoveEvent
 * @param event
 * @todo without setMouseTracking(true) 也可以？为什么？
 * @note 键鼠事件来自 viewport 而非 view
 * For convenience, QAbstractScrollArea makes all viewport events available in the virtual viewportEvent() handler.
 * 映射 view 的事件处理接口到 viewport 的键鼠事件！
 * QWidget's specialized handlers are remapped to viewport events in the cases where this makes sense.
 */

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
