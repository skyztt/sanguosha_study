#include "pixmap.h"

#include <QPainter>
#include "QGraphicsEffect"

Pixmap::Pixmap(const QString &filename):pixmap(filename)
{
    setTransformOriginPoint(pixmap.width()/2, pixmap.height()/2);
}

QRectF Pixmap::boundingRect() const{
    return QRectF(0, 0, pixmap.width(), pixmap.height());
}

void Pixmap::changePixmap(const QString &filename) {
	pixmap.load(filename);
}

void Pixmap::shift() {
	moveBy(-pixmap.width() / 2, -pixmap.height() / 2);
}

QVariant Pixmap::itemChange(GraphicsItemChange change, const QVariant &value)
{
	if (change == QGraphicsItem::ItemSelectedChange) {
		if (value.toBool()) {
			QGraphicsColorizeEffect *effect = new QGraphicsColorizeEffect(this);
			effect->setColor(QColor(0xCC, 0x00, 0x00));
			setGraphicsEffect(effect);
		}
		else
			setGraphicsEffect(NULL);
	}

	return QGraphicsObject::itemChange(change, value);
}

void Pixmap::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    painter->drawPixmap(0, 0, pixmap);
}
