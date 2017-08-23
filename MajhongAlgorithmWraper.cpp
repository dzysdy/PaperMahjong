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

bool MajhongAlgorithmWraper::is3Straight(const QList<PaperCard *> &cards) {
    return algorithm->is3Straight(cards2Numbers(cards));
}

bool MajhongAlgorithmWraper::is2Pairs(const QList<PaperCard *> &cards) {
    return algorithm->is2Pairs(cards2Numbers(cards));
}

bool MajhongAlgorithmWraper::is3Pairs(const QList<PaperCard *> &cards) {
    return algorithm->is3Pairs(cards2Numbers(cards));
}

bool MajhongAlgorithmWraper::isHappyGroup(const QList<PaperCard *> &cards) {
    return algorithm->isHappyGroup(cards2Numbers(cards));
}

bool MajhongAlgorithmWraper::isCompleteAHand(const QList<PaperCard *> &cards) {
    return algorithm->isCompleteAHand(cards2Numbers(cards));
}

vector<unsigned> MajhongAlgorithmWraper::cards2Numbers(const QList<PaperCard *> &cards)
{
    vector<unsigned> nums;
    for (PaperCard* card : cards) {
        nums.push_back(card->getCardNumber());
    }
    return nums;
}
