#include "mainscene.h"
#include "./ui_mainscene.h"
#include <QDesktopWidget>
#include <QPainter>
#include <QTimer>

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , mCoinFlipStartButton(new QStartAndBackPushBtn(":/res/MenuSceneStartButton.png"))
    , mStartSound(new QSound(":/res/TapButtonSound.wav", this))
    , mTitlePixmap(new QPixmap(":/res/Title.png"))
    , mPlayLevelSceneBgPixmap(new QPixmap(":/res/PlayLevelSceneBg.png"))
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);
    this->setFixedSize(320, 588);
//    QDesktopWidget *desktop = QApplication::desktop();
//    move((desktop->width()-this->width())*0.5, (desktop->height()-this->height())*0.5);   //ubuntu需要设置主窗口在桌面中间位置
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    this->setWindowTitle("快乐翻翻翻");

    *mTitlePixmap = mTitlePixmap->scaled(mTitlePixmap->width()*0.5, mTitlePixmap->height()*0.5);

    mChooseLevelScene = new QChooseLevelScene(this);
    auto onChooseSceneBackClicked = [&]()
    {
        auto onShowMainScene = [&]()
        {
            this->move(mChooseLevelScene->x(), mChooseLevelScene->y());
            this->show();
            mChooseLevelScene->hide();
        };
        QTimer::singleShot(300, onShowMainScene);
    };
    connect(mChooseLevelScene, &QChooseLevelScene::chooseSceneBack, onChooseSceneBackClicked);

    mCoinFlipStartButton->setParent(this);
    mCoinFlipStartButton->move(this->width()*0.5-mCoinFlipStartButton->width()*0.5, this->height()*0.7);
    auto onStartButtonClicked = [&]()
    {
        //mStartSound->setLoops(10);    //设置循环播放10次，如果参数-1，无限循环
        mStartSound->play();    //播放开始游戏音效
        mCoinFlipStartButton->zoom(true);
        mCoinFlipStartButton->zoom(false);
        auto onShowChooseScene = [&]()
        {
            mChooseLevelScene->move(this->x(), this->y());
            mChooseLevelScene->show();
            this->hide();
        };
        QTimer::singleShot(300, onShowChooseScene);
    };
    connect(mCoinFlipStartButton, &QStartAndBackPushBtn::clicked, onStartButtonClicked);
}

MainScene::~MainScene()
{
    delete mCoinFlipStartButton;
    delete mStartSound;
    delete mChooseLevelScene;
    delete mTitlePixmap;
    delete mPlayLevelSceneBgPixmap;
    delete ui;
}

void MainScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, this->width(), this->height(), *mPlayLevelSceneBgPixmap);
    painter.drawPixmap(15, 40, *mTitlePixmap);
}

void MainScene::on_action_triggered()
{
    this->close();
}
