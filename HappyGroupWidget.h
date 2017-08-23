#ifndef HAPPYGROUPWIDGET_H
#define HAPPYGROUPWIDGET_H

#include <QWidget>

class QVBoxLayout;
class CardContainer;
class HappyGroupWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HappyGroupWidget(QWidget *parent = 0);

    void setCardContainers(QList<CardContainer*> containers);
signals:

public slots:

private:
    QVBoxLayout* layout;
};

#endif // HAPPYGROUPWIDGET_H
