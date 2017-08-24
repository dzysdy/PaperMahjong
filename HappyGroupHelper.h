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
    static bool isAHappGroup(std::vector<unsigned> numbers);

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
            return std::equal(numbers.begin(), numbers.begin(), that.numbers.begin());
        }

    private:
        std::set<unsigned> numbers;
    };

    static unsigned getCardNumberTypeByName(const QString& name);

    static QList<HappyGroup> happyGroups;
    static bool isInitialed;
};

#endif // HAPPYGROUPHELPER_H
