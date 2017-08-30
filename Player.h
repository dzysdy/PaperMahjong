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
    PO_CHOWS,
    PO_PONGS,
    PO_PAIR,
    PO_WIN,
    PO_DISCARD,
    PO_DRAW,
    PO_MAKEGROUP,
    PO_ATTACHGROUP,
    PO_MAKEGROUPOK
};

class Player : public QObject
{
    Q_OBJECT

    friend class MahjongJudgment;
public:
    explicit Player(PaperMahjong* mahjong, MahjongJudgment* judgment, int controllerType = 0, QObject *parent = 0);
    ~Player();

    QList<PaperCard*> cards() {return paperCards;}

    void initCards(const QList<PaperCard*>& cards);
    PaperCard* drawsCard();
    bool discard();

    bool chows(PaperCard* drawedCard);
    bool pongs(PaperCard* drawedCard);
    bool makePair(PaperCard* drawedCard);
    bool makeHappyGroup();
    bool attachHappyGroup();
    bool testWinning(PaperCard* drawedCard);

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
