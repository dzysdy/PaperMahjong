#include "MahjongJudgment.h"
#include "Player.h"
#include "PaperMahjong.h"

#define BEFORE_DRAWSCARD_TIME 30
#define AFTER_DRAWSCARD_TIME 60

MahjongJudgment::MahjongJudgment(PaperMahjong *mahjong, QObject *parent) :
    QObject(parent),
    paperMahjong(mahjong)
{
}

void MahjongJudgment::addPlayer(Player *player) {
    connectSignals(player);
    players.push_back(player);
}

void MahjongJudgment::start() {
    if (players.size() < 2)
        return;
    paperMahjong->shuffleCards();
    playersDrawsCards();
    whosTurn = 0;
    isTimeRecording = false;
    connect(&timer, &QTimer::timeout, this, &MahjongJudgment::onTimer);
    timer.start(1000);
    doHappyGroupStep();
}

void MahjongJudgment::onTimer()
{
    if (!isTimeRecording)
        return;
    if (--timeReminded > 0)
        emit updateTime(timeReminded);
    else {
        isTimeRecording = false;
        enforce();
    }
}

void MahjongJudgment::onFirstStepCompleted(PlayerOperation operation)
{
    isTimeRecording = false;
    doSecondStep(operation);
}

void MahjongJudgment::onSecondStepCompleted(PlayerOperation operation)
{
    switch (operation) {
    case PO_DA:
        break;
        default:
        break;
    }
    changeTurn();
    doFirstStep();
}

void MahjongJudgment::onMakedHappyGroup()
{
    isTimeRecording = false;
    doFirstStep();
}

void MahjongJudgment::playersDrawsCards()
{
    for (Player* player : players) {
        QList<PaperCard*> cards;
        paperMahjong->dealingCards(16, cards);
        player->initCards(cards);
    }
    players.first()->drawsCard();
}

void MahjongJudgment::connectSignals(Player *player)
{
    connect(this, &MahjongJudgment::makeHappyGroup, player, &Player::onMakeHappyGroup);
//    connect(this, &MahjongJudgment::firstStep, player, &Player::onFirstStep);
//    connect(this, &MahjongJudgment::secondStep, player, &Player::onSecondStep);
    connect(player, &Player::firstStepCompleted, this, &MahjongJudgment::onFirstStepCompleted);
    connect(player, &Player::secondStepCompleted, this, &MahjongJudgment::onSecondStepCompleted);
    connect(player, &Player::makedHappyGroup, this, &MahjongJudgment::onMakedHappyGroup);
}

void MahjongJudgment::changeTurn()
{
    whosTurn = (whosTurn + 1)%players.size();
}

Player *MahjongJudgment::currentPlayer()
{
    return players.at(whosTurn);
}

void MahjongJudgment::doHappyGroupStep()
{
    emit makeHappyGroup();
    currentStep = OS_HAPPYGROUP;
    timeReminded = AFTER_DRAWSCARD_TIME;
    isTimeRecording = true;
}

void MahjongJudgment::doFirstStep()
{
    Player* player = currentPlayer();
    player->onFirstStep(0);
    currentStep = OS_FIRSTSTEP;
    timeReminded = BEFORE_DRAWSCARD_TIME;
    isTimeRecording = true;
    QList<PlayerOperation> operations;
    calcOperatrion(PO_NONE, operations);
    emit firstStep(operations);
}

void MahjongJudgment::doSecondStep(PlayerOperation operation)
{
    if (operation == PO_NONE)
        return;
    Player* player = currentPlayer();
    player->onSecondStep(0);
    currentStep = OS_SECONDSTEP;
    timeReminded = AFTER_DRAWSCARD_TIME;
    isTimeRecording = true;
    QList<PlayerOperation> operations;
    calcOperatrion(operation, operations);
    emit secondStep(operations);
}

void MahjongJudgment::enforce()
{
    //Player* player = currentPlayer();

}

void MahjongJudgment::calcOperatrion(PlayerOperation lastOperation, QList<PlayerOperation>& operations)
{

    operations.push_back(PO_DA);
}
