#ifndef STARTSCENE_H
#define STARTSCENE_H

#include "button.h"

#include <QGraphicsScene>

class QAction;
class QTextEdit;
class Pixmap;
class Server;

class StartScene: public QGraphicsScene{
Q_OBJECT
public:
    StartScene();
	void addButton(QAction *action);
	void switchToServer(Server *server);
private:
	Pixmap *logo = nullptr;
	QList<Button*> buttons;
};

#endif // STARTSCENE_H
