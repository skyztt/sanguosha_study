#include "player.h"
#include <QJsonObject> 
#include <QJsonDocument> 

Player::Player(QObject *parent)
	: QObject(parent),
	id_(QUuid::createUuid())
{

}

Player::Player(const QString& jsonVal, QObject *parent /*= nullptr*/)
	: QObject(parent)
{
	QJsonDocument loadDoc(QJsonDocument::fromJson(jsonVal.toUtf8()));
	QJsonObject jo = loadDoc.object();
	id_ = QUuid(jo["uuid"].toString());
	name_ = jo["name"].toString();
	avatar_ = jo["avatar"].toString();
}

Player::~Player()
{

}

QString Player::getUuidString()
{
	return id_.toString();
}

QString Player::toJson()
{
	QJsonObject outObj;
	outObj["uuid"] = getUuidString();
	outObj["name"] = name_;
	outObj["avatar"] = avatar_;

	QJsonDocument saveDoc(outObj);
	return saveDoc.toJson();
}
