#ifndef BUTTON_H
#define BUTTON_H

#include "settings.h"

#include <QGraphicsItem>
#include <QFont>
#include <QFontMetrics>

class QAction;

class Button : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit Button(const QString &label);
	explicit Button(QAction *action);

    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual QRectF boundingRect() const;

protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QString label;
    qreal width, height;
signals:
    void clicked();
};

#endif // BUTTON_H
