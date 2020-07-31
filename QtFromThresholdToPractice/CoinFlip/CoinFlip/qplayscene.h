#ifndef QPALYSCENE_H
#define QPALYSCENE_H

#include <QMainWindow>
#include <QMenuBar>
#include "qstartandbackpushbtn.h"
#include <QLabel>
#include "qcoinflippushbtn.h"
#include <QSound>

class QPlayScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit QPlayScene(QWidget *parent = nullptr);
    ~QPlayScene();
    void setLevelIndex(quint8 aIndex);
signals:
    void playSceneBack();
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    QSound mWinSound;
    QSound mFlipSound;
    QSound mBackSound;
    bool mIsFlipping = false;
    bool isWin = false;
    QCoinFlipPushBtn *mCoinBtnArray[4][4];
    int mCoinArray[4][4];   //数组保存每个金币的具体数据
    quint8 mLevelIndex;
    QLabel mLevelCaption;
    QStartAndBackPushBtn *mBackChooseLevelSceneBtn;
    QPixmap *mTitlePixmap;
    QPixmap *mPlayLevelSceneBgPixmap;
    QPropertyAnimation winLabelAnimation;
    QLabel mWinLabel;
    QMenuBar *menuBar;
};

#endif // QPALYSCENE_H
