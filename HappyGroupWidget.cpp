#include "HappyGroupWidget.h"
#include "CardContainer.h"
#include <QVBoxLayout>

HappyGroupWidget::HappyGroupWidget(QWidget *parent) :
    QWidget(parent)
{
    layout = new QVBoxLayout(this);
}

void HappyGroupWidget::setCardContainers(QList<CardContainer *> containers)
{
    if (containers.size() != 3)
        return;
    int i = 0;
    for (CardContainer* c : containers) {
        c->setParent(this);
        c->move(0, c->y() + (i++)*c->height()*0.15);
    }
}
