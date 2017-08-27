#ifndef HAPPYGROUPWIDGET_H
#define HAPPYGROUPWIDGET_H

#include <QWidget>
#include <array>

class PaperCard;
class CardContainer;
class HappyGroupWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HappyGroupWidget(QWidget *parent = 0);

    void setCards(QList<PaperCard*> cards);
signals:

public slots:

private:
    std::array<CardContainer*, 3> containers;
};

#endif // HAPPYGROUPWIDGET_H
