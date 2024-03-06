#include "levelmap.h"
#include "playscene.h"

#include <QLabel>
#include <QMessageBox>
#include <QPainter>
#include <QPropertyAnimation>
#include "mypushbutton.h"
#include <QSound>

PlayScene::PlayScene(QWidget *parent)
    : QWidget{parent}
{
    setFixedSize(320, 566);

    initBackButton();
    // 初始化左下角关卡标签
    levelLabel = new QLabel(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    levelLabel->setFont(font);
    levelLabel->setGeometry(30, height() - 50, 120, 50);


    // 初始化金币背景
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            coinsBg[i][j] = new QLabel(this);
            coinsBg[i][j]->setPixmap(QPixmap(":/res/BoardNode.png"));
            coinsBg[i][j]->move(57 + i * 50, 200 + j * 50);
        }
    }

    // 初始化胜利标签
    QPixmap pix;
    pix.load(":/res/LevelCompletedDialogBg.png");
    winLabel = new QLabel;
    winLabel->setParent(this);
    winLabel->setPixmap(pix);
    winLabel->setFixedSize(QSize(pix.width(), pix.height()));
    winLabel->setGeometry(0, 0, pix.width(), pix.height());
    winLabel->move((width() - winLabel->width()) * 0.5, -winLabel->height());

    // 背景音乐
    bgm = new QSound(":/res/myDouDZ.wav", this);
    bgm->setLoops(-1);
    // 翻硬币音效
    flipSound = new QSound(":/res/ConFlipSound.wav", this);
    // 胜利音效
    winSound = new QSound(":/res/LevelWinSound.wav", this);
}

void PlayScene::initBackButton()
{
    MyPushButton * backButton = new MyPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    backButton->setParent(this);
    backButton->move(width() - backButton->width(), height() - backButton->height());
    // 设置点击音效和释放信号
    QSound * backClickedSound = new QSound(":/res/BackButtonSound.wav", this);
    connect(backButton, &QPushButton::clicked, this, [=](){
        backClickedSound->play();
        emit backButtonClicked();
    });
}

void PlayScene::initLevel(int levelNum)
{
    win = false;
    levelLabel->setText(QString("Level:%1").arg(levelNum));
    bgm->play();

    winLabel->setGeometry(0, 0, winLabel->width(), winLabel->height());
    winLabel->move((width() - winLabel->width()) * 0.5, -winLabel->height());

    LevelMap levelMap;
    QVector<QVector<int>> map = levelMap.getLevel(levelNum);
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            // 创建金币
            if (map[i][j])  // 正
            {
                coins[i][j] = new Coin(":/res/Coin0001.png");
                coins[i][j]->isFront = true;
                coins[i][j]->cur = 1;
            }
            else    // 反
            {
                coins[i][j] = new Coin(":/res/Coin0008.png");
                coins[i][j]->isFront = false;
                coins[i][j]->cur = 8;
            }
            coins[i][j]->setParent(coinsBg[i][j]);
            coins[i][j]->move(2, 3);

            // 连接点击和翻金币动画及音效
            connect(coins[i][j], &Coin::clicked, this, [=](){
                flipCoins(i, j);
            });
        }
    }
}

void PlayScene::clearLevel()
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            delete coins[i][j];
        }
    }
    bgm->stop();
}

bool PlayScene::flipCoins(int row, int column)
{
    // 如果有正在翻转的硬币或已经赢了就取消操作
    if (Coin::flippingCount || win)
    {
        return false;
    }

    // 翻硬币前win先默认为true
    // 翻完后如果发现非正硬币就再改为false
    win = true;

    flipSound->play();
    // 翻转被点击的硬币
    coins[row][column]->flip();

    // 翻转被点击的硬币的上、右、下、左中有效位置的硬币
    QTimer::singleShot(100, this, [=](){
        int dx[4] = {-1, 0, 1, 0};
        int dy[4] = {0, 1, 0, -1};
        for (int i = 0; i < 4; ++i)
        {
            int newRow = row + dx[i];
            int newColumn = column + dy[i];

            // 跳过无效位置
            if ((newRow < 0) || (newRow > 3) || (newColumn < 0) || (newColumn > 3))
                continue;

            coins[newRow][newColumn]->flip();
        }

        checkWin();
    });

    return true;
}

void PlayScene::checkWin()
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (!coins[i][j]->isFront)
            {
                win = false;
                return;
            }
        }
    }

    // 胜利音效
    winSound->play();
    // 停止游戏中音效
    bgm->stop();

    // 胜利动画
    QPropertyAnimation * propertyAnimation = new QPropertyAnimation(winLabel, "geometry");
    propertyAnimation->setDuration(1000);
    propertyAnimation->setEasingCurve(QEasingCurve::OutBounce);
    propertyAnimation->setStartValue(QRect(winLabel->x(), winLabel->y(),
                                           winLabel->width(), winLabel->height()));
    propertyAnimation->setEndValue(QRect(winLabel->x(), winLabel->y() + 114,
                                         winLabel->width(), winLabel->height()));
    propertyAnimation->start();
}
void PlayScene::paintEvent(QPaintEvent * event)
{
    // 绘制背景图
    QPixmap pix;
    bool ret = pix.load(":/res/PlayLevelSceneBg.png");
    if (!ret)
    {
        QMessageBox::critical(this, "错误", "游玩场景中背景图加载错误");
        return;
    }

    QPainter painter(this);
    painter.drawPixmap(0, 0, width(), height(), pix);
}
