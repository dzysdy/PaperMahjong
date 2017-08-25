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

bool MajhongAlgorithm::isCompleteAHand(vector<unsigned> nums) {
    unsigned size = nums.size();
    if (size%3 == 0) {
        std::sort(nums.begin(), nums.end());
        return isAllStraightOrPairs(nums);
    }
    else if (size%3 == 2) {
        std::sort(nums.begin(), nums.end());
        unsigned index = 0;
        bool h = true;
        h = isCompleted(nums, index);
        return h;
    }
    else {
        return false;
    }
}

bool MajhongAlgorithm::take2Pairs(vector<unsigned>& nums, unsigned& index) {
    if (index > 0) {
        unsigned num = nums[index-1];
        while (nums[index] == num)
            index++;
    }

    for (; index < nums.size() - 1; index++) {
        if (nums[index] == nums[index + 1]) {
            nums.erase(nums.begin() + index, nums.begin() + index + 2);
            index += 2;
            return true;
        }
    }
    return false;
}

bool MajhongAlgorithm::take3Pairs(vector<unsigned>& nums) {
    if (nums.empty()) return true;
    if (nums[0] == nums[1] && nums[0] == nums[2]) {
        nums.erase(nums.begin(), nums.begin() + 3);
        return true;
    }
    return false;
}

bool MajhongAlgorithm::take3Straight(vector<unsigned>& nums) {
    if (nums.empty()) return true;
    if (nums[0] + 1 == nums[1] && nums[1] + 1 == nums[2]) {
        nums.erase(nums.begin(), nums.begin() + 3);
        return true;
    }
    return false;
}

bool MajhongAlgorithm::isAllStraightOrPairs(vector<unsigned>& nums) {
    while (take3Pairs(nums) || take3Straight(nums)) {
        if (nums.empty())
            return true;
    }
    return false;
}

bool MajhongAlgorithm::isCompleted(vector<unsigned>& nums, unsigned& index) {
    vector<unsigned> numsCopy(nums);
    while (take2Pairs(nums, index)) {
        if (isAllStraightOrPairs(nums))
            return true;
        else
            nums = numsCopy;
    }
    return false;
}
