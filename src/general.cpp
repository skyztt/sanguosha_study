#include "general.h"
#include "engine.h"

General::General(const QString &name, const QString &kingdom, int max_hp, bool male, const QString &pixmap_dir)
	:kingdom(kingdom), max_hp(max_hp), male(male), is_lord(false), pixmap_dir(pixmap_dir)
{
	setObjectName(name);
	hp = max_hp;

	// initialize related pixmaps
}

General::General(const QString &name)
{
	setObjectName(name);

	// initialize other field using name
	General *copy = Engine::getInstance()->getGeneral(name);
	kingdom = copy->kingdom;
	hp = max_hp = copy->max_hp;
	male = copy->max_hp;
	is_lord = false;
}

int General::getMaxHp() const {
	return max_hp;
}

int General::getHp() const {
	return hp;
}

void General::setHp(int hp) {
	if (hp > 0 && hp <= max_hp)
		this->hp = hp;
}

QString General::getKingdom() const {
	return kingdom;
}

bool General::isMale() const {
	return male;
}

bool General::isFemale() const {
	return !male;
}

bool General::isWounded() const
{
	return hp != max_hp;
}

void General::enthrone() {
	max_hp++;
	hp = max_hp;
	is_lord = true;
}

QString General::getPixmapPath(const QString &category) {
	return QString("%1/%2/%3.png").arg(pixmap_dir).arg(category).arg(objectName());
}
