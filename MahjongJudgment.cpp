#include "MahjongJudgment.h"
#include "PaperMahjong.h"
#include "PaperCard.h"
#include "Controller.h"
#include <future>
#include <QMessageBox>

#define BEFORE_DRAWSCARD_TIME 30
#define AFTER_DRAWSCARD_TIME 60

MahjongJudgment::MahjongJudgment(PaperMahjong *mahjong, QObject *parent) :
    QObject(parent),
    paperMahjong(mahjong)
{
    connect(paperMahjong, &PaperMahjong::draws, this, &MahjongJudgment::onDraws);
    connect(this, &MahjongJudgment::updateTime, this, &MahjongJudgment::onUpdateTime);
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

void MahjongJudgment::onFirstStepCompleted(int operation)
{
    lastStep = OS_FIRSTSTEP;
    isTimeRecording = false;
    doSecondStep((PlayerOperation)operation);
}

void MahjongJudgment::onSecondStepCompleted(PlayerOperation operation)
{
    lastStep = OS_SECONDSTEP;
    switch (operation) {
    case PO_DISCARD:
        changeTurn();
        doFirstStep(operation);
        break;
    case PO_MAKEGROUP:
        doFirstStep(operation);
        break;
    case PO_WIN:
        printf("game over");fflush(stdout);
        break;
    default:
        printf("error operation in second step");fflush(stdout);
        break;
    }
}

void MahjongJudgment::onMakeHappyGroupCompleted()
{
    lastStep = OS_HAPPYGROUP;
    isTimeRecording = false;
    if (++playerCompletedNums == (unsigned)players.size())
        doSecondStep(PO_NONE);
}

void MahjongJudgment::onWinningHand(Player *player)
{
    //QMessageBox::information(NULL, tr("Congradulations!"), "Player---" +player->getName() +" Win!", QMessageBox::Ok, QMessageBox::Ok);
    int sumMoney = 0;
    int deltaMoney = pow(2, player->getGroupCount());
    for (Player* p: players) {
        if (p != player) {
            p->getController()->onBalance(-deltaMoney);
            sumMoney += deltaMoney;
        }
    }
    player->getController()->onBalance(sumMoney);
    paperMahjong->destoryDealedCards();
    start();
}

void MahjongJudgment::onUpdateTime(unsigned sec)
{
    currentPlayer()->getController()->onUpdateTime(sec);
}

void MahjongJudgment::handleOperations(QList<PlayerOperation> operations)
{
    currentPlayer()->getController()->handleOperations(operations);
}

void MahjongJudgment::onDraws()
{
    for (Player* player: players) {
        player->getController()->onBalance(0);
    }
    paperMahjong->destoryDealedCards();
    start();
}

void MahjongJudgment::playersDrawsCards()
{
    bool first = true;
    for (Player* player : players) {
        QList<PaperCard*> cards;
        paperMahjong->dealingCards(first? 17: 16, cards);
        first = false;
        player->initCards(cards);
    }
}

void MahjongJudgment::connectSignals(Player *player)
{
    connect(player, &Player::firstStepCompleted, this, &MahjongJudgment::onFirstStepCompleted);
    connect(player, &Player::secondStepCompleted, this, &MahjongJudgment::onSecondStepCompleted );
    connect(player, &Player::makeHappyGroupCompleted, this, &MahjongJudgment::onMakeHappyGroupCompleted);
    connect(player, &Player::winningHand, this, &MahjongJudgment::onWinningHand);
    connect(this, &MahjongJudgment::makeHappyGroup, player->getController(), &Controller::onMakeHappyGroup);
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
    playerCompletedNums = 0;
    currentStep = OS_HAPPYGROUP;
    emit makeHappyGroup();
    timeReminded = AFTER_DRAWSCARD_TIME;
    isTimeRecording = true;
}

void MahjongJudgment::doFirstStep(PlayerOperation operation)
{
    currentStep = OS_FIRSTSTEP;
    currentPlayer()->doFirstStep(0);
    QList<PlayerOperation> operations;
    calcOperatrion(operation, operations);
    //std::async(std::launch::async, [this, operations]{ onHandleOperations(operations); });
    handleOperations(operations);
    timeReminded = BEFORE_DRAWSCARD_TIME;
    isTimeRecording = true;
}

void MahjongJudgment::doSecondStep(PlayerOperation operation)
{
    currentStep = OS_SECONDSTEP;
    currentPlayer()->doSecondStep(0);
    QList<PlayerOperation> operations;
    calcOperatrion(operation, operations);
    handleOperations(operations);
    timeReminded = AFTER_DRAWSCARD_TIME;
    isTimeRecording = true;
}

void MahjongJudgment::enforce()
{
    Player* player = currentPlayer();
    switch (currentStep) {
    case OS_HAPPYGROUP:
        for (Player* p: players) {
            if (p->cards().size()%3 == 2) {
                enforceDiscard(p);
            }
            p->makeHappyGroupOk();
        }
        break;
    case OS_FIRSTSTEP:
        player->drawsCard();
        player->notifyStepCompleted();
        break;
    case OS_SECONDSTEP:
        enforceDiscard(player);
        player->notifyStepCompleted();
        break;
    default:
        break;
    }
}

void MahjongJudgment::enforceDiscard(Player *player)
{
    for (PaperCard* c: player->cards()){
        c->setSelected(false);
    }
    player->cards().first()->setSelected(true);
    player->discard();
}

void MahjongJudgment::calcOperatrion(PlayerOperation lastOperation, QList<PlayerOperation>& operations)
{
    switch (lastStep) {
    case OS_HAPPYGROUP:
        operations.push_back(PO_DISCARD);
        break;
    case OS_FIRSTSTEP:
        if (lastOperation == PO_DRAW){
            operations.push_back(PO_ATTACHGROUP);
            operations.push_back(PO_WIN);
        }
        operations.push_back(PO_DISCARD);
        break;
    case OS_SECONDSTEP:
        if (lastOperation == PO_DISCARD) {
            operations.push_back(PO_CHOWS);
            operations.push_back(PO_PONGS);
            operations.push_back(PO_PAIR);
            operations.push_back(PO_WIN);
        }
        operations.push_back(PO_DRAW);
        break;
    default:
        break;
    }
}
