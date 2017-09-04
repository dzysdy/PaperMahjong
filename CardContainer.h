#ifndef CARDCONTAINER_H
#define CARDCONTAINER_H
#include <QLabel>

class PaperCard;
class CardContainer : public QLabel
{
    Q_OBJECT

public:
    CardContainer(QWidget *parent=Q_NULLPTR);
    CardContainer(const QString &text, QWidget *parent=Q_NULLPTR);

    void setCard(PaperCard* card, bool faceUp = true);
    PaperCard *getPaperCard() const;

protected:
    void mousePressEvent(QMouseEvent *event);

signals:
    void clicked();

private:
    void setImage(const QImage& image);
    void setSelected(bool b);
    void updateView();

    PaperCard* paperCard;
    bool selected;
};

#endif // CARDCONTAINER_H
