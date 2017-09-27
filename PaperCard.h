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
        CT_DOTS = 1,
        CT_BAMBOO = 21,
        CT_CHARACTERS = 41,
        CT_WHITEFLOWER = 61,
        CT_REDFLOWER = 71,
        CT_SHARKS = 81
    };

    explicit PaperCard(unsigned number, QObject *parent = 0);
    ~PaperCard() = default;
    bool operator < (const PaperCard& that) {
        return this->cardNumber < that.cardNumber;
    }
    QString getName() const;
    unsigned getCardNumber() const;

    bool isSelected() const;
    void setSelected(bool value);

signals:

public slots:

private:
    void setNameByNumber(unsigned number);

    unsigned cardNumber;
    QString name;
    bool selected;
};

#endif // PAPERCARD_H
