#ifndef LEVELSELECTIONSCENE_H
#define LEVELSELECTIONSCENE_H

#include <QWidget>

class LevelSelectionScene : public QWidget
{
    Q_OBJECT
public:
    explicit LevelSelectionScene(QWidget *parent = nullptr);
    virtual void paintEvent(QPaintEvent * event) override;

signals:
    void levelButtonClicked(int levelNum);
    void backButtonClicked();
private:
    void initBackButton();
};

#endif // LEVELSELECTIONSCENE_H
