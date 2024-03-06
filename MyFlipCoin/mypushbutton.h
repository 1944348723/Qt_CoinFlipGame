#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyPushButton(QWidget *parent = nullptr);
    MyPushButton(QString _normalImg, QString _pressedImg = "");
    void bounceAnim(int dy);
    virtual void mousePressEvent(QMouseEvent * event) override;
    virtual void mouseReleaseEvent(QMouseEvent * event) override;
private:
    void moveDownAnim(int dy);
    void moveUpAnim(int dy);
signals:

private:
    QString normalImg;
    QString pressedImg;
};

#endif // MYPUSHBUTTON_H
