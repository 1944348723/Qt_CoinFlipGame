#include "chooselevelscene.h"
#include <QMenuBar>
#include <QMenu>
#include <QPainter>
#include "mypushbutton.h"
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include "playscene.h"
#include "playscene.h"
#include <QSound>

ChooseLevelScene::ChooseLevelScene(QWidget *parent)
    : QMainWindow{parent}
{
    // 窗口设置
    setFixedSize(320, 588);
    setWindowTitle("选择关卡");
    setWindowIcon(QIcon(":/res/Coin0001.png"));

    // 菜单栏设置
    QMenuBar * menuBar = new QMenuBar(this);
    setMenuBar(menuBar);
    QMenu * startMenu = menuBar->addMenu("开始");
    QAction * exitAction = startMenu->addAction("退出");
    // 绑定退出按钮和操作
    connect(exitAction, &QAction::triggered, this, [=](){
        this->close();
    });

    // 返回按钮
    MyPushButton * backButton = new MyPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    backButton->setParent(this);
    backButton->move(this->width() - backButton->width(), this->height() - backButton->height());
    // 返回按钮音效
    QSound * backSound = new QSound(":/res/BackButtonSound.wav", this);
    // 按下返回按钮回到游戏主界面
    connect(backButton, &QPushButton::clicked, this, [=](){
        qDebug() <<  "点击了返回按钮";
        QTimer::singleShot(300, this, [=](){
            backSound->play();
            emit backButtonPressed();
        });
    });

    // 点击关卡按钮音效
    QSound * levelSound = new QSound(":/res/TapButtonSound.wav", this);
    // 关卡按钮
    for (int i = 0; i < 20; ++i)
    {
        // 创建按钮
        MyPushButton * levelButton = new MyPushButton(":/res/LevelIcon");
        levelButton->setParent(this);
        // 排版
        levelButton->move(25 + (i % 4) * 70, 130 + i / 4 * 70);
        // 点击进入响应关卡
        connect(levelButton, &MyPushButton::clicked, this, [=](){
            qDebug() << "选择了关卡" << i + 1;
            // 播放点击音效
            levelSound->play();
            // 关卡跳转
            PlayScene * playScene = new PlayScene(i + 1);
            this->hide();
            playScene->show();
            // 设置返回操作
            connect(playScene, &PlayScene::backButtonClicked, this, [=](){
                delete playScene;
                this->show();
            });
        });

        // 关卡数标签
        QLabel * levelLabel = new QLabel(levelButton);
        levelLabel->setFixedSize(levelButton->width(), levelButton->height());
        levelLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        levelLabel->setText(QString::number(i + 1));
    }

}

void ChooseLevelScene::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);

    // 绘制背景图片
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    // 绘制游戏名
    pix.load(":/res/Title.png");
    painter.drawPixmap((width() - pix.width()) * 0.5, 30, pix.width(), pix.height(), pix);
}
