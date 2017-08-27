#include "CardContainer.h"
#include "PaperCard.h"
#include "Util.h"
#include <QDebug>

CardContainer::CardContainer(QWidget *parent) :
    QLabel(parent),
    paperCard(nullptr),
    selected(false)
{
}

CardContainer::CardContainer(const QString &text, QWidget *parent) :
    QLabel(text, parent),
    paperCard(nullptr),
    selected(false)
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

void CardContainer::setSelected(bool b)
{
    if (selected != b) {
        selected = b;
        updateView();
    }
}

void CardContainer::setCard(PaperCard *card)
{
    setSelected(false);
    paperCard = card;
    if (paperCard) {
        QImage image(Util::getResourcePath() + paperCard->getName());
        setText(card->getName());
        setImage(image);
        show();
        setSelected(paperCard->isSelected());
    }
    else {
        hide();
    }
}

void CardContainer::updateView()
{
    if (selected) {
        this->move(x(), y()-20);
    }
    else {
        this->move(x(), y() + 20);
    }
    if (paperCard)
        paperCard->setSelected(selected);
}

void CardContainer::mousePressEvent(QMouseEvent *)
{
    setSelected(!selected);
    emit clicked();
}

PaperCard *CardContainer::getPaperCard() const
{
    return paperCard;
}
