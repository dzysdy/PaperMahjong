#ifndef HAPPYGROUPWIDGET_H
#define HAPPYGROUPWIDGET_H

#include <QWidget>
#include <array>

class QLabel;
class PaperCard;
class HappyGroupWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HappyGroupWidget(QWidget *parent = 0);
    ~HappyGroupWidget();

    void setCards(QList<PaperCard*> cards);
signals:

public slots:

private:

    std::array<QLabel*, 3> containers;
    QList<PaperCard*> cards;
};

#endif // HAPPYGROUPWIDGET_H
