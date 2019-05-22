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

void AIController::setMyTurn(bool c)
{
    Controller::setMyTurn(c);
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

<<<<<<< HEAD
    if (operations.contains(PO_DRAW)) {
=======
    if (operations.contains(PO_MO)) {
>>>>>>> 8cf424c87d487df723954aea9eb9ea20cce72a83
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
    return 1;
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
