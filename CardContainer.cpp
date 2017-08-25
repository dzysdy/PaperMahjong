#include "CardContainer.h"
#include "PaperCard.h"
#include "Util.h"

CardContainer::CardContainer(QWidget *parent) :
    QLabel(parent),
    isDown(true)
{
}

CardContainer::CardContainer(const QString &text, QWidget *parent) :
    QLabel(text, parent),
    isDown(true),
    paperCard(nullptr)
{
}

void CardContainer::setImage(const QImage &image)
{
    if (!image.isNull()) {
        QImage img = image.scaledToHeight(200);
        setPixmap(QPixmap::fromImage(img));
        setMinimumWidth(img.width());
        setMaximumWidth(img.width());
    }
}

void CardContainer::setCard(PaperCard *card)
{
    paperCard = card;
    moveBack();
    if (paperCard) {
        QImage image(Util::getResourcePath() + paperCard->getName());
        setText(card->getName());
        setImage(image);
        show();
    }
    else {
        hide();
    }
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

PaperCard *CardContainer::getPaperCard() const
{
    return paperCard;
}
