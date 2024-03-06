#include "levelmap.h"

LevelMap::LevelMap(QObject *parent)
    : QObject{parent}
{
    data[1] = QVector<QVector<int>>({
        {1, 1, 1, 1},
        {1, 1, 0, 1},
        {1, 0, 0, 0},
        {1, 1, 0, 1}
    });

    data[2] = QVector<QVector<int>>({
        {1, 0, 1, 1},
        {0, 0, 1, 1},
        {1, 1, 0, 0},
        {1, 1, 0, 1}
    });

    data[3] = QVector<QVector<int>>({
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
    });
}

QVector<QVector<int>> LevelMap::getLevel(int levelNum)
{
    return data[levelNum];
}
