#include "WorkDesk.h"
#include "CardView.h"
#include "CardContainer.h"
#include "HappyGroupWidget.h"
#include "MahjongJudgment.h"
#include <QMessageBox>

const int BUTTON_NUM = 9;
const QString gButtons[BUTTON_NUM] = {
    QObject::tr("chi"),
    QObject::tr("peng"),
    QObject::tr("ding"),
    QObject::tr("hu"),
    QObject::tr("da"),
    QObject::tr("mo"),
    QObject::tr("liaoxi"),
    QObject::tr("guoxi"),
    QObject::tr("ok")
};

WorkDesk::WorkDesk(Player *p, QObject *parent):
    Controller(p, parent)
{
    initailButtons();
}

void WorkDesk::showBtnWidget(bool show)
{
    showBtn = show;
    if (!showBtn)
        hideAllButtons();
}

void WorkDesk::initailButtons()
{
    showBtn = true;
    btnsLayout->addStretch(1);
    for (int i = 0; i < BUTTON_NUM; i++) {
        QString name = gButtons[i];
        QPushButton* button = new QPushButton(name);
        button->setMinimumWidth(30);
        btnsLayout->addWidget(button);
        buttons.insert(name, button);
        button->hide();
        connect(button, &QPushButton::clicked, this, &WorkDesk::onOperatBtnClicked);
    }
    btnsLayout->addStretch(1);
}

void WorkDesk::showButtons(QList<PlayerOperation> operations)
{
    if (!showBtn)
        return;
    for (PlayerOperation operation : operations) {
        QString name = gButtons[operation - 1];
        buttons[name]->show();
    }
}

void WorkDesk::showButtonsOnly(QList<PlayerOperation> operations)
{
    hideAllButtons();
    showButtons(operations);
}

void WorkDesk::hideAllButtons()
{
    for (QPushButton* button : buttons) {
        button->hide();
    }
}

void WorkDesk::onOperatBtnClicked()
{
    if (player->getStep() == 2) {
        otherPlayersCard = nullptr;
    }
    QPushButton* button = static_cast<QPushButton*>(sender());
    QString name = button->text();
    if (name == tr("liaoxi")) {
        if (!player->makeHappyGroup()) {
            QMessageBox::information(NULL, tr("Warning"), tr("Not a Hapyy Group."), QMessageBox::Ok, QMessageBox::Ok);
        }
            //moveToCardGroupArea(cardView->takeSelectedCards());
    }
    else if (name == tr("mo")) {
        player->drawsCard();
    }
    else if (name == tr("da")) {
        if (!player->discard()) {
            QMessageBox::information(NULL, tr("Warning"), tr("Please select a card first."), QMessageBox::Ok, QMessageBox::Ok);
        }
//        emit updateDrawedArea(cardView->takeSelectedCards().first());
    }
    else if (name == tr("chi")) {
        if (!player->eat(otherPlayersCard)){
            QMessageBox::information(NULL, tr("Warning"), tr("Please select two cards first."), QMessageBox::Ok, QMessageBox::Ok);
        }
            //moveToCardGroupArea(cards);
    }
    else if (name == tr("peng")) {
        if (!player->doubleEat(otherPlayersCard)){
            QMessageBox::information(NULL, tr("Warning"), tr("Please select two cards first."), QMessageBox::Ok, QMessageBox::Ok);
        }
    }
    else if (name == tr("ding")) {
        if (!player->singleEat(otherPlayersCard)){
            QMessageBox::information(NULL, tr("Warning"), tr("Please select a card first."), QMessageBox::Ok, QMessageBox::Ok);
        }
            //moveToCardGroupArea(cards);
    }
    else if (name == tr("hu")) {
        if (player->complete(otherPlayersCard)){
            QMessageBox::information(NULL, tr("Congradulations!"), tr("You Win! 200."), QMessageBox::Ok, QMessageBox::Ok);
        }
    }
    else if (name == tr("guoxi")) {
        player->attachHappyGroup();
    }
    else if (name == tr("ok")) {
        player->makeHappyGroupOk();
    }
}

