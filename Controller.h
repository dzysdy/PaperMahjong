#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QLCDNumber>
#include <QPushButton>
#include <QMap>
#include "Player.h"

class CardContainer;
class CardView;
class MahjongJudgment;

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(Player* p, QObject *parent = 0);
    virtual ~Controller();

    QWidget* widget();
    CardView *getCardsView() const;
    void connectSignals(MahjongJudgment* judgment);
    void moveToCardGroupArea(QList<PaperCard *> cards);
    void onUpdateTime(unsigned sec);

    virtual void setMyTurn(bool b);
    virtual void handleOperations(QList<PlayerOperation>){}

signals:
    void updateDrawedArea(PaperCard *card);

public slots:
    void onMakeHappyGroup();
    void onUpdatedDrawedCard(PaperCard* card);

protected:
    Player* player;
    QWidget* desk;
    QHBoxLayout* mainLayout;
    QHBoxLayout* leftLayout;
    QVBoxLayout* midLayout;
    QVBoxLayout* rightLayout;

    QHBoxLayout* btnsLayout;
    QHBoxLayout* cardsLayout;
    CardView* cardView;

    QLCDNumber* timeRecoder;
    PaperCard* otherPlayersCard;
    bool isMyTurn;
};

#endif // CONTROLLER_H
