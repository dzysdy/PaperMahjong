#include "CppInterface.h"
#include <assert.h>

CppInterface::CppInterface()
{

}

QString nums2String(const vector<unsigned>& nums) {
    QString tiles;
    for (unsigned num: nums) {
        tiles += QString::number(num) + "-";
    }
    if (tiles.endsWith("-")) {
        tiles.remove(tiles.size() - 1, 1);
    }
    return tiles;
}

void CppInterface::analysisTiles(QString tileString)
{
    vector<unsigned> nums;
    int type = 0;
    for (int i = tileString.size() - 1; i >= 0; i--) {
        QChar c = tileString[i];
        if (c == 'm') {
            type = 20;
        }
        else if (c == 's') {
            type = 10;
        }
        else if (c == 'p') {
            type = 0;
        }
        else if (c.isNumber()) {
            nums.push_back(type + c.digitValue());
        }
    }
    std::sort(nums.begin(), nums.end());
    emit tileModelUpdated(nums2String(nums));
    analysisTiles(nums);
}

bool removeValue(vector<unsigned>& nums, unsigned base)
{
    auto finded = std::find(nums.begin(), nums.end(), base);
    if (finded != nums.end()) {
        nums.erase(finded);
        return true;
    }
    return false;
}

bool removePair(vector<unsigned>& nums, unsigned base)
{
    if (removeValue(nums, base)) {
        if (removeValue(nums, base)) {
            return true;
        }
    }
    return false;
}

bool removeMeld(vector<unsigned>& nums, unsigned base)
{
    if (removeValue(nums, base)) {
        if (removeValue(nums, base)) {
            if (removeValue(nums, base)) {
                return true;
            }
        }
    }
    return false;
}

bool removeChow(vector<unsigned>& nums, unsigned base)
{
    if (removeValue(nums, base)) {
        if (removeValue(nums, base + 1)) {
            if (removeValue(nums, base + 2)) {
                return true;
            }
        }
    }
    return false;
}

bool removeMelds(vector<unsigned>& nums, const Melds& meld)
{
    bool ok = false;
    switch (meld.type_) {
    case Melds::MT_PAIR:
        ok = removePair(nums, meld.base_);
        break;
    case Melds::MT_MELD:
        ok = removeMeld(nums, meld.base_);
        break;
    case Melds::MT_CHOW:
        ok = removeChow(nums, meld.base_);
        break;
    default:
        break;
    }
    return ok;
}

int calcHalfMeldsCount(const vector<unsigned>& nums)
{
    int hmCount = 0;
    for (int i = 0; i < nums.size() - 1; ) {
        if (nums[i + 1] - nums[i] <= 2) {
            hmCount++;
            i += 2;
        }
        else {
            i++;
        }
    }
    return hmCount;
}

int calcReadyStepsInThisPermutation(const vector<unsigned>& nums, int missingMeldsCount, bool hasPair)
{
    assert(missingMeldsCount >= 0);
    int result = -1; //胡牌是-1向听， 听牌是0向听;
    if (!hasPair) {
        result++;
    }
    int hmCount = calcHalfMeldsCount(nums);
    int steps = hmCount > missingMeldsCount? missingMeldsCount: (2*missingMeldsCount - hmCount);
    result += steps;
    return result;
}

int factorial(int m) {
    int sum = 1;
    for (int i = m; i > 0; i--) {
        sum *= i;
    }
    return sum;
}

int calcReadySteps(const vector<unsigned>& nums, vector<Melds> melds)
{
    /// * 面子：M(meld); 雀头: P(pair); 孤牌: L(lonely tile); 搭子：HM(half meld)
    /// * s张牌，另m = s/3; 则有胡牌为 m*M + 1*P;
    /// * 听牌为 m*M+1*L or (m-1)*M + 1*P + 1*HM or (m-1)*M + 2*P
    /// * 一向听 (m-1)*M + 2*L + 1*P or ...
    /// *
    ///

    //C(m,n) m = melds.size, n = (nums.size/3)+1
    int showHandMeldsCount = nums.size()/3;
    int showHandCount = showHandMeldsCount + 1;
    int minReadySteps = showHandMeldsCount*2 + 1;//init to max ready steps
    int remainingTimes = factorial(melds.size());
    qDebug()<<__func__<<remainingTimes;
    int times = 0;
    std::sort(melds.begin(), melds.end());
    do
    {
        times++;
        if (times%10000000 == 0) {
            qDebug()<<__func__<<remainingTimes<<minReadySteps;
        }
        remainingTimes--;
        vector<unsigned> copyNums(nums);
        int currentMeldsCount = 0;
        bool pair = false;
        for (int i = 0; i <= showHandCount && i < melds.size(); i++) {
            Melds meld = melds[i];
            if (meld.type_ == Melds::MT_PAIR && pair) break;
            if (!removeMelds(copyNums, meld)) break;

            if (meld.type_ != Melds::MT_PAIR) {
                currentMeldsCount++;
            }
            else {
                pair = true;
            }
        }
        int readSteps = calcReadyStepsInThisPermutation(copyNums, showHandMeldsCount - currentMeldsCount, pair);
        if (readSteps < minReadySteps) {
            minReadySteps = readSteps;
        }
    }while(std::next_permutation(melds.begin(), melds.end()));
    return minReadySteps;
}

