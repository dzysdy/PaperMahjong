#include "HappyGroupWidget.h"
#include "CardContainer.h"
#include "PaperCard.h"
#include "Util.h"
#include <QVBoxLayout>

HappyGroupWidget::HappyGroupWidget(QWidget *parent) :
    QWidget(parent)
{
}

void HappyGroupWidget::setCards(QList<PaperCard*> cards)
{
//    if (cards.size() != 3)
//        return;
    int i = 0;
    for (PaperCard* card : cards) {
        CardContainer* container = new CardContainer();
        container->setCard(card);
        container->setParent(this);
        container->move(0, 0 + (i++)*container->height()*0.15);
    }
}
