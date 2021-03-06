#ifndef MAJHONGALGORITHM_H
#define MAJHONGALGORITHM_H

#include <vector>
#include <set>
#include "MahjongSocreRecorder.h"

using std::vector;
using std::set;

class MahjongAlgorithm
{
public:
    MahjongAlgorithm();

    bool isChow(vector<unsigned> nums);
    bool isPair(const vector<unsigned>& nums);
    bool isMelds(const vector<unsigned>& nums);
    bool isHappyGroup(vector<unsigned> nums);
    bool isWinningHand(vector<unsigned> nums);
    bool isReadyHand(const vector<unsigned>& nums);
    unsigned calcMeldsAndChowsCount(const vector<unsigned>& nums);
    vector<vector<unsigned>> scanHappyGroups(const vector<unsigned> &nums);
    vector<vector<unsigned>> scanChow(const vector<unsigned>& nums, unsigned targetNumber);
    int scanMelds(const vector<unsigned>& nums, unsigned targetNumber);
    vector<unsigned> scanLonelyCard(const vector<unsigned> &nums);
    MahjongSocreRecorder calcScore(const vector<unsigned> &nums);

private:
    bool takePair(vector<unsigned> &nums, unsigned &index);
    bool takeOneMelds(vector<unsigned> &nums);
    bool takeOneChow(vector<unsigned> &nums);
    bool takeAllMeldsAndChow(vector<unsigned> &nums);
    bool isWinningHand(vector<unsigned> &nums, unsigned &index);
    void scanHappyGroup(const vector<unsigned>& nums, const set<unsigned> &happyGroup, vector<vector<unsigned> > &groups);
    unsigned removeMelds(vector<unsigned>& nums);
    unsigned removeChows(vector<unsigned>& nums);
};

#endif // MAJHONGALGORITHM_H
