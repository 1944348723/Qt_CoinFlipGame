#include "mainscene.h"
#include <QMessageBox>
#include <QPainter>
#include <QDebug>
#include <QSound>
#include "mypushbutton.h"

MainScene::MainScene(QWidget *parent)
    : QWidget{parent}
{
    setFixedSize(320,566);

    // 创建开始按钮
    MyPushButton * startButton = new MyPushButton(":/res/MenuSceneStartButton.png");
    startButton->setParent(this);
    // 移到适当位置
    startButton->move((width() - startButton->width()) * 0.5, height() * 0.7);
    // 设置点击音效、动画、释放信号
    QSound * clickedSound = new QSound(":/res/TapButtonSound.wav", this);
    connect(startButton, &QPushButton::clicked, this, [=](){
        qDebug() << "点击了开始按钮";
        clickedSound->play();
        startButton->bounceAnim(10);
        emit startButtonClicked();
    });
}

void MainScene::paintEvent(QPaintEvent * event)
{
    // 绘制背景图
    QPixmap pix;
    bool ret = pix.load(":/res/MenuSceneBg.png");
    if (!ret)
    {
        QMessageBox::critical(this, "错误", "主场景背景图加载失败");
        return;
    }

    QPainter painter(this);
    painter.drawPixmap(0, 0, width(), height(), pix);
}
