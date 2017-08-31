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
    return algorithm->calcMeldsAndChowsCount(cards2Numbers(cards));
}

QList<QList<PaperCard *> > MajhongAlgorithmWraper::scanHappyGroups(const QList<PaperCard *> &cards)
{
    vector<vector<unsigned>> groups = algorithm->scanHappyGroups(cards2Numbers(cards));
    return indexs2Cards(cards, groups);
}

QList<QList<PaperCard *> > MajhongAlgorithmWraper::scanChow(const QList<PaperCard *> &cards, PaperCard *card)
{
    vector<vector<unsigned>> allChows = algorithm->scanChow(cards2Numbers(cards), card->getCardNumber());
    return indexs2Cards(cards, allChows);
}

QList<PaperCard *> MajhongAlgorithmWraper::scanMelds(const QList<PaperCard *> &cards, PaperCard *card)
{
    unsigned firstIndex = algorithm->scanMelds(cards2Numbers(cards), card->getCardNumber());
    QList<PaperCard *> result;
    if (firstIndex < cards.size()) {
        result.push_back(cards.at(firstIndex));
        result.push_back(cards.at(firstIndex+1));
    }
    return result;
}

PaperCard *MajhongAlgorithmWraper::scanDiscard(QList<PaperCard *> cards)
{
    vector<unsigned> lonelyCardIndexs = algorithm->scanLonelyCard(cards2Numbers(cards));
    if (!lonelyCardIndexs.empty()) {
        return cards[lonelyCardIndexs.back()];
    }
    else {
        return cards.back();
    }
}

vector<unsigned> MajhongAlgorithmWraper::cards2Numbers(const QList<PaperCard *> &cards)
{
    vector<unsigned> nums;
    for (PaperCard* card : cards) {
        nums.push_back(card->getCardNumber());
    }
    return nums;
}

QList<QList<PaperCard *> > MajhongAlgorithmWraper::indexs2Cards(const QList<PaperCard *> &cards, const vector<vector<unsigned> > &indexs)
{
    QList<QList<PaperCard *> > results;
    for (const vector<unsigned>& index: indexs) {
        QList<PaperCard *> result;
        for (unsigned num: index) {
            result.push_back(cards.at(num));
        }
        results.push_back(result);
    }
    return results;
}
