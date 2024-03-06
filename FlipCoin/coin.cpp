#include "coin.h"
#include <QDebug>

//Coin::Coin(QWidget *parent)
//    : QWidget{parent}
//{

//}

int Coin::flippingCount = 0;    // 静态成员变量要在类外初始化

Coin::Coin(QString img)
{
    QPixmap pix;
    bool ret = pix.load(img);
    if (!ret)
    {
        qDebug() << "金币图片加载失败";
        return;
    }

    // 设置图标形式和大小
    setStyleSheet("QPushButton{border:0px;}");
    setFixedSize(pix.width(), pix.height());
    setIcon(pix);
    setIconSize(QSize(pix.width(), pix.height()));

    // 连接timeout和金币翻转
    connect(&timer, &QTimer::timeout, this, &Coin::flipStep);
}

void Coin::flipStep()
{
    QString img;
    // 现在是正面表示翻转前是反面
    if (isFront)
    {
        img = QString(":/res/Coin000%1.png").arg(--cur);
    }
    else
    {
        img = QString(":/res/Coin000%1.png").arg(++cur);
    }
    QPixmap pix;
    bool ret = pix.load(img);
    if (!ret)
    {
        qDebug() << "金币翻转图片加载失败";
        timer.stop();
        return;
    }

    setIcon(pix);
    qDebug() << "flippingCound" << Coin::flippingCount;
    if ((cur == min) || (cur == max))   // 翻转完毕
    {
        timer.stop();
        --Coin::flippingCount;
    }
}

void Coin::flip()
{
    // 先改标识再做翻转动画
    isFront = !isFront;
    ++Coin::flippingCount;
    timer.start(30);
}
