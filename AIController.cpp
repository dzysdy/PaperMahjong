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
        printf(",%s", gButtons[(int)o].toStdString().c_str());
    }
    printf("\n\n");
    fflush(stdout);
    if (operations.contains(PO_LIAOXI)){
        QList<QList<PaperCard *> > results = algorithm->scanHappyGroups(player->cards());
        for (const QList<PaperCard *>& result: results) {
            selectCardsOnly(result);
            player->makeHappyGroup();
        }
        player->makeHappyGroupOk();
    }
    else {
        if (player->complete(otherPlayersCard)) {
            //emit to judgment;
            return;
        }
        operations.removeOne(PO_HU);
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

    if (operations.contains(PO_MO)) {
        player->drawsCard();
        //QList<QList<PaperCard *> > results = scanStraight(player->cards(), otherPlayersCard);
        //otherPlayersCard
    }
    else if  (operations.contains(PO_DA)) {
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
    case PO_EAT:

        break;
    case PO_PENG:

        break;
    case PO_DING:

        break;
    case PO_HU:

        break;
    case PO_DA:

        break;
    case PO_MO:

        break;
    case PO_LIAOXI:

        break;
    case PO_GUOXI:

        break;
    case PO_OK:

        break;
    default:
        break;
    }
}
