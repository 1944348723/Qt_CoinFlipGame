#include "coin.h"
#include "levelmap.h"
#include "playscene.h"

#include <QPainter>
#include <QDebug>
#include <QMenuBar>
#include <QLabel>
#include <QPropertyAnimation>
#include "mypushbutton.h"
#include <QTimer>
#include <QSound>

PlayScene::PlayScene(int _level, QWidget *parent)
    : QMainWindow{parent}
{
    level = _level;
    win = false;

    // 窗口设置
    setFixedSize(320, 588);
    setWindowIcon(QIcon(":/res/Coin0001.png"));
    setWindowTitle("游戏中");

    // 菜单栏设置
    QMenuBar * menuBar = new QMenuBar(this);
    setMenuBar(menuBar);
    QMenu * startMenu = menuBar->addMenu("开始");
    QAction * exitAction = startMenu->addAction("退出");
    // 绑定退出按钮和操作
    connect(exitAction, &QAction::triggered, this, [=](){
        this->close();
    });

    // 初始化并播放游戏中音效
    QSound * playSound = new QSound(":/res/myDouDZ.wav", this);
    playSound->setLoops(-1);
    playSound->play();

    // 初始化胜利音效
    QSound * winSound = new QSound(":/res/LevelWinSound.wav", this);

    // 初始化硬币翻转音效
    QSound * flipSound = new QSound(":/res/ConFlipSound.wav", this);

    // 返回按钮
    MyPushButton * backButton = new MyPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    backButton->setParent(this);
    backButton->move(width() - backButton->width(), height() - backButton->height());
    // 初始化反回按钮点击音效
    QSound * backSound = new QSound(":/res/BackButtonSound.wav", this);

    // 按下返回选择关卡场景
    connect(backButton, &MyPushButton::clicked, this, [=](){
        qDebug() << "游戏场景中点击了back";
        backSound->play();
        QTimer::singleShot(300, this, [=](){
            emit backButtonClicked();
        });
    });

    // 左下角显示当前关卡
    QLabel * levelLabel = new QLabel(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    levelLabel->setFont(font);
    QString str = QString("Level: %1").arg(level);
    levelLabel->setText(str);
    levelLabel->setGeometry(30, height() - 50, 120, 50);

    // 初始化胜利标签
    QPixmap pix;
    pix.load(":/res/LevelCompletedDialogBg.png");
    QLabel * winLabel = new QLabel;
    winLabel->setParent(this);
    winLabel->setPixmap(pix);
    winLabel->setGeometry(0, 0, pix.width(), pix.height());
    winLabel->move((width() - winLabel->width()) * 0.5, -winLabel->height());

    // 初始化关卡图
    LevelMap levelMap;
    levelArray = levelMap.getLevel(level);
    // 游戏操作区域
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            // 金币背景
            QPixmap pix(":/res/BoardNode.png");
            QLabel * label = new QLabel(this);
            label->setPixmap(pix);
            label->setGeometry(0, 0, pix.width(), pix.height());
            label->move(57 + i * 50, 200 + j * 50);

            Coin * coin = nullptr;
            // 金币
            if (levelArray[i][j] == 1)
            {
                coin = new Coin(":/res/Coin0001.png");
                coin->setParent(this);
                coin->isFront = true;
                coin->cur = 1;
            }
            else
            {
                coin = new Coin(":/res/Coin0008.png");
                coin->setParent(this);
                coin->isFront = false;
                coin->cur = 8;
            }
            coin->move(59 + i * 50, 204 + j * 50);
            coins[i + 1][j + 1] = coin;
            coin->row = i + 1;
            coin->column = j + 1;
            // 连接点击信号和翻转当前金币与相邻金币
            // 需要检测当前是否有金币正在翻转
            // 如果有则此次点击不触发翻转
            connect(coin, &QPushButton::clicked, this, [=](){
                qDebug() << "点击了金币";

                qDebug() << "filppingCound" << Coin::flippingCount;
                // 检查是否有金币在翻转和是否已经赢了
                if (Coin::flippingCount)
                {
                    qDebug() << "别点这么快";
                    return;
                }

                if (win)
                {
                    qDebug() << "已经赢了，别点了";
                    return;
                }

                // 翻转前先默认为赢，后续检测出非正金币再改为false
                win = true;

                // 执行翻转操作

                // 翻转音效
                flipSound->play();
                // 翻转点击金币
                coin->flip();

                QTimer::singleShot(200, this, [=](){
                    // 翻转相邻金币
                    int dx[4] = {-1, 0, 1, 0};
                    int dy[4] = {0, 1, 0, -1};
                    for (int index = 0; index < 4; ++index)
                    {
                        int newRow = coin->row + dx[index];
                        int newColumn = coin->column + dy[index];
                        // 无效区域
                        if ((newRow < 1) || (newRow > 4) || (newColumn < 1) || (newColumn > 4))
                            continue;

                        coins[newRow][newColumn]->flip();
                    }

                    // 检测是否胜利
                    for (int i = 0; i < 4; ++i)
                    {
                        for (int j = 0; j < 4; ++j)
                        {
                            if (!(coins[i + 1][j + 1]->isFront))
                            {
                                qDebug() << "还未胜利";
                                win = false;
                                return;
                            }
                        }
                    }

                    qDebug() << "胜利了";
                    // 胜利音效
                    winSound->play();
                    // 停止游戏中音效
                    playSound->stop();

                    // 胜利动画
                    QPropertyAnimation * propertyAnimation = new QPropertyAnimation(winLabel, "geometry");
                    propertyAnimation->setDuration(1000);
                    propertyAnimation->setEasingCurve(QEasingCurve::OutBounce);
                    propertyAnimation->setStartValue(QRect(winLabel->x(), winLabel->y(),
                                                           winLabel->width(), winLabel->height()));
                    propertyAnimation->setEndValue(QRect(winLabel->x(), winLabel->y() + 114,
                                                         winLabel->width(), winLabel->height()));
                    propertyAnimation->start();
                });
            });
        }
    }
}

void PlayScene::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    // 绘制背景图
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, width(), height(), pix);
}
