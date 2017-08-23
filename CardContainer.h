#ifndef CARDCONTAINER_H
#define CARDCONTAINER_H
#include <QLabel>

class CardContainer : public QLabel
{
    Q_OBJECT

public:
    CardContainer(QWidget *parent=Q_NULLPTR);
    CardContainer(const QString &text, QWidget *parent=Q_NULLPTR);

    void setImage(const QImage& image);
    void moveUpBack(bool up);

protected:
    void mousePressEvent(QMouseEvent *event);

signals:
    void clicked();

private:
    void moveUp();
    void moveBack();

    bool isDown;
};

#endif // CARDCONTAINER_H
