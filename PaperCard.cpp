#include "PaperCard.h"
#include <assert.h>
#include <QDebug>

PaperCard::PaperCard(unsigned number, QObject *parent) :
    QObject(parent),
    cardNumber(number),
    selected(false)
{
    setNameByNumber(number);
}

QString PaperCard::getName() const
{
    return name;
}

unsigned PaperCard::getCardNumber() const
{
    return cardNumber;
}

void PaperCard::setNameByNumber(unsigned number)
{
    if (number < CT_TIAO) {
        name = "b_" + QString::number(number - CT_BING + 1);
    }
    else if (number < CT_WAN) {
        name = "t_" + QString::number(number - CT_TIAO + 1);
    }
    else if (number < CT_WHITE) {
        name = "w_" + QString::number(number - CT_WAN + 1);
    }
    else {
        switch (number) {
        case CT_WHITE:
            name = "white";
            break;
        case CT_RED:
            name = "red";
            break;
        case CT_SHARKS:
            name = "sharks";
            break;
        default:
            assert(false);
            break;
        }
    }
}

bool PaperCard::isSelected() const
{
    return selected;
}

void PaperCard::setSelected(bool value)
{
    selected = value;
}
