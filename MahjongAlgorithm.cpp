#include "MahjongAlgorithm.h"
#include "HappyGroupHelper.h"
#include <algorithm>

MahjongAlgorithm::MahjongAlgorithm()
{
    HappyGroupHelper::initial();
}

bool MahjongAlgorithm::isChow(vector<unsigned> nums) {
    if (nums.size() != 3)
        return false;
    std::sort(nums.begin(), nums.end());
    return nums[0] + 1 == nums[1] && nums[1] + 1 == nums[2];
}

bool MahjongAlgorithm::isPair(const vector<unsigned> &nums)
{
    if (nums.size() != 2)
        return false;
    return nums[0] == nums[1];
}

bool MahjongAlgorithm::isMelds(const vector<unsigned> &nums) {
    if (nums.size() != 3)
        return false;
    return nums[0] == nums[1] && nums[0] == nums[2];
}

bool MahjongAlgorithm::isHappyGroup(vector<unsigned> nums) {
    return HappyGroupHelper::isAHappyGroup(nums);
}

bool MahjongAlgorithm::isWinningHand(vector<unsigned> nums) {
    size_t size = nums.size();
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

bool MahjongAlgorithm::isReadyHand(const vector<unsigned> &nums)
{
    return false;
}

vector<vector<unsigned>> MahjongAlgorithm::scanHappyGroups(const vector<unsigned>& nums)
{
    vector<vector<unsigned>> allGroups;
    unsigned count = HappyGroupHelper::getHappyGroupNum();
    for (unsigned i = 0; i < count; ++i) {
        set<unsigned> happyGroup = HappyGroupHelper::getHappyGroup(i);
        scanHappyGroup(nums, happyGroup, allGroups);
    }
    return allGroups;
}

vector<vector<unsigned> > MahjongAlgorithm::scanChow(const vector<unsigned>& nums, unsigned targetNumber)
{
    vector<vector<unsigned> > allChows;
    auto left1 = std::find(nums.begin(), nums.end(), targetNumber - 1);
    auto right1 = std::find(nums.begin(), nums.end(), targetNumber + 1);
    if (left1 != nums.end()) {
        auto left2 = std::find(nums.begin(), nums.end(), targetNumber - 2);
        if (left2 != nums.end()) {
            vector<unsigned> chow{unsigned(left2 - nums.begin()), unsigned(left1 - nums.begin())};
            allChows.push_back(chow);
        }
    }

    if (right1 != nums.end()) {
        auto right2 = std::find(nums.begin(), nums.end(), targetNumber + 2);
        if (right2 != nums.end()) {
            vector<unsigned> chow{unsigned(right1 - nums.begin()), unsigned(right2 - nums.begin())};
            allChows.push_back(chow);
        }
    }

    if (left1 != nums.end() && right1 != nums.end()) {
        vector<unsigned> chow{unsigned(left1 - nums.begin()), unsigned(right1 - nums.begin())};
        allChows.push_back(chow);
    }
    return allChows;
}

int MahjongAlgorithm::scanMelds(const vector<unsigned> &nums, unsigned targetNumber)
{
    auto sameNumItor = std::find(nums.begin(), nums.end(), targetNumber);
    if (sameNumItor != nums.end() && (sameNumItor + 1) != nums.end() && *(sameNumItor + 1) == targetNumber) {
        return (int)(sameNumItor - nums.begin());
    }
    return -1;
}

vector<unsigned> MahjongAlgorithm::scanLonelyCard(const vector<unsigned>& nums)
{
    vector<unsigned> indexs;
    //std::sort(nums.begin(), nums.end());//wrong sort broke the index;
    for (int i = 0; i < nums.size(); i++) {
        bool leftLonely = i - 1 >= 0? (nums[i] - nums[i - 1] > 2): true;
        bool rightLonely = i + 1 < nums.size()? (nums[i + 1] - nums[i] > 2): true;
        if (leftLonely && rightLonely ) {
            indexs.push_back(i);
        }
    }
    return indexs;
}

MahjongSocreRecorder MahjongAlgorithm::calcScore(const vector<unsigned>& nums)
{
    MahjongSocreRecorder mahjongScore;
    vector<unsigned> score;
    unsigned readHandScore = calcMeldsAndChowsCount(nums);
    score.push_back(readHandScore);

    return mahjongScore;
}

bool MahjongAlgorithm::takePair(vector<unsigned>& nums, unsigned& index) {
    if (index > 0) {
        unsigned num = nums[index-1];
        while (index < nums.size() && nums[index] == num )
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

bool MahjongAlgorithm::takeOneMelds(vector<unsigned>& nums) {
    if (nums.empty()) return true;
    if (nums[0] == nums[1] && nums[0] == nums[2]) {
        nums.erase(nums.begin(), nums.begin() + 3);
        return true;
    }
    return false;
}

bool MahjongAlgorithm::takeOneChow(vector<unsigned>& nums) {
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

bool MahjongAlgorithm::takeAllMeldsAndChow(vector<unsigned>& nums) {
    while (takeOneMelds(nums) || takeOneChow(nums)) {
        if (nums.empty())
            return true;
    }
    return false;
}

bool MahjongAlgorithm::isWinningHand(vector<unsigned>& nums, unsigned& index) {
    vector<unsigned> numsCopy(nums);
    while (takePair(nums, index)) {
        if (takeAllMeldsAndChow(nums))
            return true;
        else
            nums = numsCopy;
    }
    return false;
}

void MahjongAlgorithm::scanHappyGroup(const vector<unsigned>& nums, const set<unsigned>& happyGroup, vector<vector<unsigned>>& groups)
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

unsigned MahjongAlgorithm::calcMeldsAndChowsCount(const vector<unsigned> &nums)
{
    vector<unsigned> copyNums(nums);
    std::sort(copyNums.begin(), copyNums.end());
    takeAllMeldsAndChow(copyNums);// to be donw.
    return (17 - copyNums.size())%3;
}
