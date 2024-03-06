#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPainter>
#include <QDebug>
#include "chooselevelscene.h"
#include <QTimer>
#include <QSound>

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    // 设置主场景

    // 设置大小
    setFixedSize(320, 588);
    // 设置标题图片
    setWindowIcon(QPixmap(":/res/Coin0001.png"));
    // 设置应用标题
    setWindowTitle("FlipCoin");

    // 退出游戏按钮点击实现
    connect(ui->actionExit, &QAction::triggered, this, &QMainWindow::close);

    // 开始按钮
    startButton = new MyPushButton(":/res/MenuSceneStartButton.png");
    startButton->setParent(this);
    startButton->move(this->width() * 0.5 - startButton->width() * 0.5, this->height() * 0.7);
    // 开始按钮点击音效
    QSound * startSound = new QSound(":/res/TapButtonSound.wav", this);

    // 创建选择关卡场景
    ChooseLevelScene * chooseLevelScene = new ChooseLevelScene(this);
    // 按下返回按钮回到主场景
    connect(chooseLevelScene, &ChooseLevelScene::backButtonPressed, this, [=](){
        chooseLevelScene->hide();
        this->show();
    });

    // 点击开始按钮后有动画效果，然后进入关卡选择场景
    connect(startButton, &QPushButton::clicked, this, [=](){
        qDebug() << "点击了开始按钮";
        // 点击音效
        startSound->play();
        startButton->moveDownAnim(10);
        startButton->moveUpAnim(10);

        // 点击后过0.4秒再进入，让开始按钮的动画完成
        QTimer::singleShot(400, this, [=](){
            this->hide();
            chooseLevelScene->show();
        });
    });
}

void MainScene::paintEvent(QPaintEvent * event)
{
    // 显示背景图片
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    // 显示游戏名
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width() * 0.5, pix.height() * 0.5);
    painter.drawPixmap(10, 30, pix.width(), pix.height(), pix);


}

MainScene::~MainScene()
{
    delete ui;
}

