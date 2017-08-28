#include "HappyGroupWidget.h"
#include "CardContainer.h"
#include "PaperCard.h"
#include "Util.h"
#include <QVBoxLayout>
#include <QLabel>

HappyGroupWidget::HappyGroupWidget(QWidget *parent) :
    QWidget(parent)
{
    for (unsigned i = 0; i < containers.size(); i++) {
        CardContainer* container = new CardContainer();
        container->setParent(this);
        container->move(0, 0 + i*container->height()*0.15);
        containers[i] = container;
    }
}

void HappyGroupWidget::setCards(QList<PaperCard*> cards)
{
    if (cards.size() > 3)
        return;
    int i = 0;
    for (PaperCard* card : cards) {
        containers[i++]->setCard(card);
    }
}
