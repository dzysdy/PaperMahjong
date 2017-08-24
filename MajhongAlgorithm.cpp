#include "MajhongAlgorithm.h"
#include "HappyGroupHelper.h"

MajhongAlgorithm::MajhongAlgorithm()
{
    HappyGroupHelper::initial();
}

bool MajhongAlgorithm::is3Straight(vector<unsigned> nums) {
    if (nums.size() != 3)
        return false;
    std::sort(nums.begin(), nums.end());
    return nums[0] + 1 == nums[1] && nums[1] + 1 == nums[2];
}

bool MajhongAlgorithm::is2Pairs(const vector<unsigned> &nums)
{
    if (nums.size() != 2)
        return false;
    return nums[0] == nums[1];
}

bool MajhongAlgorithm::is3Pairs(const vector<unsigned> &nums) {
    if (nums.size() != 3)
        return false;
    return nums[0] == nums[1] && nums[0] == nums[2];
}

bool MajhongAlgorithm::isHappyGroup(vector<unsigned> nums) {
    return HappyGroupHelper::isAHappGroup(nums);
}

using IntItor = vector<unsigned>::iterator;

bool take2Pairs(IntItor begin, vector<unsigned>& nums) {
    while (begin != nums.end()) {
        if (is2Pairs(vector<unsigned>(begin, begin+1))) {
            nums.erase(begin, begin + 1);
            begin += 2;
            return true;
        }
        begin++;
    }
    return false;
}

bool take3Pairs(vector<unsigned>& nums) {
    if (nums.empty()) return true;
    if (nums[0] == nums[1] && nums[0] == nums[2]) {
        nums.erase(nums.begin(), nums.begin() + 2);
        return true;
    }
    return false;
}

bool take3Straight(vector<unsigned>& nums) {
    if (nums.empty()) return true;
    if (nums[0] + 1 == nums[1] && nums[1] + 1 == nums[2]) {
        nums.erase(nums.begin(), nums.begin() + 2);
        return true;
    }
    return false;
}

bool isCompleted(vector<unsigned>& nums) {
    if (take3Pairs(nums) || take3Straight(nums)) {
        if (nums.empty()) return true;
        isCompleted(nums);
    }
    return false;
}

bool MajhongAlgorithm::isCompleteAHand(vector<unsigned> nums) {
    unsigned size = nums.size();
    if (size%3 == 0 || size%3 == 2) {
        std::sort(nums.begin(), nums.end());
        vector<unsigned> numsCopy(nums);

        for (int i=0;i<nums.size() -1; i++) {
            if (nums[i] == nums[i + 1]) {
                break;
            }
        }
        nums.erase(nums.begin()+i,nums.begin()+i+1);

        if (nums.empty()) {
            return true;
        }
        else {

        }

        return true;
    }
    else {
        return false;
    }
}
