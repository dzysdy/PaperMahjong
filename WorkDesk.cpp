#include "WorkDesk.h"
#include "CardsWidget.h"
#include "CardContainer.h"
#include "HappyGroupWidget.h"
#include "MahjongJudgment.h"
#include <QMessageBox>

const int BUTTON_NUM = 9;
const QString gButtons[BUTTON_NUM] = {
    "chi",
    "peng",
    "ding",
    "hu",
    "da",
    "mo",
    "liaoxi",
    "guoxi",
    "ok",
};

WorkDesk::WorkDesk(Player *p, QObject *parent):
    Controller(p, parent)
{
    initailButtons();
}

void WorkDesk::showBtnWidget(bool show)
{
//    for (QPushButton* button: buttons) {
//        if (show)
//            button->show();
//        else
//            button->hide();
//    }
}

void WorkDesk::initailButtons()
{
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
    QPushButton* button = static_cast<QPushButton*>(sender());
    QString name = button->text();
    if (name == "liaoxi") {
        if (player->makeHappyGroup(cardsWidget->getSelectedCards())) {
            QList<CardContainer*> containers = cardsWidget->takeSelectedCards();
            HappyGroupWidget* hg = new HappyGroupWidget();
            hg->setCardContainers(containers);
            leftLayout->addWidget(hg);
        }
        else {
            QMessageBox::information(NULL, "Warning", "Not a Hapyy Group.", QMessageBox::Ok, QMessageBox::Ok);
        }
    }
    else if (name == "mo") {
        PaperCard* card = player->drawsCard();
        if (card) {
            cardsWidget->addCard(card);
        }
    }
    else if (name == "da") {
        QList<PaperCard *> cards = cardsWidget->getSelectedCards();
        if (cards.size() == 1) {
            if (player->removeCard(cards.first())) {
                QList<CardContainer*> containers = cardsWidget->takeSelectedCards();
                emit updateDrawedArea(containers.first());
            }
        }
        else {
            QMessageBox::information(NULL, "Warning", "Please select a card first.", QMessageBox::Ok, QMessageBox::Ok);
        }
    }
    else if (name == "ok") {
        player->makeHappyGroupOk();
    }
}