void findAllMelds(vector<unsigned> nums, vector<Melds>& melds)
{
    if (nums.size() < 3)
        return;
    int id = 0;
    unsigned base = nums.front();
    for (int i = 1; i < nums.size() - 2; i++) {
        if (nums[i] == base) {
            melds.emplace_back(base, Melds::MT_PAIR, id++);
            if (nums[i + 1] == base) {
                melds.emplace_back(base, Melds::MT_MELD, id++);
            }
        }

        int delta = 1;
        for (int j = i; j < nums.size(); j++) {
            if (nums[j] > base + delta)
                break;
            if (nums[j] == base + delta) {
                if (++delta == 3) {
                    melds.emplace_back(base, Melds::MT_CHOW, id++);
                }
            }
        }

        base = nums[i];
    }

    if (base == nums.back()) {
        melds.emplace_back(base, Melds::MT_PAIR, id++);
    }
}

void CppInterface::analysisTiles(vector<unsigned> nums)
{
    vector<unsigned> lonelyTiles = takeLonelyTiles(nums);
    if (!lonelyTiles.empty()) {
        QString lonelyTilesString = nums2String(lonelyTiles);
        emit lonelyTilesUpdated(lonelyTilesString);
    }

    //计算向听数
    vector<Melds> melds;
    findAllMelds(nums, melds);
    int readySteps = calcReadySteps(nums, melds);
    emit readyStepsUpdated(readySteps);
    //遍历打掉每张牌的进张情况 note: 有效进张为所有手牌的临牌

//    vector<unsigned> copyNums(nums);
//    //remove repeat num
//    for (auto itor = nums.begin(); itor < nums.end(); ) {
//        if (*itor == *(itor + 1)) {
//            itor = nums.erase(itor);
//        }
//        else {
//            itor++;
//        }
//    }

//    // scan all melds

//    vector<Melds> melds;
//    for (int i = 0; i < nums.size(); i++) {
//        if (nums[i] + 1 == nums[i + 1] && nums[i] + 2 == nums[i + 2]) {
//            melds.emplace_back(nums[i], nums[i + 1], nums[i + 2]);
//        }
//    }
}

void CppInterface::calcAdjacentTiles(const vector<unsigned>& srcNums, vector<unsigned>& adjacentNums){
    for (unsigned num: srcNums) {
        apendIfNotContain(num, adjacentNums);
        if (num > 30) {
            continue;
        }
        if (num != 1) {
            apendIfNotContain(num - 1, adjacentNums);
        }
        if (num != 9) {
            apendIfNotContain(num + 1, adjacentNums);
        }
    }
}

bool CppInterface::apendIfNotContain(unsigned i, vector<unsigned> &srcNums)
{
    auto finded = std::find(srcNums.begin(), srcNums.end(), i);
    if (finded != srcNums.end()) {
        srcNums.push_back(i);
        return true;
    }
    return false;
}

vector<unsigned> CppInterface::takeLonelyTiles(vector<unsigned>& nums)
{
    std::sort(nums.begin(), nums.end());
    vector<unsigned> lonelyTiles;
    for (int i = 0; i < nums.size(); i++) {
        bool leftLonely = i - 1 >= 0? (nums[i] - nums[i - 1] > 2): true;
        bool rightLonely = i + 1 < nums.size()? (nums[i + 1] - nums[i] > 2): true;
        if (leftLonely && rightLonely ) {
            lonelyTiles.push_back(nums[i]);
        }
    }
    return lonelyTiles;
}
