#include "MajhongAlgorithmWraper.h"
#include "MajhongAlgorithm.h"
#include "PaperCard.h"

MajhongAlgorithmWraper* MajhongAlgorithmWraper::me = nullptr;

MajhongAlgorithmWraper::MajhongAlgorithmWraper():
    algorithm(new MajhongAlgorithm())
{
}

MajhongAlgorithmWraper *MajhongAlgorithmWraper::instance()
{
    if (!me) {
        me = new MajhongAlgorithmWraper();
    }
    return me;
}

bool MajhongAlgorithmWraper::isChow(const QList<PaperCard *> &cards) {
    return algorithm->isChow(cards2Numbers(cards));
}

bool MajhongAlgorithmWraper::isPair(const QList<PaperCard *> &cards) {
    return algorithm->isPair(cards2Numbers(cards));
}

bool MajhongAlgorithmWraper::isMelds(const QList<PaperCard *> &cards) {
    return algorithm->isMelds(cards2Numbers(cards));
}

bool MajhongAlgorithmWraper::isHappyGroup(const QList<PaperCard *> &cards) {
    return algorithm->isHappyGroup(cards2Numbers(cards));
}

bool MajhongAlgorithmWraper::isWinningHand(const QList<PaperCard *> &cards) {
    return algorithm->isWinningHand(cards2Numbers(cards));
}

int MajhongAlgorithmWraper::calcCurrentScore(const QList<PaperCard *> &cards)
{
    return 1;
}

QList<QList<PaperCard *> > MajhongAlgorithmWraper::scanHappyGroups(QList<PaperCard *> cards)
{
    vector<vector<unsigned>> groups = algorithm->scanHappyGroups(cards2Numbers(cards));
    QList<QList<PaperCard *> > results;
    for (const vector<unsigned>& group: groups) {
        QList<PaperCard *> result;
        for (unsigned num: group) {
            result.push_back(cards.at(num));
        }
        results.push_back(result);
    }
    return results;
}

PaperCard *MajhongAlgorithmWraper::scanDiscard(QList<PaperCard *> cards)
{
    return cards.first();
}

vector<unsigned> MajhongAlgorithmWraper::cards2Numbers(const QList<PaperCard *> &cards)
{
    vector<unsigned> nums;
    for (PaperCard* card : cards) {
        nums.push_back(card->getCardNumber());
    }
    return nums;
}
