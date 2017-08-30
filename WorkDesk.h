#ifndef WORKDESK_H
#define WORKDESK_H
#include "Controller.h"

class WorkDesk : public Controller
{
    Q_OBJECT

public:
    explicit WorkDesk(Player* p, QObject *parent = 0);
    virtual ~WorkDesk();

    virtual void setMyTurn(bool show);
    virtual void handleOperations(QList<PlayerOperation> operations);

public slots:
    void onOperatBtnClicked();

private:
    void initailButtons();
    void showButtons(QList<PlayerOperation> operations);
    void hideAllButtons();
    void moveToCardGroupArea(QList<PaperCard *> cards);

    QMap<QString, QPushButton*> buttons;
    bool showBtn;
};

#endif // WORKDESK_H
