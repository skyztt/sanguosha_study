#ifndef GENERAL_H
#define GENERAL_H

#include <QObject>

class General : public QObject
{
	Q_OBJECT
		Q_PROPERTY(QString kingdom READ getKingdom CONSTANT)
		Q_PROPERTY(int max_hp READ getMaxHp CONSTANT)
		Q_PROPERTY(int hp READ getHp WRITE setHp)
		Q_PROPERTY(bool male READ isMale STORED false CONSTANT)
		Q_PROPERTY(bool female READ isFemale STORED false CONSTANT)
		Q_PROPERTY(bool wounded READ isWounded STORED false)

public:
	explicit General(const QString &name, const QString &kingdom, int max_hp, bool male, const QString &pixmap_dir);
	General(const QString &name);

	// property getters/setters
	int getMaxHp() const;
	int getHp() const;
	void setHp(int hp);
	QString getKingdom() const;
	bool isMale() const;
	bool isFemale() const;
	bool isWounded() const;

	// make this general to lord, thus enable its lord skill and increase its maximal hp
	void enthrone();

	void setIsLeader(bool bLeader) {
		leader = bLeader;
	}

	QString getPixmapPath(const QString &category);
private:
	QString kingdom;
	int max_hp, hp;
	bool male = true;
	bool is_lord = false;
	bool leader = false;
	QString pixmap_dir;
};

#endif // GENERAL_H
