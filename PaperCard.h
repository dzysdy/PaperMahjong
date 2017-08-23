#ifndef PAPERCARD_H
#define PAPERCARD_H

#include <QObject>
/*
 *  1-9 * 4
 *  21-19 * 4
 *  41-29 * 4
 *  61*4 71*4 81*4
 */
class PaperCard : public QObject, public QObjectUserData
{
    Q_OBJECT
public:
    enum CardType {
        CT_BING = 1,
        CT_TIAO = 21,
        CT_WAN = 41,
        CT_WHITE = 61,
        CT_RED = 71,
        CT_SHARKS = 81
    };

    explicit PaperCard(unsigned number, QObject *parent = 0);

    bool operator < (const PaperCard& that) {
        return this->cardNumber < that.cardNumber;
    }
    QString getName() const;
    unsigned getCardNumber() const;

signals:

public slots:

private:
    void setNameByNumber(unsigned number);

    unsigned cardNumber;
    QString name;
};

#endif // PAPERCARD_H
