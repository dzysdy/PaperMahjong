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

void WorkDesk::moveToCardGroupArea(QList<PaperCard *> cards)
{
    HappyGroupWidget* hg = new HappyGroupWidget();
    hg->setCards(cards);
    leftLayout->addWidget(hg);
}

void WorkDesk::onOperatBtnClicked()
{
    if (player->getStep() == 2) {
        otherPlayersCard = nullptr;
    }
    QPushButton* button = static_cast<QPushButton*>(sender());
    QString name = button->text();
    if (name == "liaoxi") {
        if (player->makeHappyGroup(cardsWidget->getSelectedCards())) {
            moveToCardGroupArea(cardsWidget->takeSelectedCards());
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
                emit updateDrawedArea(cardsWidget->takeSelectedCards().first());
            }
        }
        else {
            QMessageBox::information(NULL, "Warning", "Please select a card first.", QMessageBox::Ok, QMessageBox::Ok);
        }
    }
    else if (name == "chi") {
        QList<PaperCard *> cards = cardsWidget->getSelectedCards();
        if (player->eat(cards , otherPlayersCard)){
            cardsWidget->takeSelectedCards();
            cards.push_back(otherPlayersCard);
            moveToCardGroupArea(cards);
        }
    }
    else if (name == "peng") {
        QList<PaperCard *> cards = cardsWidget->getSelectedCards();
        if (player->doubleEat(cards, otherPlayersCard)){
            cardsWidget->takeSelectedCards();
            cards.push_back(otherPlayersCard);
            moveToCardGroupArea(cards);
        }
    }
    else if (name == "ding") {
        QList<PaperCard *> cards = cardsWidget->getSelectedCards();
        if (player->singleEat(cards.first(), otherPlayersCard)){
            cardsWidget->takeSelectedCards();
            cards.push_back(otherPlayersCard);
            moveToCardGroupArea(cards);
        }
    }
    else if (name == "hu") {
        if (player->complete(otherPlayersCard)){
            QMessageBox::information(NULL, "Congradulations!", "You Win! 200.", QMessageBox::Ok, QMessageBox::Ok);
        }
    }
    else if (name == "guoxi") {
        player->attachHappyGroup(cardsWidget->getSelectedCards().first());
    }
    else if (name == "ok") {
        player->makeHappyGroupOk();
    }
}

