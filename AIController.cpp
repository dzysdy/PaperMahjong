#include "AIController.h"
#include "MajhongAlgorithmWraper.h"
#include "PaperCard.h"
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
    algorithm(MajhongAlgorithmWraper::instance())
{

}

void AIController::setMyTurn(bool b)
{
    Controller::setMyTurn(b);
}

void AIController::handleOperations(QList<PlayerOperation> operations)
{
    printf("%s: %d step: ",__func__,player->getStep());
    for (PlayerOperation o: operations) {
        printf(",%s", tr(gButtons[(int)o].toStdString().c_str()).toStdString().c_str());
    }
    printf("\n\n");
    fflush(stdout);
    if (operations.contains(PO_MAKEGROUP)){
        QList<QList<PaperCard *> > results = algorithm->scanHappyGroups(player->cards());
        for (const QList<PaperCard *>& result: results) {
            selectCardsOnly(result);
            player->makeHappyGroup();
        }
        player->makeHappyGroupOk();
    }
    else {
        if (player->testWinning(otherPlayersCard)) {
            //emit to judgment;
            return;
        }
        operations.removeOne(PO_WIN);
        int currentScore = algorithm->calcCurrentScore(player->cards());
        PlayerOperation highScoreOperation;
        for (PlayerOperation operation: operations) {
            int score = calcOperationScore(operation);
            if (score > currentScore) {
                highScoreOperation = operation;
            }
        }
        doOperation(highScoreOperation);
    }

    if (operations.contains(PO_DRAW)) {
        player->drawsCard();
        //QList<QList<PaperCard *> > results = scanStraight(player->cards(), otherPlayersCard);
        //otherPlayersCard
    }
    else if  (operations.contains(PO_DISCARD)) {
        PaperCard* card = algorithm->scanDiscard(player->cards());
        QList<PaperCard *> result{card};
        selectCardsOnly(result);
        player->discard();
    }
}

void AIController::selectCardsOnly(const QList<PaperCard *> cards)
{
    for (PaperCard* card: player->cards()) {
        card->setSelected(cards.contains(card));
    }
}

int AIController::calcOperationScore(PlayerOperation operation)
{
    int score = 0;
    switch (operation) {
    case PO_CHOWS:
    {
        QList<QList<PaperCard *> > results = algorithm->scanChow(player->cards(), otherPlayersCard);
        if (!results.empty()) {
            selectCardsOnly(results.first());
            player->chows(otherPlayersCard);
            score = 2;
        }
        break;
    }
    case PO_PONGS:

        break;
    case PO_PAIR:

        break;
    case PO_WIN:

        break;
    case PO_DISCARD:

        break;
    case PO_DRAW:

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

void AIController::doOperation(PlayerOperation operation)
{
    switch (operation) {
    case PO_CHOWS:

        break;
    case PO_PONGS:

        break;
    case PO_PAIR:

        break;
    case PO_WIN:

        break;
    case PO_DISCARD:

        break;
    case PO_DRAW:

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
}
