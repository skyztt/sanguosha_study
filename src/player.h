#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include "QUuid"

class Player : public QObject
{
	Q_OBJECT
public:
	Player(QObject *parent = nullptr);
	Player(const QString& jsonVal, QObject *parent = nullptr);
	~Player();
	QString getUuidString();
	QString name() {
		return name_;
	}
	QString avatar() {
		return avatar_;
	}

	void setName(const QString& name) {
		name_ = name;
	}
	void setAvatar(const QString& avatar) {
		avatar_ = avatar;
	}

	QString toJson();
private:
	QUuid id_;
	QString name_;
	QString avatar_;
};

#endif // PLAYER_H
