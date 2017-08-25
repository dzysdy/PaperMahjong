#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QLabel>
#include "Player.h"

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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void updateDrawedCard(PaperCard *card);

private slots:
    void on_startBtn_clicked();
    void onUpdateDrawedArea(PaperCard *card);

private:
    void initail();

    Ui::MainWindow *ui;
    PaperMahjong* mahjong;
    MahjongJudgment* judgment;
    Player* player1;
    Player* player2;
    QLabel* drawedCardContainer;
};

#endif // MAINWINDOW_H
