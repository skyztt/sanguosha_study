#ifndef ROOMSCENE_H
#define ROOMSCENE_H

#include "photo.h"
#include "dashboard.h"
#include "card.h"

#include <QGraphicsScene>

class RoomScene : public QGraphicsScene
{
    Q_OBJECT
public:
    RoomScene();
	void updatePhotos();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

private:
	QList<Photo*> photos;
    Dashboard *dashboard = nullptr;
    Pixmap *pile;
    QGraphicsSimpleTextItem *skill_label;
	Pixmap *avatar = nullptr;
};

#endif // ROOMSCENE_H
