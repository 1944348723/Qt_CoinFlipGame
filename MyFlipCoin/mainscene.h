#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QWidget>

class MainScene : public QWidget
{
    Q_OBJECT
public:
    explicit MainScene(QWidget *parent = nullptr);
    virtual void paintEvent(QPaintEvent * event) override;

signals:
    void startButtonClicked();
};

#endif // MAINSCENE_H
