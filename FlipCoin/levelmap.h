#ifndef LEVELMAP_H
#define LEVELMAP_H

#include <QObject>
#include <QHash>

class LevelMap : public QObject
{
    Q_OBJECT
public:
    explicit LevelMap(QObject *parent = nullptr);
    QVector<QVector<int>> getLevel(int levelNum);
private:
    QHash<int, QVector<QVector<int>>> data;
signals:

};

#endif // LEVELMAP_H
