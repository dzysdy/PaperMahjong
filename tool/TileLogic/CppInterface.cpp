#include "CppInterface.h"
#include <assert.h>
#include <set>
#include <time.h>
using std::set;

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
    clock_t t;
    t = clock();
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
        else if (c == 'z') {
            type = 30;
        }
        else if (c.isNumber()) {
            int digit = c.digitValue();
            if (type == 30)
                digit *= 3;
            nums.push_back(type + digit);
        }
    }
    std::sort(nums.begin(), nums.end());
    emit tileModelUpdated(nums2String(nums));
    analysisTiles(nums);
    clock_t deltaT = clock() - t;
    qDebug()<<__func__<<"cost:"<<((float)deltaT)/CLOCKS_PER_SEC;
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
    for (int i = 0; i < (int)nums.size() - 1; ) {
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

long long factorial(int m) {
    long long sum = 1;
    for (int i = m; i > 0; i--) {
        sum *= i;
    }
    return sum;
}

template <typename BidirIt>
class PermutationGenerater {
    PermutationGenerater(BidirIt first, BidirIt last, int digitNumber):
        first_(first), last_(last), digitNumber_(digitNumber),
        systemBase_(last - first), decimalIndex_(0)
    {
    }
/// A(4,4)
/// 1234
/// 1243
/// 1324
/// 1342
/// 1423
/// 1432
/// 2134
/// 2143
/// 2314
/// 从后面开始找，把最后一个数换到，遇到的第一个比他小的数的位置上去。

/// A(4,3) 1234
/// 12
/// 13
/// 14
/// 21
/// 23
/// 24
/// 31
/// 32
/// 34 ...
///
///
/// 12345
///
/// 123 45
/// 124 35
/// 125 34
/// 132
/// 134
/// 135
/// 14
///
    bool nextPermutation(BidirIt first, BidirIt last, int digitNumber) {
        if (first == last) return false;
        BidirIt i = last;
        if (first == --i) return false;

        while (true) {
            BidirIt i1, i2;

            i1 = i;
            if (*--i < *i1) {
                i2 = last;
                while (!(*i < *--i2));
                std::iter_swap(i, i2);
                std::reverse(i1, last);
                return true;
            }
            if (i == first) {
                std::reverse(first, last);
                return false;
            }
        }
    }

    BidirIt first_;
    BidirIt last_;
    int digitNumber_;
    int systemBase_;
    int decimalIndex_;
};

int calcReadySteps(const vector<unsigned>& nums, vector<Melds> melds, set<unsigned>& tilesCanBeDiscarded)
{
    /// * 面子：M(meld); 雀头: P(pair); 孤牌: L(lonely tile); 搭子：HM(half meld)
    /// * s张牌，另m = s/3; 则有胡牌为 m*M + 1*P;
    /// * 听牌为 m*M+1*L or (m-1)*M + 1*P + 1*HM or (m-1)*M + 2*P
    /// * 一向听 (m-1)*M + 2*L + 1*P or ...
    /// *
    ///

    //A(m,n) m = melds.size, n = (nums.size/3)+1
    int showHandMeldsCount = (int)nums.size()/3;
    int showHandCount = showHandMeldsCount + 1;
    int minReadySteps = showHandMeldsCount*2 + 1;//init to max ready steps
    long long remainingTimes = factorial((int)melds.size())/factorial((int)melds.size()-showHandCount);
    std::sort(melds.begin(), melds.end());
    do
    {
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
            tilesCanBeDiscarded.clear();
            if (minReadySteps < 0) {
                break;
            }
        }
        if (readSteps <= minReadySteps) {
            tilesCanBeDiscarded.insert(copyNums.begin(), copyNums.end());
        }
        if (melds.size() > showHandCount) {
            std::reverse(melds.begin()+showHandCount, melds.end());
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
    for (int i = 1; i < nums.size() - 1; i++) {
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

int calcReadySteps(const vector<unsigned>& nums, set<unsigned>& tilesCanBeDiscarded)
{
    vector<Melds> melds;
    findAllMelds(nums, melds);
    int readySteps = calcReadySteps(nums, melds, tilesCanBeDiscarded);
    return readySteps;
}

int calcReadySteps(const vector<unsigned>& nums)
{
    set<unsigned> tilesCanBeDiscarded;
    return calcReadySteps(nums, tilesCanBeDiscarded);
}

void CppInterface::analysisTiles(vector<unsigned> nums)
{
    vector<unsigned> lonelyTiles = takeLonelyTiles(nums);
    if (!lonelyTiles.empty()) {
        QString lonelyTilesString = nums2String(lonelyTiles);
        emit lonelyTilesUpdated(lonelyTilesString);
    }

    //计算向听数
    set<unsigned> tilesCanBeDiscarded;
    int readySteps = calcReadySteps(nums, tilesCanBeDiscarded);
    emit readyStepsUpdated(readySteps);
    //遍历打掉每张牌的进张情况 note: 有效进张为所有手牌的临牌
    if (readySteps < 0)
        return;

    class DisCardAndDraw{
    public:
        DisCardAndDraw():drawCount(0){}
        bool operator <(const DisCardAndDraw& that) {
            return drawCount < that.drawCount;
        }

        unsigned discardNum;
        vector<unsigned> drawNums;
        int drawCount;
    };

    vector<unsigned> adjacentNums;
    calcAdjacentTiles(nums, adjacentNums);
    vector<DisCardAndDraw> dcds;
    for (auto itor = tilesCanBeDiscarded.rbegin(); itor != tilesCanBeDiscarded.rend(); ++itor) {
        vector<unsigned> copyNums(nums);
        DisCardAndDraw dcd;
        if (removeValue(copyNums, *itor)) {
            dcd.discardNum = *itor;
            for (unsigned adjacentNum: adjacentNums) {
                if (adjacentNum != *itor) {
                    vector<unsigned> copyNums2(copyNums);
                    copyNums2.push_back(adjacentNum);
                    std::sort(copyNums2.begin(), copyNums2.end());
                    int rs = calcReadySteps(copyNums2);
                    if (rs < readySteps) {
                        dcd.drawNums.push_back(adjacentNum);
                        dcd.drawCount += 4;
                    }
                }
            }
            if (!dcd.drawNums.empty()) {
                dcds.push_back(dcd);
                qDebug()<<__func__<<"discard:"<<dcd.discardNum;
                qDebug()<<__func__<<"draws:"<<dcd.drawNums;
            }
        }
    }
    /// [
    ///     {
    ///         "discard": "",
    ///         "draws": ["",""]
    ///     }
    /// ]

    std::sort(dcds.begin(), dcds.end());
    std::reverse(dcds.begin(), dcds.end());
    QJsonArray dcdArray;
    for (DisCardAndDraw dcd: dcds) {
        if (!dcd.drawNums.empty()) {
            QJsonObject dcdObj;
            QJsonArray discardNumsArray;
            for (unsigned drawNum: dcd.drawNums) {
                QJsonObject obj;
                obj["draw"] = QString::number(drawNum);
                discardNumsArray.append(obj);
            }
            dcdObj["discard"] = QString::number(dcd.discardNum);
            dcdObj["draws"] = discardNumsArray;
            dcdArray.append(dcdObj);
        }
    }
    qDebug()<<__func__<<dcdArray;
    emit discardTilesUpdated(dcdArray);
}

void CppInterface::calcAdjacentTiles(const vector<unsigned>& srcNums, vector<unsigned>& adjacentNums){
    for (unsigned num: srcNums) {
        apendIfNotContain(num, adjacentNums);
        if (num > 30) {
            continue;
        }
        if (num%10 != 1) {
            apendIfNotContain(num - 1, adjacentNums);
        }
        if (num%10 != 9) {
            apendIfNotContain(num + 1, adjacentNums);
        }
    }
}

bool CppInterface::apendIfNotContain(unsigned i, vector<unsigned> &srcNums)
{
    auto finded = std::find(srcNums.begin(), srcNums.end(), i);
    if (finded == srcNums.end()) {
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
