#include "CardsWidget.h"
#include "CardContainer.h"
#include "PaperCard.h"
#include "Util.h"
#include <QHBoxLayout>
#include <QDebug>

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
    qDebug()<<this<<__func__<<__LINE__<<cardContainers.size() << cardsNum ;
    if (cardContainers.size() - cardsNum > 0) {
        CardContainer* cardContainer = cardContainers[cardsNum++];
        cardContainer->setCard(card);
    }
    qDebug()<<this<<__func__<<__LINE__<<cardContainers.size() << cardsNum ;
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

QList<PaperCard*> CardsWidget::takeSelectedCards()
{
    qDebug()<<this<<__func__<<__LINE__<<cardContainers.size() << cardsNum ;
    //change to mvc, this is a view, papercards is model.
    QList<PaperCard*> cards;
    for (CardContainer* container : selectedContainers) {
        cardsNum--;
        layout->removeWidget(container);
        cardContainers.removeOne(container);
        container->hide();
        layout->addWidget(container);
        cardContainers.push_back(container);
        cards.push_back(container->getPaperCard());
    }
    selectedContainers.clear();
    qDebug()<<this<<__func__<<__LINE__<<cardContainers.size() << cardsNum ;
    return cards;
}

QList<PaperCard *> CardsWidget::getSelectedCards() const
{
    QList<PaperCard *> selectedCards;
    for (CardContainer* container : selectedContainers) {
        selectedCards.push_back(container->getPaperCard());
    }
    return selectedCards;
}
