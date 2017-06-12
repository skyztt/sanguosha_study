#ifndef STARTSCENE_H
#define STARTSCENE_H

#include "button.h"

#include <QGraphicsScene>

class QAction;
class QTextEdit;
class Pixmap;

class StartScene: public QGraphicsScene{
Q_OBJECT
public:
    StartScene();
	void addButton(QAction *action);
	void leave();
private:
	Pixmap *logo = nullptr;
	QList<Button*> buttons;
	QTextEdit *server_log = nullptr;
private slots:
	void showServerLog();
};

#endif // STARTSCENE_H
