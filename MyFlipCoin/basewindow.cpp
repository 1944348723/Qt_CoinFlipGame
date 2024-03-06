#include "basewindow.h"
#include "ui_basewindow.h"
#include <QMenuBar>
#include <QTimer>

BaseWindow::BaseWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BaseWindow)
{
    ui->setupUi(this);

    initWindow();

    // 一开始默认进入主场景
    mainScene = new MainScene(this);
    setCentralWidget(mainScene);
    setWindowTitle("MyFlipCoin");

    // 提前加载选择关卡场景
    levelSelectionScene = new LevelSelectionScene;
    // 连接主场景中的开始按钮和进入选择关卡场景
    connect(mainScene, &MainScene::startButtonClicked, this, [=](){
        QTimer::singleShot(500, this, [=](){
            takeCentralWidget();
            setCentralWidget(levelSelectionScene);
            setWindowTitle("选择关卡");
        });
    });

    // 连接选择关卡场景中的back按钮和返回主场景
    connect(levelSelectionScene, &LevelSelectionScene::backButtonClicked, this, [=](){
        QTimer::singleShot(300, this, [=](){
            takeCentralWidget();
            setCentralWidget(mainScene);
            setWindowTitle("MyFlipCoin");
        });
    });

    // 提前加载游戏场景（不包含金币）
    playScene = new PlayScene;
    // 连接选择关卡按钮点击和进入游戏场景
    connect(levelSelectionScene, &LevelSelectionScene::levelButtonClicked, this, [=](int levelNum){
        QTimer::singleShot(300, this, [=](){
            takeCentralWidget();
            playScene->initLevel(levelNum);  // 初始化关卡金币
            setCentralWidget(playScene);
            setWindowTitle("游戏中");
        });
    });

    // 连接游戏场景返回按钮和返回操作
    connect(playScene, &PlayScene::backButtonClicked, this, [=](){
        QTimer::singleShot(300, this, [=](){
            takeCentralWidget();
            playScene->clearLevel();    // 清理金币
            setCentralWidget(levelSelectionScene);
            setWindowTitle("选择关卡");
        });
    });
}

BaseWindow::~BaseWindow()
{
    delete ui;
}

void BaseWindow::initWindow()
{
    // 窗口设置
    setFixedSize(320, 588);
    setWindowIcon(QIcon(":/res/Coin0001.png"));

    // 菜单栏
    QMenuBar * menuBar = new QMenuBar(this);
    setMenuBar(menuBar);
    QMenu * startMenu = menuBar->addMenu("开始");
    QAction * exitAction = startMenu->addAction("退出");
    // 连接点击退出和退出操作
    connect(exitAction, &QAction::triggered, this, &QMainWindow::close);
}
