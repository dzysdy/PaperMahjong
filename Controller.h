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
class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);

    QWidget* widget();
    CardsWidget *getCardsWidget() const;

signals:

public slots:
    void onOperatBtnClicked();
    void onUpdateTime(unsigned sec);
    void onMakeHappyGroup();
    void onFirstStep(QList<PlayerOperation> operations);
    void onSecondStep(QList<PlayerOperation> operations);

protected:
    void initailButtons();
    void connectSignals();
    void showButtons(QList<PlayerOperation> operations);
    void hideAllButtons();
    void updateDrawedArea(CardContainer *container);

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

    QMap<QString, QPushButton*> buttons;
    CardContainer* drawedCardContainer;
};

#endif // CONTROLLER_H
