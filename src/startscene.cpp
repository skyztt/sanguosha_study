#include "startscene.h"

#include "roomscene.h"
#include "QStyle"

StartScene::StartScene(){
    setBackgroundBrush(QBrush(QPixmap(":/images/background.png")));

    QGraphicsPixmapItem *logo = addPixmap(QPixmap(":/images/logo.png"));
    logo->setOffset(-logo->pixmap().width()/2, -logo->pixmap().height()/2);
    logo->setPos(0, -Config.Rect.height()/4);

    //my e-mail address
    QFont email_font(Config.SmallFont);
    email_font.setStyle(QFont::StyleItalic);
    QGraphicsSimpleTextItem *email_text = addSimpleText("moligaloo@gmail.com", email_font);
    email_text->setBrush(Qt::white);
    email_text->setPos(Config.Rect.width()/2 - email_text->boundingRect().width(),
                       Config.Rect.height()/2 - email_text->boundingRect().height());
}

void StartScene::addButton(QAction *action)
{
	qreal menu_height = Config.BigFont.pixelSize();
	Button *button = new Button(action);
	button->setPos(0, (btnCount_++ - 0.8)*menu_height);

	addItem(button);
}

