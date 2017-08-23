#ifndef MAJHONGALGORITHM_H
#define MAJHONGALGORITHM_H

#include <vector>
#include <algorithm>

using std::vector;

class MajhongAlgorithm
{
public:
    MajhongAlgorithm();

    bool is3Straight(vector<unsigned> nums) {
        if (nums.size() != 3)
            return false;
        std::sort(nums.begin(), nums.end());
        return nums[0] + 1 == nums[1] && nums[1] + 1 == nums[2];
    }
    bool is2Pairs(const vector<unsigned>& nums) {
        if (nums.size() != 2)
            return false;
        return nums[0] == nums[1];
    }
    bool is3Pairs(const vector<unsigned>& nums) {
        if (nums.size() != 3)
            return false;
        return nums[0] == nums[1] && nums[0] == nums[2];
    }
    bool isHappyGroup(vector<unsigned> nums) {
        if (nums.size() != 3)
            return false;
        std::sort(nums.begin(), nums.end());
        return true;
    }
    bool isCompleteAHand(vector<unsigned> nums) {
        unsigned size = nums.size();
        if (size%3 == 0 || size%3 == 2) {
//            std::sort(nums.begin(), nums.end());
//            for (unsigned i = 0; i < nums.size(); ) {
//                unsigned a = nums[i];
//                unsigned b= nums[i + 1];
//                unsigned c= nums[i + 2];
//                if (is3Straight(a, b, c) )
//            }
            return true;
        }
        else {
            return false;
        }
    }
};

#endif // MAJHONGALGORITHM_H
