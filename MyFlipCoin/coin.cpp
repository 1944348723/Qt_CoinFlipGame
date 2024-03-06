#include "coin.h"

#include <QMessageBox>

//Coin::Coin(QWidget *parent)
//    : QWidget{parent}
//{

//}

int Coin::flippingCount = 0;    // 静态成员变量要在类外初始化

Coin::Coin(QString img)
{
    // 设置初始状态图
    QPixmap pix;
    bool ret = pix.load(img);
    if (!ret)
    {
        QMessageBox::critical(this, "错误", "金币图片加载失败");
        return;
    }
    setFixedSize(pix.width(), pix.height());
    setStyleSheet("QPushButton{border:0px;}");
    setIcon(pix);
    setIconSize(QSize(width(), height()));

    // 连接定时器timeout和Coin切换至下一张图
    connect(&timer, &QTimer::timeout, this, &Coin::flipStep);
}

void Coin::flip()
{
    isFront = !isFront;
    ++flippingCount;
    timer.start(30);
}

void Coin::flipStep()
{
    // 此时isFront已经取反了，表示正在向什么方向翻转
    QString img;
    if (!isFront)
    {
        img = QString(":/res/Coin000%1.png").arg(++cur);
    }
    else
    {
        img = QString(":/res/Coin000%1.png").arg(--cur);
    }

    QPixmap pix;
    bool ret = pix.load(img);
    if (!ret)
    {
        QMessageBox::critical(this, "错误", "金币翻转图片加载失败");
        timer.stop();
        return;
    }
    setIcon(pix);

    // 翻转完成
    if ((cur == min) || (cur == max))
    {
        timer.stop();
        --flippingCount;
    }
}
