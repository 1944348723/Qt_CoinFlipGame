#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include "coin.h"
#include <QMutex>

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit PlayScene(int _level, QWidget *parent = nullptr);
    virtual void paintEvent(QPaintEvent * event) override;

signals:
    void backButtonClicked();

private:
    int level;
    QVector<QVector<int>> levelArray;
    Coin * coins[5][5];
    bool win;
};

#endif // PLAYSCENE_H
