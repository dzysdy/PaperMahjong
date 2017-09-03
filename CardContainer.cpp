#include "CardContainer.h"
#include "PaperCard.h"
#include "Util.h"
#include <QDebug>

#define CARDMINWIDTH 80
#define CARDMINHEIGHT 200
CardContainer::CardContainer(QWidget *parent) :
    QLabel(parent),
    paperCard(nullptr),
    selected(false)
{
    this->setMinimumWidth(CARDMINWIDTH);
}

CardContainer::CardContainer(const QString &text, QWidget *parent) :
    QLabel(text, parent),
    paperCard(nullptr),
    selected(false)
{
    this->setMinimumWidth(CARDMINWIDTH);
}

void CardContainer::setImage(const QImage &image)
{
    if (!image.isNull()) {
        QImage img = image.scaledToHeight(CARDMINHEIGHT);
        setPixmap(QPixmap::fromImage(img));
        setMinimumWidth(img.width());
        setMaximumWidth(img.width());
    }
}

void CardContainer::setSelected(bool b)
{
    if (selected != b && paperCard) {
        selected = b;
        updateView();
    }
}

void CardContainer::setCard(PaperCard *card)
{
    setSelected(false);
    paperCard = card;
    if (paperCard) {
        QImage image(Util::getResourcePath() + "/sg/" + paperCard->getName());
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
