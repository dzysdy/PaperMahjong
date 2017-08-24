#include "Controller.h"
#include "CardsWidget.h"
#include "CardContainer.h"
#include "HappyGroupWidget.h"
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

Controller::Controller(QObject *parent) : QObject(parent)
{
    desk = new QWidget();
    mainLayout = new QHBoxLayout();
    desk->setLayout(mainLayout);

    leftLayout = new QHBoxLayout();
    mainLayout->addLayout(leftLayout, 6);

    midLayout = new QVBoxLayout();
    mainLayout->addLayout(midLayout, 17);
    btnsLayout = new QHBoxLayout();
    cardsLayout = new QHBoxLayout();

    cardsWidget = new CardsWidget();
    cardsWidget->initail(17);
    cardsWidget->setMinimumWidth(400);
    cardsLayout->addWidget(cardsWidget);
    cardsLayout->addStretch(1);

    midLayout->addLayout(btnsLayout);
    midLayout->addLayout(cardsLayout);

    rightLayout = new QVBoxLayout();
    timeRecoder = new QLCDNumber();
    rightLayout->addWidget(timer);
}

QWidget *Controller::widget()
{
    return desk;
}

CardsWidget *Controller::getCardsWidget() const
{
    return cardsWidget;
}

void Controller::initailButtons()
{
    for (int i = 0; i < BUTTON_NUM; i++) {
        QString name = gButtons[i];
        QPushButton* button = new QPushButton(name);
        btnsLayout->addWidget(button);
        buttons.insert(name, button);
        button->hide();
        connect(button, &QPushButton::clicked, this, &Controller::onOperatBtnClicked);
    }
}

void Controller::connectSignals()
{
    connect(judgment, &MahjongJudgment::updateTime, this, &Controller::onUpdateTime);
    connect(judgment, &MahjongJudgment::makeHappyGroup, this, &Controller::onMakeHappyGroup);
    connect(judgment, &MahjongJudgment::firstStep, this, &Controller::onFirstStep);
    connect(judgment, &MahjongJudgment::secondStep, this, &Controller::onSecondStep);
}

void Controller::showButtons(QList<PlayerOperation> operations)
{
    hideAllButtons();
    for (PlayerOperation operation : operations) {
        QString name = gButtons[operation - 1];
        buttons[name]->show();
    }
    buttons["ok"]->show();
}

void Controller::hideAllButtons()
{
    for (QPushButton* button : buttons) {
        button->hide();
    }
}

void Controller::updateDrawedArea(CardContainer *container)
{
    if (drawedCardContainer) {
        drawedCardContainer->setParent(nullptr);
        //ui->drawedCardArea->removeWidget(drawedCardContainer);
        delete drawedCardContainer;
    }
    drawedCardContainer = container;
    //ui->drawedCardArea->addWidget(drawedCardContainer);
}

void Controller::onUpdateTime(unsigned sec)
{
    timeRecoder->display((int)sec);
}

void Controller::onMakeHappyGroup()
{
    cardsWidget->setMode(CardsWidget::CSM_LIAOXI);
    hideAllButtons();
    buttons["liaoxi"]->show();
}

void Controller::onFirstStep(QList<PlayerOperation> operations)
{
    cardsWidget->setMode(CardsWidget::CSM_CHI);
    showButtons(operations);
}

void Controller::onSecondStep(QList<PlayerOperation> operations)
{
    cardsWidget->setMode(CardsWidget::CSM_CUSTOM);
    showButtons(operations);
}

void Controller::onOperatBtnClicked()
{
    QPushButton* button = static_cast<QPushButton*>(sender());
    QString name = button->text();
    if (name == "liaoxi") {
        if (player1->makeHappyGroup(cardsWidget->getSelectedCards())) {
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
        PaperCard* card = player1->drawsCard();
        if (card) {
            cardsWidget->addCard(card);
        }
    }
    else if (name == "da") {
        QList<PaperCard *> cards = cardsWidget->getSelectedCards();
        if (cards.size() == 1) {
            if (player1->removeCard(cards.first())) {
                QList<CardContainer*> containers = cardsWidget->takeSelectedCards();
                updateDrawedArea(containers.first());
            }
        }
        else {
            QMessageBox::information(NULL, "Warning", "Please select a card first.", QMessageBox::Ok, QMessageBox::Ok);
        }
    }
}
