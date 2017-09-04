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
#include <QLabel>

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
    void moveToCardGroupArea(QList<PaperCard *> cards);
    void onUpdateTime(unsigned sec);
    void onBalance(int deltaMoney);
    void handleOperations(QList<PlayerOperation>);
    //virtual void setMyTurn(bool b);
    virtual void handleOperations(){}

signals:
    void updateDrawedArea(PaperCard *card);
    void asynHandleOperations();

public slots:
    void onMakeHappyGroup();
    void onUpdatedDrawedCard(PaperCard* card);
    void onHandleOperations();

protected:
    void clearLayout(QLayout *layout);

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
    int money;
    QLabel* moneyLabel;
    QList<PlayerOperation> playerOperations;
};

#endif // CONTROLLER_H
