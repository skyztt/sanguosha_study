#ifndef ENGINE_H
#define ENGINE_H

#include <QScriptEngine>

class General;

class Engine : public QScriptEngine
{
Q_OBJECT
public:
    explicit Engine(QObject *parent = 0);
	void init();

	Q_INVOKABLE QObject *addGeneral(const QString &name, const QString &kingdom, int max_hp, bool male);
	Q_INVOKABLE void addTranslationTable(QVariantMap table);
private:
	QObject *generals = nullptr;
	QObject *translation = nullptr;
};

#endif // ENGINE_H
