#ifndef AICONTROLLER_H
#define AICONTROLLER_H
#include "Controller.h"

class AIController : public Controller
{
public:
    AIController(Player* p, QObject *parent = 0);
    virtual void setMyTurn(bool b);

protected:
    virtual void handleOperations(QList<PlayerOperation> operations);

private:
    void selectCardsOnly(const QList<PaperCard *> cards);
    int calcOperationScore(PlayerOperation operation);
    void doOperation(PlayerOperation operation);

    MajhongAlgorithmWraper* algorithm;
};

#endif // AICONTROLLER_H
