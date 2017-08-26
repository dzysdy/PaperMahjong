#ifndef CARDMODEL_H
#define CARDMODEL_H

#include <QObject>

class PaperCard;
class CardModel: public QObject {
    Q_OBJECT

public:
    CardModel(QObject* parent = nullptr);

    void update();
    QList<PaperCard*> data();
    void setData(const QList<PaperCard*>& data);

signals:
    void updated();

private:
    friend class Player;

    QList<PaperCard*> cards;
};

#endif // CARDMODEL_H