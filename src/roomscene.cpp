#include "roomscene.h"
#include "settings.h"

#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QGraphicsSceneMouseEvent>
#include "carditem.h"
#include "engine.h"

RoomScene::RoomScene()
{
    setBackgroundBrush(Config.BackgroundBrush);
    skill_label = addSimpleText(Config.UserName, Config.BigFont);
    skill_label->setPos(-400, -100);

	QStringList generalList{"caocao", "liubei", "sunquan", "simayi", "guojia", "zhugeliang", "zhouyu"};
    for(QString general : generalList){
		addGeneral(general);
    }
  
	dashboard = new Dashboard;
	dashboard->setGeneral(Engine::getInstance()->getGeneral(Config.userGeneral));

	for (int i = 0; i < 5; i++) {
		Card *card = Engine::getInstance()->getCard(qrand() % 108);
		if (card)
			dashboard->addCard(card);
	}

	addItem(dashboard);

	avatar = dashboard->getAvatar();	

	enterAnimation();
}

void RoomScene::updatePhotos()
{
	QParallelAnimationGroup *group = new QParallelAnimationGroup(this);

	int i;
	for (i = 0; i < photos.size(); i++) {
		Photo *photo = photos[i];
		QPropertyAnimation *translation = new QPropertyAnimation(photo, "x");
		translation->setEndValue(i * photo->boundingRect().width() + Config.Rect.x());
		translation->setEasingCurve(QEasingCurve::OutBounce);

		group->addAnimation(translation);
	}

	group->start(QAbstractAnimation::DeleteWhenStopped);
}

void RoomScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsScene::mousePressEvent(event);
    if(event->button() == Qt::RightButton){
        // use skill
    }
}

void RoomScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsScene::mouseMoveEvent(event);

	QGraphicsObject *obj = static_cast<QGraphicsObject*>(focusItem());
	CardItem *card = qobject_cast<CardItem*>(obj);
	if (!card || !card->isUnderMouse())
		return;

	foreach(Photo *photo, photos) {
		if (photo->isUnderMouse()) {
			photo->setSelected(true);
			break;
		}
	}
	if (avatar->isUnderMouse()) {
		avatar->setSelected(true);
	}
}

void RoomScene::showBust(const QString &name)
{
	QString filename = "generals/bust/" + name + ".png";
	if (!bust) {
		bust = new Pixmap(filename);
		bust->shift();
		addItem(bust);
	}
	else
		bust->changePixmap(filename);

	QPropertyAnimation *appear = new QPropertyAnimation(bust, "scale");
	appear->setStartValue(0.2);
	appear->setEndValue(1.0);

	appear->start();

	connect(appear, SIGNAL(finished()), bust, SIGNAL(visibleChanged()));
}

void RoomScene::enterAnimation()
{
	QParallelAnimationGroup *group = new QParallelAnimationGroup(this);

	qreal photoWidth;
	if (!_generals.isEmpty()) {
		photoWidth = _generals.front()->boundingRect().width();

		qreal x = Config.Rect.x();
		qreal y = Config.Rect.y() + 10;		
		for (auto generalPhoto : _generals) {
			int duration = 1500.0 * qrand() / RAND_MAX;
			QPropertyAnimation *translation = new QPropertyAnimation(generalPhoto.data(), "pos");
			translation->setEndValue(QPointF(x, y));
			translation->setEasingCurve(QEasingCurve::OutBounce);
			translation->setDuration(duration);

			group->addAnimation(translation);
			x += photoWidth;
		}
	}
		
	QPointF start_pos(Config.Rect.topLeft());
	QPointF end_pos(Config.Rect.x(), Config.Rect.bottom() - dashboard->boundingRect().height());
	int duration = 1500;

	QPropertyAnimation *translation = new QPropertyAnimation(dashboard, "pos");
	translation->setStartValue(start_pos);
	translation->setEndValue(end_pos);
	translation->setEasingCurve(QEasingCurve::OutBounce);
	translation->setDuration(duration);

	QPropertyAnimation *enlarge = new QPropertyAnimation(dashboard, "scale");
	enlarge->setStartValue(0.2);
	enlarge->setEndValue(1.0);
	enlarge->setEasingCurve(QEasingCurve::OutBounce);
	enlarge->setDuration(duration);

	group->addAnimation(translation);
	group->addAnimation(enlarge);

	group->start(QAbstractAnimation::DeleteWhenStopped);
}

void RoomScene::addGeneral(const QString& name)
{
	General *general = Engine::getInstance()->getGeneral(name);
	QSharedPointer<Photo> photo(new Photo);
	_generals << photo;
	photo->loadAvatar("generals/small/" + general->objectName() + ".png");
	addItem(photo.data());
}

