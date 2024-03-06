#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    // explicit MyPushButton(QWidget *parent = nullptr);
    MyPushButton(QString nomalImg, QString pressedImg = "");

    virtual void mousePressEvent(QMouseEvent * event) override;
    virtual void mouseReleaseEvent(QMouseEvent * event) override;
signals:

public slots:
    void moveUpAnim(int dy);
    void moveDownAnim(int dy);

private:
    QString normalImg;
    QString pressedImg;
};

#endif // MYPUSHBUTTON_H
