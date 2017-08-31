#include "HappyGroupHelper.h"
#include "Util.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QString>
#include <assert.h>

bool HappyGroupHelper::isInitialed = false;
QList<HappyGroupHelper::HappyGroup> HappyGroupHelper::happyGroups;

bool HappyGroupHelper::isAHappyGroup(std::vector<unsigned> numbers) {
    assert(isInitialed);
    HappyGroup group;
    for (unsigned number: numbers) {
        group.addNumber(number);
    }
    return happyGroups.contains(group);
}

unsigned HappyGroupHelper::getHappyGroupNum()
{
    return happyGroups.size();
}

std::set<unsigned> HappyGroupHelper::getHappyGroup(unsigned index)
{
    HappyGroup happyGroup = happyGroups[index];
    return happyGroup.numbers;
}

void HappyGroupHelper::initial()
{
    QFile file(Util::getResourcePath() + "happyGroup.json");
    if (file.open(QFile::ReadOnly)) {
        QJsonParseError err;
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &err);
        if (err.error == QJsonParseError::NoError) {
            QJsonObject obj = doc.object();
            QJsonArray array = obj["happy_groups"].toArray();
            for (const QJsonValue& v : array) {
                QJsonArray group = v.toArray();
                HappyGroup happyGroup;
                for (QJsonValue card: group) {
                    QString cardName = card.toString();
                    unsigned cardNumber = getCardNumberTypeByName(cardName);
                    happyGroup.addNumber(cardNumber);
                }
                happyGroups.push_back(happyGroup);
            }
            isInitialed = true;
            return;
        }
    }
    assert(false);
}

unsigned HappyGroupHelper::getCardNumberTypeByName(const QString &name)
{
    unsigned number = 0;
    if (name == "sharks") {
        number = PaperCard::CT_SHARKS;
    }
    else if (name == "white") {
        number = PaperCard::CT_WHITEFLOWER;
    }
    else if (name == "red") {
        number = PaperCard::CT_REDFLOWER;
    }
    else if (name.contains("b_")) {
        number = PaperCard::CT_DOTS;
        number += name.right(1).toInt() - 1;
    }
    else if (name.contains("t_")) {
        number = PaperCard::CT_BAMBOO;
        number += name.right(1).toInt() - 1;
    }
    else if (name.contains("w_")) {
        number = PaperCard::CT_CHARACTERS;
        number += name.right(1).toInt() - 1;
    }
    return number;
}
