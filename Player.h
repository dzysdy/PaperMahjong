#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

class PaperCard;
class PaperMahjong;
class MajhongAlgorithmWraper;
class Controller;
enum PlayerOperation {
    PO_NONE,
    PO_EAT,
    PO_PENG,
    PO_DING,
    PO_HU,
    PO_DA,
    PO_MO,
    PO_LIAOXI,
    PO_GUOXI,
    PO_OK
};

class Player : public QObject
{
    Q_OBJECT

    friend class MahjongJudgment;
public:
    explicit Player(PaperMahjong* mahjong, MahjongJudgment* judgment, QObject *parent = 0);

    QList<PaperCard*> cards() {return paperCards;}

    void initCards(const QList<PaperCard*>& cards);
    PaperCard* drawsCard();
    bool removeCard(PaperCard* card);

    bool eat(const QList<PaperCard *> &cards);
    bool doubleEat(const QList<PaperCard*>& cards);
    bool singleEat(const QList<PaperCard*>& cards);
    bool makeHappyGroup(const QList<PaperCard *> &cards);
    void makeHappyGroupOk();

    void doFirstStep(int operation);
    void doSecondStep(int operation);

    QWidget* desk();
    Controller *getController() const;

signals:
    void firstStepCompleted(PlayerOperation operation);
    void secondStepCompleted(PlayerOperation operation);
    void makedHappyGroup();

public slots:    
    void onMakeHappyGroup();

private:
    void addOneCard(PaperCard* card);
    void notifyStepCompleted();

    PaperMahjong* paperMahjong;
    QList<PaperCard*> paperCards;
    MajhongAlgorithmWraper* algorithm;
    Controller* controller;
    PlayerOperation lastOperation;
    int step;
};

#endif // PLAYER_H
