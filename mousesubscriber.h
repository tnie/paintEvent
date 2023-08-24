#ifndef MOUSESUBSCRIBER_H
#define MOUSESUBSCRIBER_H


class QMouseEvent;
class QWGraphicsView;
class QGraphicsItem;

class ViewMouseSubscriber
{
public:
    virtual void on_mouseMoveEvent(QMouseEvent *event, QWGraphicsView * view) {} ;
    virtual void on_mousePressEvent(QMouseEvent *event, QWGraphicsView * view) =0;
};

class PointMaker: public ViewMouseSubscriber
{
private:
    QGraphicsItem *item_ = nullptr; // single
    // MouseSubscriber interface
public:
    virtual void on_mousePressEvent(QMouseEvent *event, QWGraphicsView * view) override;
};

class LineMaker: public ViewMouseSubscriber
{
private:
    QGraphicsItem *item1_ = nullptr; // start
    QGraphicsItem *item2_ = nullptr; // end
    QGraphicsItem *line_ = nullptr;
    // MouseSubscriber interface
public:
    virtual void on_mouseMoveEvent(QMouseEvent *event, QWGraphicsView *view) override;
    virtual void on_mousePressEvent(QMouseEvent *event, QWGraphicsView *view) override;
};



#endif // MOUSESUBSCRIBER_H
