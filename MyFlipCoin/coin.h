#ifndef COIN_H
#define COIN_H

#include <QPushButton>
#include <QTimer>

class Coin : public QPushButton
{
    Q_OBJECT
public:
    // explicit Coin(QWidget *parent = nullptr);
    Coin(QString img);
    void flip();
private:
    void flipStep();
signals:

public:
    bool isFront;
    static int flippingCount;
    int cur;
private:
    QTimer timer;   // 用来实现硬币翻转动画
    int min = 1;
    int max = 8;
};

#endif // COIN_H
