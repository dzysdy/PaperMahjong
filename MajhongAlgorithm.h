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
};

#endif // MAJHONGALGORITHM_H
