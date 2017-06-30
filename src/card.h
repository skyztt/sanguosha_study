#ifndef CARD_H
#define CARD_H

#include "cardclass.h"

class Card : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString suit READ getSuitString CONSTANT)
    Q_PROPERTY(bool red READ isRed STORED false CONSTANT)
    Q_PROPERTY(bool black READ isBlack STORED false CONSTANT)
    Q_PROPERTY(int number READ getNumber CONSTANT)
    Q_PROPERTY(QString number_string READ getNumberString CONSTANT)
    Q_PROPERTY(QString type READ getTypeString CONSTANT)

public:
    // enumeration type
    enum Suit {Spade, Club, Heart, Diamond, NoSuit};

    // constructor
    Card(CardClass *card_class, enum Suit suit, int number, int id);

    // property getters, as all properties of card is read only, no setter is defined
    QString getSuitString() const;
    bool isRed() const;
    bool isBlack() const;
    int getNumber() const;
    QString getNumberString() const;
    QString getTypeString() const;
    enum Suit getSuit() const;


    // static functions
    static bool CompareBySuitNumber(const Card *a, const Card *b);
    static bool CompareByType(const Card *a, const Card *b);

private:
    CardClass *card_class;
    enum Suit suit;
    int number;
    int id;
};

#endif // CARD_H
