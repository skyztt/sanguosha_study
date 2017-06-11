#include "button.h"

#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QSound>
#include <QMediaPlayer>

Button::Button(const QString &label)
    :label(label){

    QFontMetrics metrics(Config.BigFont);
    width = metrics.width(label);
    height = metrics.height();

    setFlags(QGraphicsItem::ItemIsFocusable);
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::LeftButton);
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *){
    setFocus(Qt::MouseFocusReason);
	
	QMediaPlayer* player = new QMediaPlayer;
	player->setMedia(QUrl::fromLocalFile(Config.ButtonHoverSource));
	player->play();
	connect(player, &QMediaPlayer::mediaStatusChanged, this, [player](QMediaPlayer::MediaStatus status) {
		if (status == QMediaPlayer::EndOfMedia) {
			player->deleteLater();
		}
	});
    //Phonon::MediaObject *effect = Phonon::createPlayer(Phonon::MusicCategory, Config.ButtonHoverSource);
   // effect->play();

    //connect(effect, SIGNAL(finished()), effect, SLOT(deleteLater()));
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event){
    event->accept();
}

void Button::mouseReleaseEvent(QGraphicsSceneMouseEvent *){
	//QSound::play("audio/button-down.mp3");
	//QSound::play("I:/sanguosha/sanguosha_study/audio/button-down.mp3");

	QMediaPlayer* player = new QMediaPlayer;
	player->setMedia(QUrl::fromLocalFile(Config.ButtonDownSource));
	player->play();
	connect(player, &QMediaPlayer::mediaStatusChanged, this, [player](QMediaPlayer::MediaStatus status) {
		if (status == QMediaPlayer::EndOfMedia) {
			player->deleteLater();
		}
	});

    //Phonon::MediaObject *effect = Phonon::createPlayer(Phonon::MusicCategory, Config.ButtonDownSource);
    //effect->play();

    emit clicked();
}

QRectF Button::boundingRect() const{
    return QRectF(-width/2 -2, -height/2 -8, width + 10, height + 10);
}

void Button::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    painter->setFont(Config.BigFont);
    qreal font_size = Config.BigFont.pixelSize();

    if(hasFocus()){
        painter->setPen(QPen(Qt::black));
        painter->drawText(QPointF(8 - width/2, 8 + font_size/2), label);

        painter->setPen(QPen(Qt::white));
        painter->drawText(QPointF(-2 - width/2,-2 + font_size/2),label);
    }else{
        painter->setPen(QPen(Qt::black));
        painter->drawText(QPointF(5 - width/2, 5 + font_size/2), label);

        painter->setPen(QPen(Qt::white));
        painter->drawText(QPointF(-width/2, font_size/2),label);
    }
}
