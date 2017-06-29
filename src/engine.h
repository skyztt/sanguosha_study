#ifndef ENGINE_H
#define ENGINE_H

#include <QScriptEngine>

class General;

class Engine : public QScriptEngine
{
Q_OBJECT
public:
    explicit Engine(QObject *parent = 0);

	Q_INVOKABLE QObject *addGeneral(const QString &name, const QString &kingdom, int max_hp, bool male);
	Q_INVOKABLE QObject *addCard(const QString &card_class, const QString &suit_str, int number);
	Q_INVOKABLE QObject *addCardClass(const QString &class_name);

	Q_INVOKABLE void addTranslationTable(const QScriptValue &table);
	Q_INVOKABLE QString translate(const QString &to_translate);
	
	Q_INVOKABLE QScriptValue doScript(const QString &filename);
	Q_INVOKABLE void alert(const QString &message);
	Q_INVOKABLE void quit(const QString &reason = QString());

	General *getGeneral(const QString &name);
private:
	QObject *generals = nullptr;
	QObject *translation = nullptr;
	QObject *card_classes = nullptr;
};

extern Engine *Sanguosha;

#endif // ENGINE_H
