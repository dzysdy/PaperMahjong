#include "HappyGroupWidget.h"
#include "PaperCard.h"
#include "Util.h"
#include <QVBoxLayout>
#include <QLabel>

HappyGroupWidget::HappyGroupWidget(QWidget *parent) :
    QWidget(parent)
{
    for (unsigned i = 0; i < containers.size(); i++) {
        QLabel* container = new QLabel();
        container->setParent(this);
        container->move(0, 0 + i*container->height()*0.08);
        containers[i] = container;
    }
    this->setMinimumWidth(50);
}

HappyGroupWidget::~HappyGroupWidget()
{
}

void HappyGroupWidget::setCards(QList<PaperCard*> cards)
{
    if (cards.size() > 3)
        return;
    int i = 0;
    for (PaperCard* card : cards) {
        card->setSelected(false);
        containers[i++]->setPixmap(QPixmap::fromImage(QImage(Util::getResourcePath() + "sg/" + card->getName()).scaledToWidth(50)));
    }
}
