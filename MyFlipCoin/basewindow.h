#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include <QMainWindow>
#include "mainscene.h"
#include "levelselectionscene.h"
#include "PlayScene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class BaseWindow; }
QT_END_NAMESPACE

class BaseWindow : public QMainWindow
{
    Q_OBJECT

public:
    BaseWindow(QWidget *parent = nullptr);
    ~BaseWindow();

private:
    void initWindow();
private:
    Ui::BaseWindow *ui;
    MainScene * mainScene;
    LevelSelectionScene * levelSelectionScene;
    PlayScene * playScene;
};
#endif // BASEWINDOW_H
