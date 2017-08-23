#ifndef CARDSWIDGET_H
#define CARDSWIDGET_H

#include <QWidget>

class PaperCard;
class QHBoxLayout;
class CardContainer;
class CardsWidget : public QWidget
{
    Q_OBJECT
public:
    enum CardsSelectedMode {
        CSM_CUSTOM,
        CSM_LIAOXI,
        CSM_CHI,
    };

    explicit CardsWidget(QWidget *parent = 0);

    void initail(unsigned num);
    void addCard(PaperCard* card);
    void addCard(const QList<PaperCard*> cards);
    void setMode(CardsSelectedMode mode);
    QList<CardContainer*> takeSelectedCards();
    QList<PaperCard *> getSelectedCards() const;

signals:

public slots:
    void onCardClicked();

private:
    QHBoxLayout* layout;
    QList<CardContainer*> cardContainers;
    QList<CardContainer*> selectedContainers;
    CardsSelectedMode csmMode;
    unsigned cardsNum;
};

#endif // CARDSWIDGET_H
