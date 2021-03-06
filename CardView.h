#ifndef CARDSWIDGET_H
#define CARDSWIDGET_H

#include <QWidget>

class PaperCard;
class QHBoxLayout;
class CardContainer;
class CardModel;

class CardView: public QWidget {
    Q_OBJECT

public:
    CardView(QWidget* parent = nullptr);

    void initail(unsigned num);
    void setModel(CardModel* cardModel);
    void update();

private slots:
    void onUpdated();
    void onCardClicked();

private:
    void showData(CardModel *cardModel);

    CardModel* model;
    QHBoxLayout* layout;
    QList<CardContainer*> cardContainers;
};

#endif // CARDSWIDGET_H
