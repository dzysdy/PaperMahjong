#ifndef AICONTROLLER_H
#define AICONTROLLER_H
#include "Controller.h"

class AIController : public Controller
{
    Q_OBJECT

public:
    AIController(Player* p, QObject *parent = 0);
    virtual void handleOperations();

private:
    void selectCardsOnly(const QList<PaperCard *>& cards);
    float calcOperationScore(PlayerOperation operation, QList<PaperCard *> &data);
    bool doOperation(PlayerOperation operation);
    int calcScoreWhenRemoveCards(QList<PaperCard *> cards, const QList<PaperCard*>& cardsToRemove);
    void handleOperationThread(QList<PlayerOperation> operations);

    MahjongAlgorithmWraper* algorithm;
    QList<PaperCard *> operatData;
    float meldsCount;
    int test;
};

#endif // AICONTROLLER_H
