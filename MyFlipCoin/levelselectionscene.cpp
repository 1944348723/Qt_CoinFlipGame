#include "levelselectionscene.h"
#include <QLabel>
#include <QMessageBox>
#include <QPainter>
#include <QSound>
#include "mypushbutton.h"

LevelSelectionScene::LevelSelectionScene(QWidget *parent)
    : QWidget{parent}
{
    setFixedSize(320, 566);
    initBackButton();

    QSound * levelClickedSound = new QSound(":/res/TapButtonSound.wav", this);
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            // 关卡数按钮
            MyPushButton * levelButton = new MyPushButton(":/res/LevelIcon.png");
            levelButton->setParent(this);
            // 布局
            levelButton->move(25 + j * 70, 130 + i * 70);
            // 设置点击音效和关卡跳转
            connect(levelButton, &QPushButton::clicked, this, [=](){
                levelClickedSound->play();
                emit levelButtonClicked(i * 4 + j + 1);
            });

            // 关卡数标签
            QLabel * levelLabel = new QLabel(QString::number(i * 4 + j + 1), levelButton);
            levelLabel->setFixedSize(levelButton->width(), levelButton->height());
            levelLabel->setAlignment(Qt::AlignCenter);
        }
    }
}

void LevelSelectionScene::initBackButton()
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

void LevelSelectionScene::paintEvent(QPaintEvent * event)
{
    // 绘制背景图
    QPixmap pix;
    bool ret = pix.load(":/res/OtherSceneBg.png");
    if (!ret)
    {
        QMessageBox::critical(this, "错误", "选择关卡场景背景图加载错误");
        return;
    }

    QPainter painter(this);
    painter.drawPixmap(0, 0, width(), height(), pix);

    // 绘制标题
    ret = pix.load(":/res/Title.png");
    if (!ret)
    {
        QMessageBox::critical(this, "错误", "选择关卡场景中游戏标题加载错误");
        return;
    }
    painter.drawPixmap((width() - pix.width()) * 0.5, 30, pix.width(), pix.height(), pix);
}
