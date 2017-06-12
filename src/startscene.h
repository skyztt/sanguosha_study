#ifndef STARTSCENE_H
#define STARTSCENE_H

#include "button.h"

#include <QGraphicsScene>

class QAction;

class StartScene: public QGraphicsScene{
Q_OBJECT
public:
    StartScene();
	void addButton(QAction *action);
private:
	int btnCount_ = 0;
};

#endif // STARTSCENE_H
