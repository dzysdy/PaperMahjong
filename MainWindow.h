#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
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

private slots:
    void on_startBtn_clicked();

private:
    void initail();

    Ui::MainWindow *ui;
    PaperMahjong* mahjong;
    MahjongJudgment* judgment;
    Player* player1;
    Player* player2;
};

#endif // MAINWINDOW_H
