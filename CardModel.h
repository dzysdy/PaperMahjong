#ifndef CARDMODEL_H
#define CARDMODEL_H

#include <QObject>

class PaperCard;
class CardModel: public QObject {
    Q_OBJECT

public:
    CardModel(QObject* parent = nullptr);
    ~CardModel();

    void update();
    const QList<PaperCard *> &data();
    void setData(const QList<PaperCard*>& data);

    bool getFaceUp() const;
    void setFaceUp(bool value);

signals:
    void updated();

private:
    friend class Player;

    QList<PaperCard*> cards;
    bool faceUp;
};

#endif // CARDMODEL_H
