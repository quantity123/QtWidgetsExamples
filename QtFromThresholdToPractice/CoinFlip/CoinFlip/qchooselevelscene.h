#ifndef QCHOOSELEVELSCENE_H
#define QCHOOSELEVELSCENE_H

#include <QMainWindow>
#include "qstartandbackpushbtn.h"
#include "qplayscene.h"
#include <QSound>

class QChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit QChooseLevelScene(QWidget *parent = nullptr);
    ~QChooseLevelScene();
signals:
    void chooseSceneBack();
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    QSound mBackSound;
    QSound mChooseSound;
    QPlayScene *mPlayScene;
    //封装一个coinBtnList类来管理按钮与label数字，方便释放
    QStartAndBackPushBtn *mBackMainSceneBtn;
    QPixmap *mTitlePixmap;
    QPixmap *mChooseLevelSceneBgPixmap;
    QMenuBar *menuBar;
};

#endif // QCHOOSELEVELSCENE_H
