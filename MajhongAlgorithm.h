#ifndef MAJHONGALGORITHM_H
#define MAJHONGALGORITHM_H

#include <vector>
#include <set>
#include <algorithm>

using std::vector;
using std::set;

class MajhongAlgorithm
{
public:
    MajhongAlgorithm();

    bool is3Straight(vector<unsigned> nums);
    bool is2Pairs(const vector<unsigned>& nums);
    bool is3Pairs(const vector<unsigned>& nums);
    bool isHappyGroup(vector<unsigned> nums);
    bool isCompleteAHand(vector<unsigned> nums);
    vector<vector<unsigned>> scanHappyGroups(const vector<unsigned> &nums);

private:
    bool take2Pairs(vector<unsigned> &nums, unsigned &index);
    bool take3Pairs(vector<unsigned> &nums);
    bool take3Straight(vector<unsigned> &nums);
    bool isAllStraightOrPairs(vector<unsigned> &nums);
    bool isCompleted(vector<unsigned> &nums, unsigned &index);
    void scanHappyGroup(const vector<unsigned>& nums, const set<unsigned> &happyGroup, vector<vector<unsigned> > &groups);
};

#endif // MAJHONGALGORITHM_H
