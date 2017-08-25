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
class CardsWidget;
class MahjongJudgment;

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(Player* p, QObject *parent = 0);

    QWidget* widget();
    CardsWidget *getCardsWidget() const;
    void connectSignals(MahjongJudgment* judgment);
    virtual void showBtnWidget(bool){}

signals:
    void updateDrawedArea(PaperCard *card);

public slots:
    void onUpdateTime(unsigned sec);
    void onMakeHappyGroup();
    void onFirstStep(QList<PlayerOperation> operations);
    void onSecondStep(QList<PlayerOperation> operations);
    void onUpdatedDrawedCard(PaperCard* card);

protected:
    virtual void showButtons(QList<PlayerOperation>){}
    virtual void showButtonsOnly(QList<PlayerOperation>){}
    virtual void hideAllButtons(){}

    Player* player;
    QWidget* desk;
    QHBoxLayout* mainLayout;
    QHBoxLayout* leftLayout;
    QVBoxLayout* midLayout;
    QVBoxLayout* rightLayout;

    QHBoxLayout* btnsLayout;
    QHBoxLayout* cardsLayout;
    CardsWidget* cardsWidget;

    QLCDNumber* timeRecoder;
    PaperCard* otherPlayersCard;
};

#endif // CONTROLLER_H
