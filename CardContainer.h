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

    void setCard(PaperCard* card);
    void setImage(const QImage& image);
    void moveUpBack(bool up);
    PaperCard *getPaperCard() const;

protected:
    void mousePressEvent(QMouseEvent *event);

signals:
    void clicked();

private:
    void moveUp();
    void moveBack();

    bool isDown;
    PaperCard* paperCard;
};

#endif // CARDCONTAINER_H
