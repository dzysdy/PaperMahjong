#ifndef HAPPYGROUPHELPER_H
#define HAPPYGROUPHELPER_H

#include "PaperCard.h"
#include <set>
#include <vector>
#include <algorithm>
class HappyGroupHelper
{
public:
    HappyGroupHelper() = delete;

    static void initial();
    static bool isAHappyGroup(std::vector<unsigned> numbers);
    static unsigned getHappyGroupNum();
    static std::set<unsigned> getHappyGroup(unsigned index);

private:
    class HappyGroup {
    public:
        HappyGroup() = default;

        void addNumber(unsigned number) {
            numbers.insert(number);
        }

        bool operator ==(const HappyGroup& that) {
            if (numbers.size() != that.numbers.size())
                return false;
            return std::equal(numbers.begin(), numbers.end(), that.numbers.begin());
        }

        std::set<unsigned> numbers;
    };

    static unsigned getCardNumberTypeByName(const QString& name);

    static QList<HappyGroup> happyGroups;
    static bool isInitialed;
};

#endif // HAPPYGROUPHELPER_H
