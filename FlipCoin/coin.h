#ifndef COIN_H
#define COIN_H

#include <QPushButton>
#include <QTimer>

class Coin : public QPushButton
{
    Q_OBJECT
public:
    //explicit Coin(QWidget *parent = nullptr);

    Coin(QString img);
signals:

public slots:
    void flip();        // 开启翻转定时器

private slots:
    void flipStep();    // 翻转单步
public:
    QTimer timer;   // 用来实现金币翻转
    bool isFront;   // 是否是正面
    int min = 1;        // 图片最小编号，表示正面
    int max = 8;        // 图片最大编号，表示反面
    int cur;        // 当前图片编号
    int row;
    int column;
    static int flippingCount;  // 在翻转的金币个数
};

#endif // COIN_H
