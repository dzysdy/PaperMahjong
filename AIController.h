#ifndef AICONTROLLER_H
#define AICONTROLLER_H
#include "Controller.h"

class AIController : public Controller
{
    Q_OBJECT

public:
    AIController(Player* p, QObject *parent = 0);
    virtual void setMyTurn(bool b);
    virtual void handleOperations(QList<PlayerOperation> operations);

private:
    void selectCardsOnly(const QList<PaperCard *>& cards);
    float calcOperationScore(PlayerOperation operation, QList<PaperCard *> &data);
    void doOperation(PlayerOperation operation);
    int calcScoreWhenRemoveCards(QList<PaperCard *> cards, const QList<PaperCard*>& cardsToRemove);
    MahjongAlgorithmWraper* algorithm;
    QList<PaperCard *> operatData;
    float meldsCount;
};

#endif // AICONTROLLER_H
