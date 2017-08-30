#include "MajhongAlgorithm.h"
#include "HappyGroupHelper.h"
#include <algorithm>

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
    return HappyGroupHelper::isAHappyGroup(nums);
}

bool MajhongAlgorithm::isCompleteAHand(vector<unsigned> nums) {
    unsigned size = nums.size();
    if (size%3 == 0) {
        sort(nums.begin(), nums.end());
        return isAllStraightOrPairs(nums);
    }
    else if (size%3 == 2) {
        sort(nums.begin(), nums.end());
        unsigned index = 0;
        return isCompleted(nums, index);
    }
    else {
        return false;
    }
}

vector<vector<unsigned>> MajhongAlgorithm::scanHappyGroups(const vector<unsigned>& nums)
{
    vector<vector<unsigned>> allGroups;
    unsigned count = HappyGroupHelper::getHappyGroupNum();
    for (unsigned i = 0; i < count; ++i) {
        set<unsigned> happyGroup = HappyGroupHelper::getHappyGroup(i);
        scanHappyGroup(nums, happyGroup, allGroups);
    }
    return allGroups;
}

vector<vector<unsigned> > MajhongAlgorithm::scanStraight(vector<unsigned> nums, unsigned targetNumber)
{
    vector<vector<unsigned> > s;
    nums.push_back(targetNumber);
    std::sort(nums.begin(), nums.end());
return s;
}

int MajhongAlgorithm::calcScore(vector<unsigned> nums)
{
    std::sort(nums.begin(), nums.end());
    return 0;
}

bool MajhongAlgorithm::take2Pairs(vector<unsigned>& nums, unsigned& index) {
    if (index > 0) {
        unsigned num = nums[index-1];
        while (index < nums.size() && nums[index] == num )//index range.  to be fixed
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
    vector<unsigned> indexs{0};
    for (unsigned i = 1; i < nums.size(); i++) {
        unsigned num = nums[indexs.back()] + 1;
        if (num < nums[i]) {
            break;
        }
        else if (num == nums[i]) {
            indexs.push_back(i);
            if (indexs.size() == 3) {
                nums.erase(nums.begin() + indexs[2]);
                nums.erase(nums.begin() + indexs[1]);
                nums.erase(nums.begin() + indexs[0]);
                return true;
            }
        }
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

void MajhongAlgorithm::scanHappyGroup(const vector<unsigned>& nums, const set<unsigned>& happyGroup, vector<vector<unsigned>>& groups)
{
    vector<unsigned> group;
    auto finded = nums.begin();
    for (unsigned hGNum: happyGroup) {
        finded = std::find(finded + 1, nums.end(), hGNum);
        if (finded != nums.end()) {
            group.push_back(finded - nums.begin());
        }
        else {
            break;
        }
    }
    if (group.size() == happyGroup.size()) {
        groups.push_back(group);
    }
}
