#include "mypushbutton.h"
#include <QPixmap>
#include <QMessageBox>
#include <QDebug>
#include <QPropertyAnimation>

//MyPushButton::MyPushButton(QWidget *parent)
//    : QWidget{parent}
//{

//}

MyPushButton::MyPushButton(QString _normalImg, QString _pressedImg)
{

    normalImg = _normalImg;
    pressedImg = _pressedImg;

    // 检测正常状态下图片路径的有效性
    QPixmap pix;
    bool ret = pix.load(normalImg);
    if (!ret)
    {
        QMessageBox::critical(this, "错误", "加载按钮失败");
        return;
    }

    // 将按钮设置成正常形态，并匹配图片大小
    setFixedSize(pix.width(), pix.height());
    setStyleSheet("QPushButton{border:0px;}");  // 无边界，即只要图片中的图标
    setIcon(pix);
    setIconSize(QSize(width(), height()));
}

void MyPushButton::mousePressEvent(QMouseEvent * event)
{
    // 是否设置了按钮在鼠标按下状态的图片路径
    if (!pressedImg.isEmpty())
    {
        QPixmap pix;
        bool ret = pix.load(pressedImg);
        // 路径是否有效
        if (!ret)
        {
            QMessageBox::critical(this, "错误", "按钮在鼠标按下状态的图片加载失败");
        }
        else
        {
            setIcon(pix);
        }
    }

    QPushButton::mousePressEvent(event);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent * event)
{
    // 是否设置了按钮在鼠标按下状态的图片路径
    if (!pressedImg.isEmpty())
    {
        setIcon(QIcon(normalImg));
    }

    QPushButton::mouseReleaseEvent(event);
}

void MyPushButton::bounceAnim(int dy)
{
    moveDownAnim(dy);
    moveUpAnim(dy);
}

void MyPushButton::moveDownAnim(int dy)
{
    QPropertyAnimation * propertyAnimation = new QPropertyAnimation(this, "geometry");
    propertyAnimation->setDuration(300);
    propertyAnimation->setStartValue(QRect(x(), y(), width(), height()));
    propertyAnimation->setEndValue(QRect(x(), y() + dy, width(), height()));
    propertyAnimation->setEasingCurve(QEasingCurve::OutBounce);
    propertyAnimation->start();
}

void MyPushButton::moveUpAnim(int dy)
{
    QPropertyAnimation * propertyAnimation = new QPropertyAnimation(this, "geometry");
    propertyAnimation->setDuration(300);
    propertyAnimation->setStartValue(QRect(x(), y() + dy, width(), height()));
    propertyAnimation->setEndValue(QRect(x(), y(), width(), height()));
    propertyAnimation->setEasingCurve(QEasingCurve::OutBounce);
    propertyAnimation->start();
}
