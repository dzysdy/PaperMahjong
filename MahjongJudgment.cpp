#include "MahjongJudgment.h"
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
    lastStep = OS_FIRSTSTEP;
    isTimeRecording = false;
    doSecondStep(operation);
}

void MahjongJudgment::onSecondStepCompleted(PlayerOperation operation)
{
    lastStep = OS_SECONDSTEP;
    switch (operation) {
    case PO_DA:
        changeTurn();
        doFirstStep(operation);
        break;
    case PO_LIAOXI:
        doFirstStep(operation);
        break;
    case PO_HU:
        printf("game over");fflush(stdout);
        break;
    default:
        printf("error operation in second step");fflush(stdout);
        break;
    }
}

void MahjongJudgment::onMakedHappyGroup()
{
    lastStep = OS_HAPPYGROUP;
    isTimeRecording = false;
    doSecondStep(PO_NONE);
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
    currentStep = OS_HAPPYGROUP;
    emit makeHappyGroup();
    timeReminded = AFTER_DRAWSCARD_TIME;
    isTimeRecording = true;
}

void MahjongJudgment::doFirstStep(PlayerOperation operation)
{
    currentStep = OS_FIRSTSTEP;
    QList<PlayerOperation> operations;
    calcOperatrion(operation, operations);
    emit firstStep(operations);
    Player* player = currentPlayer();
    player->doFirstStep(0);
    timeReminded = BEFORE_DRAWSCARD_TIME;
    isTimeRecording = true;
}

void MahjongJudgment::doSecondStep(PlayerOperation operation)
{
    currentStep = OS_SECONDSTEP;
    QList<PlayerOperation> operations;
    calcOperatrion(operation, operations);
    emit secondStep(operations);
    Player* player = currentPlayer();
    player->doSecondStep(0);
    timeReminded = AFTER_DRAWSCARD_TIME;
    isTimeRecording = true;
}

void MahjongJudgment::enforce()
{
    Player* player = currentPlayer();
    switch (currentStep) {
    case OS_HAPPYGROUP:
        for (Player* p: players) {
            if (p->cards().size()%3 == 2)
                p->removeCard(p->cards().first());
            p->makeHappyGroupOk();
        }
        break;
    case OS_FIRSTSTEP:
        player->drawsCard();
        break;
    case OS_SECONDSTEP:
        player->removeCard(player->cards().first());
        break;
    default:
        break;
    }
}

void MahjongJudgment::calcOperatrion(PlayerOperation lastOperation, QList<PlayerOperation>& operations)
{
    switch (lastStep) {
    case OS_HAPPYGROUP:
        operations.push_back(PO_DA);
        break;
    case OS_FIRSTSTEP:
        if (lastOperation == PO_MO){
            operations.push_back(PO_GUOXI);
            operations.push_back(PO_HU);
        }
        else {
            operations.push_back(PO_DA);
        }
        break;
    case OS_SECONDSTEP:
        if (lastOperation == PO_DA) {
            operations.push_back(PO_EAT);
            operations.push_back(PO_PENG);
            operations.push_back(PO_DING);
            operations.push_back(PO_HU);
        }
        operations.push_back(PO_MO);
        break;
    default:
        break;
    }
}
