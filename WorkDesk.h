#ifndef WORKDESK_H
#define WORKDESK_H
#include "Controller.h"

class WorkDesk : public Controller
{
public:
    WorkDesk(Player* p, QObject *parent = 0);

    virtual void showBtnWidget(bool show);

public slots:
    void onOperatBtnClicked();

private:
    void initailButtons();
    void showButtons(QList<PlayerOperation> operations);
    void showButtonsOnly(QList<PlayerOperation> operations);
    void hideAllButtons();

    QMap<QString, QPushButton*> buttons;
};

#endif // WORKDESK_H
