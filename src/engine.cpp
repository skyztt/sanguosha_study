#include "engine.h"

#include <QFile>
#include <QStringList>
#include <QMessageBox>
#include <QScriptValueIterator>

#include "general.h"
#include "QString"
#include "card.h"
#include "cardclass.h"

Engine *Sanguosha = nullptr;

Engine::Engine(QObject *parent) :
    QScriptEngine(parent)
{
	globalObject().setProperty("sgs", newQObject(this));

	generals = new QObject(this);
	generals->setObjectName("generals");

	translation = new QObject(this);
	translation->setObjectName("translation");

	card_classes = new QObject(this);
	card_classes->setObjectName("card_classes");

	//qScriptRegisterMetaType()

	QStringList script_files;
	script_files << "init.js" << "cards.js" << "generals.js";
	foreach(QString filename, script_files) {
		doScript("scripts/" + filename);
	}
}

QObject * Engine::addGeneral(const QString &name, const QString &kingdom, int max_hp, bool male)
{
	General *general = new General(name, kingdom, max_hp, male);
	general->setParent(generals);
	return general;
}

QObject *Engine::addCard(const QString &name, const QString &suit_str, const QScriptValue& number_value) {
	Card::Suit suit;
	if (suit_str == "spade")
		suit = Card::Spade;
	else if (suit_str == "club")
		suit = Card::Club;
	else if (suit_str == "heart")
		suit = Card::Heart;
	else if (suit_str == "diamond")
		suit = Card::Diamond;
	else
		suit = Card::NoSuit;

	int number = 0;
	if (number_value.isString()) {
		QString number_str = number_value.toString();
		if (number_str == "A")
			number = 1;
		else if (number_str == "J")
			number = 11;
		else if (number_str == "Q")
			number = 12;
		else if (number_str == "K")
			number = 13;
	}
	else if (number_value.isNumber()) {
		number = number_value.toNumber();
	}

	CardClass *card_class = getCardClass(name);
	if (card_class) {
		int id = cards.length();
		Card *card = new Card(card_class, suit, number, id);
		cards << card;
		return card;
	}
	else
		return NULL;
}

Q_INVOKABLE QObject * Engine::addCardClass(const QString &class_name, const QString &type_str)
{
	int id = card_classes->children().count();
	CardClass::Type type;
	if (type_str == "basic")
		type = CardClass::Basic;
	else if (type_str == "equip")
		type = CardClass::Equip;
	else if (type_str == "trick")
		type = CardClass::Trick;
	else
		type = CardClass::UserDefined;

	CardClass *card_class = new CardClass(class_name, type, id, card_classes);
	return card_class;
}

Q_INVOKABLE void Engine::addTranslationTable(const QScriptValue &table)
{
	if (!table.isObject())
		return;

	QScriptValueIterator itor(table);
	while (itor.hasNext()) {
		itor.next();
		translation->setProperty(itor.name().toUtf8(), itor.value().toString());
	}
}

QString Engine::translate(const QString &to_translate) {
	return translation->property(to_translate.toUtf8()).toString();
}

Q_INVOKABLE QScriptValue Engine::doScript(const QString &filename)
{
	QString error_msg;
	QScriptValue result;
	QFile file(filename);
	if (file.open(QIODevice::ReadOnly)) {
		result = evaluate(file.readAll(), filename);
		if (hasUncaughtException()) {
			error_msg = tr("%1\n\n Stack trace:\n %2")
				.arg(uncaughtException().toString())
				.arg(uncaughtExceptionBacktrace().join("\n"));
		}
	}
	else
		error_msg = tr("Script file %1 can not be opened for execution!").arg(filename);

	if (!error_msg.isEmpty()) {
		QMessageBox::warning(NULL, tr("Script exception!"), error_msg);
		exit(1);
	}

	return result;
}

General * Engine::getGeneral(const QString &name)
{
	return generals->findChild<General*>(name);
}

CardClass *Engine::getCardClass(const QString &name) {
	return card_classes->findChild<CardClass*>(name);
}

void Engine::alert(const QString &message) {
	QMessageBox::information(NULL, tr("Script alert"), message);
}

void Engine::quit(const QString &reason) {
	if (!reason.isEmpty())
		QMessageBox::warning(NULL, tr("Script quit"), reason);
	exit(0);
}

Card *Engine::getCard(int index) {
	if (index < 0 || index >= cards.length())
		return NULL;
	else
		return cards[index];
}