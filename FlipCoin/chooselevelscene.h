#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);

    virtual void paintEvent(QPaintEvent * event) override;
signals:
    void backButtonPressed();

};

#endif // CHOOSELEVELSCENE_H
