#ifndef HAPPYGROUPWIDGET_H
#define HAPPYGROUPWIDGET_H

#include <QWidget>

class PaperCard;
class HappyGroupWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HappyGroupWidget(QWidget *parent = 0);

    void setCards(QList<PaperCard*> cards);
signals:

public slots:
};

#endif // HAPPYGROUPWIDGET_H
