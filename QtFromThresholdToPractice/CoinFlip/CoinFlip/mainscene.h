#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include "qstartandbackpushbtn.h"
#include "qchooselevelscene.h"
#include <QSound>

QT_BEGIN_NAMESPACE
namespace Ui { class MainScene; }
QT_END_NAMESPACE

class MainScene : public QMainWindow
{
    Q_OBJECT
public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();
protected:
    //绘图事件
    void paintEvent(QPaintEvent *event) override;
private slots:
    void on_action_triggered();
private:
    QStartAndBackPushBtn *mCoinFlipStartButton;
    QSound *mStartSound;
    QChooseLevelScene *mChooseLevelScene;
    QPixmap *mTitlePixmap;
    QPixmap *mPlayLevelSceneBgPixmap;
    Ui::MainScene *ui;
};
#endif // MAINSCENE_H
