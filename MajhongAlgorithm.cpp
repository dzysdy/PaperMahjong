#include "MajhongAlgorithm.h"
#include "HappyGroupHelper.h"
#include <algorithm>

MajhongAlgorithm::MajhongAlgorithm()
{
    HappyGroupHelper::initial();
}

bool MajhongAlgorithm::isChow(vector<unsigned> nums) {
    if (nums.size() != 3)
        return false;
    std::sort(nums.begin(), nums.end());
    return nums[0] + 1 == nums[1] && nums[1] + 1 == nums[2];
}

bool MajhongAlgorithm::isPair(const vector<unsigned> &nums)
{
    if (nums.size() != 2)
        return false;
    return nums[0] == nums[1];
}

bool MajhongAlgorithm::isMelds(const vector<unsigned> &nums) {
    if (nums.size() != 3)
        return false;
    return nums[0] == nums[1] && nums[0] == nums[2];
}

bool MajhongAlgorithm::isHappyGroup(vector<unsigned> nums) {
    return HappyGroupHelper::isAHappyGroup(nums);
}

bool MajhongAlgorithm::isWinningHand(vector<unsigned> nums) {
    unsigned size = nums.size();
    if (size%3 == 0) {
        sort(nums.begin(), nums.end());
        return takeAllMeldsAndChow(nums);
    }
    else if (size%3 == 2) {
        sort(nums.begin(), nums.end());
        unsigned index = 0;
        return isWinningHand(nums, index);
    }
    else {
        return false;
    }
}

bool MajhongAlgorithm::isReadyHand(const vector<unsigned> &nums)
{
    return false;
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

vector<vector<unsigned> > MajhongAlgorithm::scanChow(const vector<unsigned>& nums, unsigned targetNumber)
{
    vector<vector<unsigned> > allStraights;
    auto left1 = std::find(nums.begin(), nums.end(), targetNumber - 1);
    auto right1 = std::find(nums.begin(), nums.end(), targetNumber + 1);
    if (left1 != nums.end()) {
        auto left2 = std::find(nums.begin(), nums.end(), targetNumber - 2);
        if (left2 != nums.end()) {
            vector<unsigned> straight{left2 - nums.begin(), left1 - nums.begin()};
            allStraights.push_back(straight);
        }
    }

    if (right1 != nums.end()) {
        auto right2 = std::find(nums.begin(), nums.end(), targetNumber + 2);
        if (right2 != nums.end()) {
            vector<unsigned> straight{right1 - nums.begin(), right2 - nums.begin()};
            allStraights.push_back(straight);
        }
    }

    if (left1 != nums.end() && right1 != nums.end()) {
        vector<unsigned> straight{left1 - nums.begin(), right1 - nums.begin()};
        allStraights.push_back(straight);
    }
    return allStraights;
}

MahjongSocreRecorder MajhongAlgorithm::calcScore(vector<unsigned> nums)
{
    MahjongSocreRecorder mahjongScore;
    vector<unsigned> score;
    std::sort(nums.begin(), nums.end());
    takeAllMeldsAndChow(nums);
    //score.push_back();
    return mahjongScore;
}

bool MajhongAlgorithm::takePair(vector<unsigned>& nums, unsigned& index) {
    if (index > 0) {
        unsigned num = nums[index-1];
        while (nums[index] == num)//index range.  to be fixed
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

bool MajhongAlgorithm::takeOneMelds(vector<unsigned>& nums) {
    if (nums.empty()) return true;
    if (nums[0] == nums[1] && nums[0] == nums[2]) {
        nums.erase(nums.begin(), nums.begin() + 3);
        return true;
    }
    return false;
}

bool MajhongAlgorithm::takeOneChow(vector<unsigned>& nums) {
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

bool MajhongAlgorithm::takeAllMeldsAndChow(vector<unsigned>& nums) {
    while (takeOneMelds(nums) || takeOneChow(nums)) {
        if (nums.empty())
            return true;
    }
    return false;
}

bool MajhongAlgorithm::isWinningHand(vector<unsigned>& nums, unsigned& index) {
    vector<unsigned> numsCopy(nums);
    while (takePair(nums, index)) {
        if (takeAllMeldsAndChow(nums))
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

unsigned MajhongAlgorithm::calcMeldsAndChowsCount(const vector<unsigned> &nums)
{
    return 0;
}
