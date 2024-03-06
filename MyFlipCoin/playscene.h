#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QWidget>
#include <QLabel>
#include <QSound>
#include "coin.h"

class PlayScene : public QWidget
{
    Q_OBJECT
public:
    explicit PlayScene(QWidget *parent = nullptr);
    virtual void paintEvent(QPaintEvent * event) override;
    void initBackButton();
    // 初始化关卡左下角标签和游戏区域金币
    void initLevel(int levelNum);
    // 清除左下角标签和游戏区域金币
    void clearLevel();
    bool flipCoins(int row, int column);
    // 检查是否赢了
    void checkWin();
signals:
    void backButtonClicked();
private:
    QSound * bgm;
    QSound * flipSound;
    QSound * winSound;
    QLabel * levelLabel;    // 左下角关卡标签
    QLabel * winLabel;
    QLabel * coinsBg[4][4];
    Coin * coins[4][4];
    bool win = false;
};

#endif // PLAYSCENE_H
