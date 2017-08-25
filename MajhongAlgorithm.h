#ifndef MAJHONGALGORITHM_H
#define MAJHONGALGORITHM_H

#include <vector>
#include <algorithm>

using std::vector;

class MajhongAlgorithm
{
public:
    MajhongAlgorithm();

    bool is3Straight(vector<unsigned> nums);
    bool is2Pairs(const vector<unsigned>& nums);
    bool is3Pairs(const vector<unsigned>& nums);
    bool isHappyGroup(vector<unsigned> nums);
    bool isCompleteAHand(vector<unsigned> nums);

private:
    bool take2Pairs(vector<unsigned> &nums, unsigned &index);
    bool take3Pairs(vector<unsigned> &nums);
    bool take3Straight(vector<unsigned> &nums);
    bool isAllStraightOrPairs(vector<unsigned> &nums);
    bool isCompleted(vector<unsigned> &nums, unsigned &index);
};

#endif // MAJHONGALGORITHM_H
