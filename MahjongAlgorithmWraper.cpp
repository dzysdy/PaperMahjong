#include "MahjongAlgorithmWraper.h"
#include "MahjongAlgorithm.h"
#include "PaperCard.h"

MahjongAlgorithmWraper* MahjongAlgorithmWraper::me = nullptr;

MahjongAlgorithmWraper::MahjongAlgorithmWraper():
    algorithm(new MahjongAlgorithm())
{
}

MahjongAlgorithmWraper *MahjongAlgorithmWraper::instance()
{
    if (!me) {
        me = new MahjongAlgorithmWraper();
    }
    return me;
}

bool MahjongAlgorithmWraper::isChow(const QList<PaperCard *> &cards) {
    return algorithm->isChow(cards2Numbers(cards));
}

bool MahjongAlgorithmWraper::isPair(const QList<PaperCard *> &cards) {
    return algorithm->isPair(cards2Numbers(cards));
}

bool MahjongAlgorithmWraper::isMelds(const QList<PaperCard *> &cards) {
    return algorithm->isMelds(cards2Numbers(cards));
}

bool MahjongAlgorithmWraper::isHappyGroup(const QList<PaperCard *> &cards) {
    return algorithm->isHappyGroup(cards2Numbers(cards));
}

bool MahjongAlgorithmWraper::isWinningHand(const QList<PaperCard *> &cards) {
    return algorithm->isWinningHand(cards2Numbers(cards));
}

int MahjongAlgorithmWraper::calcCurrentScore(const QList<PaperCard *> &cards)
{
    return algorithm->calcMeldsAndChowsCount(cards2Numbers(cards));
}

QList<QList<PaperCard *> > MahjongAlgorithmWraper::scanHappyGroups(const QList<PaperCard *> &cards)
{
    vector<vector<unsigned>> groups = algorithm->scanHappyGroups(cards2Numbers(cards));
    return indexs2Cards(cards, groups);
}

QList<QList<PaperCard *> > MahjongAlgorithmWraper::scanChow(const QList<PaperCard *> &cards, PaperCard *card)
{
    vector<vector<unsigned>> allChows = algorithm->scanChow(cards2Numbers(cards), card->getCardNumber());
    return indexs2Cards(cards, allChows);
}

QList<PaperCard *> MahjongAlgorithmWraper::scanMelds(const QList<PaperCard *> &cards, PaperCard *card)
{
    int firstIndex = algorithm->scanMelds(cards2Numbers(cards), card->getCardNumber());
    QList<PaperCard *> result;
    if (firstIndex < cards.size()-1 && firstIndex >= 0) {
        result.push_back(cards.at(firstIndex));
        result.push_back(cards.at(firstIndex+1));
    }
    return result;
}

PaperCard *MahjongAlgorithmWraper::scanDiscard(QList<PaperCard *> cards)
{
    std::sort(cards.begin(), cards.end(), [](PaperCard* pc1, PaperCard* pc2){return *pc1 < *pc2;});
    vector<unsigned> lonelyCardIndexs = algorithm->scanLonelyCard(cards2Numbers(cards));
    if (!lonelyCardIndexs.empty()) {
        return cards[lonelyCardIndexs.back()];
    }
    else {
        return cards.back();
    }
}

vector<unsigned> MahjongAlgorithmWraper::cards2Numbers(const QList<PaperCard *> &cards)
{
    vector<unsigned> nums;
    for (PaperCard* card : cards) {
        nums.push_back(card->getCardNumber());
    }
    return nums;
}

QList<QList<PaperCard *> > MahjongAlgorithmWraper::indexs2Cards(const QList<PaperCard *> &cards, const vector<vector<unsigned> > &indexs)
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
