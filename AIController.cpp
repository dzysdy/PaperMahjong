#include "AIController.h"
#include "MahjongAlgorithmWraper.h"
#include "PaperCard.h"
#include "CardView.h"
#include <assert.h>
#include <thread>
#include <QDebug>

const QString gButtons[] = {
    "none",
    QObject::tr("chi"),
    QObject::tr("peng"),
    QObject::tr("ding"),
    QObject::tr("hu"),
    QObject::tr("da"),
    QObject::tr("mo"),
    QObject::tr("liaoxi"),
    QObject::tr("guoxi"),
    QObject::tr("ok")
};

AIController::AIController(Player *p, QObject *parent):
    Controller(p, parent),
    algorithm(MahjongAlgorithmWraper::instance())
{
    //cardView->hide();
}

void AIController::handleOperations()
{
//    printf("%s: %d step: ",__func__,player->getStep());
//    for (PlayerOperation o: operations) {
//        printf(",%s", tr(gButtons[(int)o].toStdString().c_str()).toStdString().c_str());
//    }
//    printf("\n\n");
//    fflush(stdout);


    handleOperationThread(playerOperations);
//    std::thread t1(&AIController::handleOperationThread, this, operations);
//    t1.join();
}

void AIController::selectCardsOnly(const QList<PaperCard *> &cards)
{
    for (PaperCard* card: player->cards()) {
        card->setSelected(cards.contains(card));
    }
}

float AIController::calcOperationScore(PlayerOperation operation, QList<PaperCard *>& data)
{
    float score = 0;
    switch (operation) {
    case PO_CHOWS:
    {
        QList<QList<PaperCard *> > results = algorithm->scanChow(player->cards(), otherPlayersCard);
        int higestScore = 0;
        for (QList<PaperCard *> result: results) {
            int s = calcScoreWhenRemoveCards(player->cards(), result);
            if (s > higestScore) {
                higestScore = s;
                data = result;
            }
        }
        score = higestScore;
        break;
    }
    case PO_PONGS:
    {
        QList<PaperCard *> result = algorithm->scanMelds(player->cards(), otherPlayersCard);
        if (!result.empty()) {
            int s = calcScoreWhenRemoveCards(player->cards(), result);
            score = s;
            data = result;
        }
        break;
    }
    case PO_PAIR:

        break;
    case PO_WIN:
        score = 100;
        break;
    case PO_DISCARD:
        score = 99;
        break;
    case PO_DRAW:
        score = meldsCount + 0.2;
        break;
    case PO_MAKEGROUP:

        break;
    case PO_ATTACHGROUP:

        break;
    case PO_MAKEGROUPOK:

        break;
    default:
        break;
    }
    return score;
}

bool AIController::doOperation(PlayerOperation operation)
{
    switch (operation) {
    case PO_CHOWS:
    {
        assert(operatData.size() == 2);
        selectCardsOnly(operatData);
        player->chows(otherPlayersCard);
        break;
    }
    case PO_PONGS:
        assert(operatData.size() == 2);
        selectCardsOnly(operatData);
        player->pongs(otherPlayersCard);
        break;
    case PO_PAIR:

        break;
    case PO_WIN:

        break;
    case PO_DISCARD:
    {
        PaperCard* card = algorithm->scanDiscard(player->cards());
        QList<PaperCard *> result{card};
        selectCardsOnly(result);
        player->discard();
    }
        break;
    case PO_DRAW:
        if (!player->drawsCard()) {
            return false;
        }
        break;
    case PO_MAKEGROUP:

        break;
    case PO_ATTACHGROUP:

        break;
    case PO_MAKEGROUPOK:

        break;
    default:
        break;
    }
    return true;
}

int AIController::calcScoreWhenRemoveCards(QList<PaperCard *> cards, const QList<PaperCard *> &cardsToRemove)
{
    for (PaperCard* card : cardsToRemove) {
        if (cards.contains(card)) {
            cards.removeOne(card);
        }
    }
    return algorithm->calcCurrentScore(cards);
}

void AIController::handleOperationThread(QList<PlayerOperation> operations)
{
    bool needNotify = true;
    if (operations.contains(PO_MAKEGROUP)){
        QList<QList<PaperCard *> > results = algorithm->scanHappyGroups(player->cards());
        for (const QList<PaperCard *>& result: results) {
            selectCardsOnly(result);
            player->makeHappyGroup();
        }
        player->makeHappyGroupOk();
        needNotify = false;
    }
    else {
        if (player->testWinning(otherPlayersCard)) {
            return;
        }
        operations.removeOne(PO_WIN);
        meldsCount = algorithm->calcCurrentScore(player->cards());
        qDebug()<<__func__<<"meldsCount:"<<meldsCount;

        float highScore = meldsCount;
        PlayerOperation highScoreOperation = player->getStep() == 1? PO_DRAW: PO_DISCARD;
        for (PlayerOperation operation: operations) {
            QList<PaperCard *> data;
            float score = calcOperationScore(operation, data);
            if (score > highScore) {
                highScore = score;
                highScoreOperation = operation;
                operatData = data;
            }
        }
        needNotify = doOperation(highScoreOperation);
    }
    if (needNotify) {
        player->notifyStepCompleted();
    }
}
