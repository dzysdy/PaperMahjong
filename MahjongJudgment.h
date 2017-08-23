#ifndef MAHJONGJUDGMENT_H
#define MAHJONGJUDGMENT_H

#include <QObject>
#include <QTimer>

class Player;
class PaperMahjong;
enum PlayerOperation;
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
    void updateTime(unsigned sec);
    void firstStep(QList<PlayerOperation> operations);
    void secondStep(QList<PlayerOperation> operations);
    void makeHappyGroup();

public slots:
    void onTimer();
    void onFirstStepCompleted(PlayerOperation operation);
    void onSecondStepCompleted(PlayerOperation operation);
    void onMakedHappyGroup();

private:
    void playersDrawsCards();
    void connectSignals(Player* player);
    void changeTurn();
    Player *currentPlayer();
    void doHappyGroupStep();
    void doFirstStep();
    void doSecondStep(PlayerOperation operation);
    void enforce();
    void calcOperatrion(PlayerOperation lastOperation, QList<PlayerOperation> &operations);

    PaperMahjong* paperMahjong;
    QList<Player*> players;
    unsigned whosTurn;
    QTimer timer;
    int timeReminded;
    bool isTimeRecording;
    OperatStep currentStep;
};

#endif // MAHJONGJUDGMENT_H
