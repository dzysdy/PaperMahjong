#ifndef MAHJONGJUDGMENT_H
#define MAHJONGJUDGMENT_H

#include <QObject>
#include <QTimer>
#include "Player.h"

class Player;
class PaperMahjong;
class MahjongJudgment : public QObject
{
    Q_OBJECT
public:
    enum OperatStep {
        OS_HAPPYGROUP,
        OS_FIRSTSTEP,
        OS_SECONDSTEP
    };

    explicit MahjongJudgment(PaperMahjong* mahjong, QObject *parent = 0);

    void addPlayer(Player* player);
    void start();

    bool canEat();
    bool canDoubleEat();
    bool canSingleEat();
    bool canComplete();

signals:
    void makeHappyGroup();

    void updateTime(unsigned sec);
    void firstStep(QList<PlayerOperation> operations);
    void secondStep(QList<PlayerOperation> operations);

public slots:
    void onTimer();
    void onFirstStepCompleted(PlayerOperation operation);
    void onSecondStepCompleted(PlayerOperation operation);
    void onMakedHappyGroup();

    void onUpdateTime(unsigned sec);
    void onFirstStep(QList<PlayerOperation> operations);
    void onSecondStep(QList<PlayerOperation> operations);

private:
    void playersDrawsCards();
    void connectSignals(Player* player);
    void changeTurn();
    Player *currentPlayer();
    void doHappyGroupStep();
    void doFirstStep(PlayerOperation operation);
    void doSecondStep(PlayerOperation operation);
    void enforce();
    void enforceDiscard(Player* player);
    void calcOperatrion(PlayerOperation lastOperation, QList<PlayerOperation> &operations);

    PaperMahjong* paperMahjong;
    QList<Player*> players;
    unsigned whosTurn;
    QTimer timer;
    int timeReminded;
    bool isTimeRecording;
    OperatStep currentStep;
    OperatStep lastStep;
    unsigned playerCompletedNums;
};

#endif // MAHJONGJUDGMENT_H
