#include "qchooselevelscene.h"
#include <QMenuBar>
#include <QPainter>
#include <QLabel>
#include <QTimer>

QChooseLevelScene::QChooseLevelScene(QWidget *parent)
    : QMainWindow(parent)
    , mBackSound(":/res/BackButtonSound.wav", this)
    , mChooseSound(":/res/TapButtonSound.wav", this)
    , mBackMainSceneBtn(new QStartAndBackPushBtn(":/res/BackButton.png", ":/res/BackButtonSelected.png"))
    , mTitlePixmap(new QPixmap(":/res/Title.png"))
    , mChooseLevelSceneBgPixmap(new QPixmap(":/res/OtherSceneBg.png"))
    , menuBar(new QMenuBar(this))
{
    this->setFixedSize(320, 588);
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    this->setWindowTitle("选择游戏关卡场景");

    this->setMenuBar(menuBar);
    QMenu *startMenu = menuBar->addMenu("开始");
    QAction *exitAction = startMenu->addAction("退出");
    auto onActionExit = [&]()
    {
        this->close();
    };
    connect(exitAction, &QAction::triggered, onActionExit);

    mBackMainSceneBtn->setParent(this);
    mBackMainSceneBtn->move(this->width()-mBackMainSceneBtn->width(), this->height()-mBackMainSceneBtn->height());
    auto onBackMainSeneBtnClicked = [&]()
    {
        //友元类调用
        //传mainscene里的函数指针进来并调用
        //自定义信号并调用信号，让mainscene来连接信号(注意：哪个类里调用信号在哪个类里声明信号)
        //this->hide();
        mBackSound.play();
        emit this->chooseSceneBack();
    };
    connect(mBackMainSceneBtn, &QStartAndBackPushBtn::clicked, onBackMainSeneBtnClicked);

    for (int i = 0; i < 20; ++i)
    {
        QStartAndBackPushBtn *coin = new QStartAndBackPushBtn(":/res/LevelIcon.png"); //没释放内存
        coin->setParent(this);
        coin->move(20 + i%4 * 75, 160 + i/4 * 75);
        auto onCoinClicked = [=]()
        {
            mChooseSound.play();    //播放选中一关开始音效
            mPlayScene = new QPlayScene(this);
            mPlayScene->setLevelIndex(i+1);
            mPlayScene->move(this->x(), this->y());
            mPlayScene->show();
            auto onPlaySceneBackClicked = [&]()
            {
                auto onShowChooseScene = [&]()
                {
                    this->move(mPlayScene->x(), mPlayScene->y());
                    this->show();
                    delete mPlayScene;
                    mPlayScene = nullptr;
                };
                QTimer::singleShot(300, onShowChooseScene);
            };
            connect(mPlayScene, &QPlayScene::playSceneBack, onPlaySceneBackClicked);
            this->hide();
        };
        connect(coin, &QStartAndBackPushBtn::clicked, onCoinClicked);

//        QLabel *lbLevelNum = new QLabel(QString::number(i+1), this);    //未释放内存
        QLabel *lbLevelNum = new QLabel(this);    //未释放内存
        lbLevelNum->setNum(i+1);
        lbLevelNum->setFixedSize(coin->width(), coin->height());
        lbLevelNum->move(20 + i%4 * 75, 160 + i/4 * 75);
        lbLevelNum->setAlignment(Qt::AlignCenter);
        //设置label属性，透过鼠标事件
        lbLevelNum->setAttribute(Qt::WA_TransparentForMouseEvents);
    }
}

QChooseLevelScene::~QChooseLevelScene()
{
    delete mBackMainSceneBtn;
    delete mTitlePixmap;
    delete mChooseLevelSceneBgPixmap;
    delete menuBar;
}

void QChooseLevelScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, this->width(), this->height(), *mChooseLevelSceneBgPixmap);
    painter.drawPixmap((this->width()-mTitlePixmap->width())*0.5, 40, *mTitlePixmap);
}
