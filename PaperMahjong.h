#ifndef PAPERMAHJONG_H
#define PAPERMAHJONG_H

#include <QObject>

class PaperCard;
class PaperMahjong : public QObject
{
    Q_OBJECT
public:
    explicit PaperMahjong(QObject *parent = 0);

    void shuffleCards();
    void dealingCards(unsigned num, QList<PaperCard*>& paperCards);
    PaperCard* getCard();
    void destoryDealedCards();

signals:
    void draws();
public slots:

private:
    void initCustomCard(unsigned begin);
    void initFourCards(unsigned cardNumber);

    QList<unsigned> cardNumbers;
    QList<PaperCard*> dealedCards;
    bool shuffled;
};

#endif // PAPERMAHJONG_H
