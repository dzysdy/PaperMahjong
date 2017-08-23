#include "CardsWidget.h"
#include "CardContainer.h"
#include "PaperCard.h"
#include "Util.h"
#include <QHBoxLayout>

CardsWidget::CardsWidget(QWidget *parent) :
    QWidget(parent),
    layout(nullptr)
{
}

void CardsWidget::initail(unsigned num)
{
    if (layout)
        return;
    layout = new QHBoxLayout(this);
    while (num--) {
        CardContainer* cardContainer = new CardContainer();
        layout->addWidget(cardContainer);
        cardContainers.push_back(cardContainer);
        connect(cardContainer, &CardContainer::clicked, this, &CardsWidget::onCardClicked);
    }
    cardsNum = 0;
}

void CardsWidget::addCard(PaperCard *card)
{
    if (cardContainers.size() - cardsNum > 0) {
        CardContainer* cardContainer = cardContainers[cardsNum];
        QImage image(Util::getResourcePath() + card->getName());
        cardContainer->setText(card->getName());
        cardContainer->setImage(image);
        cardContainer->setUserData(0, card);
        cardsNum++;
    }
}

void CardsWidget::addCard(const QList<PaperCard *> cards)
{
    for (PaperCard* card : cards) {
        addCard(card);
    }
}

void CardsWidget::onCardClicked()
{
    CardContainer* cardContainer = static_cast<CardContainer*>(sender());
    if (selectedContainers.contains(cardContainer)) {
        selectedContainers.removeOne(cardContainer);
    }
    else {
        selectedContainers.push_back(cardContainer);
    }
}

void CardsWidget::setMode(CardsSelectedMode mode)
{
    csmMode = mode;
}

QList<CardContainer*> CardsWidget::takeSelectedCards()
{
    QList<CardContainer*> containers;
    for (CardContainer* container : selectedContainers) {
        container->setParent(nullptr);
        layout->removeWidget(container);
        containers.push_back(container);
    }
    this->update();
    selectedContainers.clear();
    return containers;
}

QList<PaperCard *> CardsWidget::getSelectedCards() const
{
    QList<PaperCard *> selectedCards;
    for (CardContainer* container : selectedContainers) {
        PaperCard* card = static_cast<PaperCard*>(container->userData(0));
        selectedCards.push_back(card);
    }
    return selectedCards;
}
