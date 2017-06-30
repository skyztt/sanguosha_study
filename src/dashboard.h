#ifndef DASHBOARD_H
#define DASHBOARD_H

#include "pixmap.h"
#include "general.h"

#include <QPushButton>

class CardItem;
class Card;

class Dashboard : public Pixmap
{
    Q_OBJECT

public:
    Dashboard();
	void addCard(Card* card);
    void addCardItem(CardItem *card);
	void setGeneral(General *general);
	Pixmap *getAvatar();

protected:
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QList<CardItem*> cards;
    General *general = nullptr;
    QPixmap magatamas[5];
	Pixmap *avatar = nullptr;
    bool use_skill;

    void adjustCards();

private slots:
    void sortCards(int sort_type);
};

#endif // DASHBOARD_H
