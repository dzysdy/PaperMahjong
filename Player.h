#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

class PaperCard;
class PaperMahjong;
class MajhongAlgorithmWraper;
class Controller;
class MahjongJudgment;
class CardModel;

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
    ~Player();

    QList<PaperCard*> cards() {return paperCards;}

    void initCards(const QList<PaperCard*>& cards);
    PaperCard* drawsCard();
    bool discard();

    bool eat(PaperCard* drawedCard);
    bool doubleEat(PaperCard* drawedCard);
    bool singleEat(PaperCard* drawedCard);
    bool makeHappyGroup();
    bool attachHappyGroup();
    bool complete(PaperCard* drawedCard);

    void makeHappyGroupOk();
    void doFirstStep(int operation);
    void doSecondStep(int operation);

    QWidget* desk();
    Controller *getController() const;

    int getStep() const;

signals:
    void firstStepCompleted(PlayerOperation operation);
    void secondStepCompleted(PlayerOperation operation);
    void makedHappyGroup();

public slots:    
    void onMakeHappyGroup();

private:
    void notifyStepCompleted();
    QList<PaperCard*> getSelectedCards();

    //update model
    void addCardToModel(PaperCard* card);
    void removeCardsFromModel(const QList<PaperCard *> &cards);

    PaperMahjong* paperMahjong;
    Controller* controller;
    CardModel* cardModel;
    QList<PaperCard*>& paperCards;
    MajhongAlgorithmWraper* algorithm;
    PlayerOperation lastOperation;
    int step;
};

#endif // PLAYER_H
