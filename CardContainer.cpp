#include "CardContainer.h"

CardContainer::CardContainer(QWidget *parent) :
    QLabel(parent),
    isDown(true)
{
}

CardContainer::CardContainer(const QString &text, QWidget *parent) :
    QLabel(text, parent),
    isDown(true)
{
}

void CardContainer::setImage(const QImage &image)
{
    if (!image.isNull())
        setPixmap(QPixmap::fromImage(image.scaledToHeight(200)));
}

void CardContainer::moveUpBack(bool up)
{
    if (up)
        moveUp();
    else
        moveBack();
}

void CardContainer::mousePressEvent(QMouseEvent *)
{
    moveUpBack(isDown);
    emit clicked();
}

void CardContainer::moveUp()
{
    isDown = false;
    this->move(x(), y()-20);
}

void CardContainer::moveBack()
{
    if (isDown)
        return;
    isDown = true;
    this->move(x(), y() + 20);
}
