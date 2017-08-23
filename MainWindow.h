#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>

namespace Ui {
class MainWindow;
}
class MahjongJudgment;
class PaperMahjong;
class PaperCard;
class Player;
class QPushButton;
class CardsWidget;
class CardContainer;
enum PlayerOperation;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_startBtn_clicked();
    void onOperatBtnClicked();
    void onUpdateTime(unsigned sec);
    void onMakeHappyGroup();
    void onFirstStep(QList<PlayerOperation> operations);
    void onSecondStep(QList<PlayerOperation> operations);

private:
    void initail();
    void initailButtons();
    void connectSignals();
    void showButtons(QList<PlayerOperation> operations);
    void hideAllButtons();
    void updateDrawedArea(CardContainer* container);

    Ui::MainWindow *ui;
    PaperMahjong* mahjong;
    MahjongJudgment* judgment;
    Player* player1;
    Player* player2;
    QMap<QString, QPushButton*> buttons;
    CardsWidget* cardsWidget;
    CardContainer* drawedCardContainer;
};

#endif // MAINWINDOW_H
