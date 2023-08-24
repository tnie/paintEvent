
#ifndef QWGRAPHICSVIEW_H
#define QWGRAPHICSVIEW_H


#include <QGraphicsView>

class ViewMouseSubscriber;

class QWGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit QWGraphicsView(QWidget *parent = nullptr);

    ViewMouseSubscriber *mouseSubscriber() const;
    void setMouseSubscriber(ViewMouseSubscriber *newMouseSubscriber);

signals:
    void mouseMovePoint(const QPoint&);
    void mouseClicked(const QPoint&);

    // QWidget interface
protected:
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;

private:
    ViewMouseSubscriber * mouseSubscriber_;
};

#endif // QWGRAPHICSVIEW_H
