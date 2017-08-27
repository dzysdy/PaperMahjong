#include "AIController.h"
#include "MajhongAlgorithmWraper.h"
#include "PaperCard.h"
#include <QDebug>

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
    printf("%s",__func__);
    for (PlayerOperation o: operations) {
        printf(",%d", (int)o);
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
    else if (operations.contains(PO_MO)) {
        player->drawsCard();
        //QList<QList<PaperCard *> > results = scanStraight(player->cards(), otherPlayersCard);
        //otherPlayersCard
    }
    else if  (operations.contains(PO_DA)) {
        player->discard();
    }
}

void AIController::selectCardsOnly(const QList<PaperCard *> cards)
{
    for (PaperCard* card: player->cards()) {
        card->setSelected(cards.contains(card));
    }
}
