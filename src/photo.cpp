#include "photo.h"
#include "settings.h"

#include <QPainter>
#include <QMimeData>
#include <QDrag>
#include <QGraphicsScene>
#include "card.h"
#include "QMessageBox"
#include "QGraphicsSceneEvent"

Photo::Photo()
    :Pixmap(":/images/photo-back.png"),
    avatar_frame(":/images/avatar-frame.png")
{
	setAcceptHoverEvents(true);
}

void Photo::loadAvatar(const QString &filename){
    avatar.load(filename);
    avatar = avatar.scaled(QSize(128,58));
}

void Photo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Pixmap::paint(painter, option, widget);
    if(!avatar.isNull()){
        painter->drawPixmap(1, 13, avatar);
        painter->drawPixmap(0, 10, avatar_frame);
    }
}

void Photo::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
	QGraphicsObject *obj = static_cast<QGraphicsObject*>(scene()->focusItem());
	Card *card = qobject_cast<Card*>(obj);
	if (card && card->contains(card->mapFromItem(this, event->pos()))) {
		QMessageBox::information(NULL, "", card->objectName());
	}
}


