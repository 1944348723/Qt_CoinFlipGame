#include "mypushbutton.h"
#include <QDebug>
#include <QPropertyAnimation>
#include <QMouseEvent>

//MyPushButton::MyPushButton(QPushButton *parent)
//    : QPushButton{parent}
//{

//}

MyPushButton::MyPushButton(QString _normalImg, QString _pressedImg):
    normalImg(_normalImg),
    pressedImg(_pressedImg)
{
    // 检测按钮正常情况下的图片路径是否有效
    QPixmap pix;
    bool ret = pix.load(normalImg);
    if (!ret)
    {
        qDebug() << "开始按钮图片加载失败";
        return;
    }

    // 将按钮设置成图片大小
    this->setFixedSize(pix.width(), pix.height());
    // 设置为不规则图形
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(), pix.height()));
}

void MyPushButton::mousePressEvent(QMouseEvent * event)
{
    // 如果按下状态图片路径非空，则检查路径是否有效
    // 有效则切换为按下状态图片，否则不改变
    // 如果路径无效直接跳过
    if (!pressedImg.isEmpty())
    {
        // 检测按钮按下情况下的图片路径是否有效
        QPixmap pix;
        bool ret = pix.load(pressedImg);
        if (!ret)   // 无效
        {
            qDebug() << "开始按钮图片加载失败";
        }
        else
        {
            this->setIcon(pix);
            this->setIconSize(QSize(pix.width(), pix.height()));
        }
    }

    // 交给父类处理
    QPushButton::mousePressEvent(event);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent * event)
{
    // 如果按下状态图片路径非空，则检查路径是否有效
    // 无效则跳过
    // 有效则切换回正常状态下的图片
    if (!pressedImg.isEmpty())
    {
        // 检测按钮正常情况下的图片路径是否有效
        QPixmap pix;
        bool ret = pix.load(normalImg);
        if (!ret)
        {
            qDebug() << "开始按钮图片加载失败";
        }
        else
        {
            this->setIcon(pix);
            this->setIconSize(QSize(pix.width(), pix.height()));
        }
    }

    // 交给父类处理
    QPushButton::mouseReleaseEvent(event);
}

void MyPushButton::moveDownAnim(int dy)
{
    QPropertyAnimation * animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(500);
    animation->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
    animation->setEndValue(QRect(this->x(), this->y() + dy, this->width(), this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);

    animation->start();
}

void MyPushButton::moveUpAnim(int dy)
{
    QPropertyAnimation * animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(500);
    animation->setStartValue(QRect(this->x(), this->y() + dy, this->width(), this->height()));
    animation->setEndValue(QRect(this->x(), this->y(), this->width(), this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);

    animation->start();
}
