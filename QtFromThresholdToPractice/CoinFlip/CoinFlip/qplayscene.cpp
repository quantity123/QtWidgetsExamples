#include "qplayscene.h"
#include <QPainter>
#include "dataconfig.h"
#include <QTimer>
#include <QDebug>
#include <QPropertyAnimation>

QPlayScene::QPlayScene(QWidget *parent)
    : QMainWindow(parent)
    , mWinSound(":/res/LevelWinSound.wav", this)
    , mFlipSound(":/res/ConFlipSound.wav", this)
    , mBackSound(":/res/BackButtonSound.wav", this)
    , mBackChooseLevelSceneBtn(new QStartAndBackPushBtn(":/res/BackButton.png", ":/res/BackButtonSelected.png"))
    , mTitlePixmap(new QPixmap(":/res/Title.png"))
    , mPlayLevelSceneBgPixmap(new QPixmap(":/res/PlayLevelSceneBg.png"))
    , menuBar(new QMenuBar(this))
{
    this->setFixedSize(320, 588);
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    this->setWindowTitle("翻金币游戏场景");

    this->setMenuBar(menuBar);
    QMenu *startMenu = menuBar->addMenu("开始");
    QAction *exitAction = startMenu->addAction("退出");
    auto onActionExit = [&]()
    {
        this->close();
    };
    connect(exitAction, &QAction::triggered, onActionExit);

    //设置游戏标题大小
    *mTitlePixmap = mTitlePixmap->scaled(mTitlePixmap->width()*0.5, mTitlePixmap->height()*0.5);

    //设置胜利图片显示和动画
    mWinLabel.setParent(this);
    QPixmap winPixmap;
    winPixmap.load(":/res/LevelCompletedDialogBg.png");
    mWinLabel.setGeometry((this->width()-winPixmap.width())*0.5, -winPixmap.height(), winPixmap.width(), winPixmap.height());
    mWinLabel.setPixmap(winPixmap);
    //设置动画对象是哪个目标
    winLabelAnimation.setTargetObject(&mWinLabel);
    //设置动画属性类型
    winLabelAnimation.setPropertyName("geometry");
    //设置动画播放时间
    winLabelAnimation.setDuration(2000);
    //设置动画缓缓移动曲线
    winLabelAnimation.setEasingCurve(QEasingCurve::OutBounce);
    //设置起始位置
    winLabelAnimation.setStartValue(QRect(mWinLabel.x(), mWinLabel.y(), mWinLabel.width(), mWinLabel.height()));
    //设置结束位置
    winLabelAnimation.setEndValue(QRect(mWinLabel.x(), mWinLabel.y()+185, mWinLabel.width(), mWinLabel.height()));

    //设置返回按钮
    mBackChooseLevelSceneBtn->setParent(this);
    mBackChooseLevelSceneBtn->move(this->width()-mBackChooseLevelSceneBtn->width(), this->height()-mBackChooseLevelSceneBtn->height());
    auto onBackChooseLevelBtnClicked = [&]()
    {
        mBackSound.play();
        //自定义信号并调用信号，(注意：哪个类里调用信号在哪个类里声明信号)
        emit this->playSceneBack();
    };
    connect(mBackChooseLevelSceneBtn, &QStartAndBackPushBtn::clicked, onBackChooseLevelBtnClicked);

    mLevelCaption.setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    mLevelCaption.setFont(font);
    mLevelCaption.setGeometry(10, this->height()-50, 120, 50);
}

QPlayScene::~QPlayScene()
{
    delete mBackChooseLevelSceneBtn;
    delete mTitlePixmap;
    delete mPlayLevelSceneBgPixmap;
    delete menuBar;
}

void QPlayScene::setLevelIndex(quint8 aIndex)
{
    mLevelIndex = aIndex;
    mLevelCaption.setText("Level:" + QString::number(mLevelIndex));

    dataConfig coinArrayConfig;
    //初始化金币游戏数组
    for (quint8 i=0; i<4; ++i)
    {
        for (quint8 j=0; j<4; ++j)
        {
            mCoinArray[i][j] = coinArrayConfig.mData[this->mLevelIndex][i][j];
        }
    }

    //显示金币背景图与金币
    for (quint8 i=0; i<4; ++i)
    {
        for (quint8 j=0; j<4; j++)
        {
            //背景图
            QPixmap pixmap(":/res/BoardNode.png");
            QLabel *label = new QLabel(this);
            label->setPixmap(pixmap);
            label->setGeometry(57+i*50, 200+j*50, pixmap.width(), pixmap.height());

            //金币图
            QString coinPixmap;
            if (mCoinArray[i][j] == 1)
                coinPixmap = ":/res/Coin0001.png";
            else
                coinPixmap = ":/res/Coin0008.png";
            QCoinFlipPushBtn *coinBtn = new QCoinFlipPushBtn(coinPixmap);
            coinBtn->setParent(this);
            coinBtn->move(59+i*50, 204+j*50);
            coinBtn->setPosX(i);
            coinBtn->setPosY(j);
            coinBtn->setFlag(mCoinArray[i][j]); //1正面，2反面
            mCoinBtnArray[i][j] = coinBtn;

            auto onCoinBtnClicked = [=]()
            {
                if (isWin)  //如果胜利了不往后执行
                    return;
                if (mIsFlipping)
                    return;
                mFlipSound.play();  //翻转硬币音效
                mIsFlipping = true;
                //点击反转硬币
                coinBtn->changeFlag();
//                mCoinArray[i][j] = this->mCoinArray[i][j]==0 ? 1 : 0;

                auto onDelayFlipAroundCoins = [=]()
                {
                    //翻转硬币的左侧硬币
                    if (coinBtn->posX()-1 >= 0)
                    {
                        mCoinBtnArray[coinBtn->posX()-1][coinBtn->posY()]->changeFlag();
//                        mCoinArray[coinBtn->posX()-1][coinBtn->posY()] = mCoinArray[coinBtn->posX()-1][coinBtn->posY()]==0 ? 1 : 0;
                    }

                    //翻转硬币的右侧硬币
                    if (coinBtn->posX()+1 <= 3)
                    {
                        mCoinBtnArray[coinBtn->posX()+1][coinBtn->posY()]->changeFlag();
//                        mCoinArray[coinBtn->posX()+1][coinBtn->posY()] = mCoinArray[coinBtn->posX()+1][coinBtn->posY()]==0 ? 1 : 0;
                    }

                    //翻转硬币的上侧硬币
                    if (coinBtn->posY()-1 >= 0)
                    {
                        mCoinBtnArray[coinBtn->posX()][coinBtn->posY()-1]->changeFlag();
//                        mCoinArray[coinBtn->posX()][coinBtn->posY()-1] = mCoinArray[coinBtn->posX()][coinBtn->posY()-1]==0 ? 1 : 0;
                    }

                    //翻转硬币的下侧硬币
                    if (coinBtn->posY()+1 <= 3)
                    {
                        mCoinBtnArray[coinBtn->posX()][coinBtn->posY()+1]->changeFlag();
//                        mCoinArray[coinBtn->posX()][coinBtn->posY()+1] = mCoinArray[coinBtn->posX()][coinBtn->posY()+1]==0 ? 1 : 0;
                    }

                    //判断是否胜利
                    isWin = true;
                    for (quint8 i=0; i<4; ++i)
                    {
                        for (quint8 j=0; j<4; ++j)
                        {
                            if (mCoinBtnArray[i][j]->flag() == false)
                            {
                                this->isWin = false;
                                mIsFlipping = false;
                                return;
                            }
                        }
                    }
                    if (isWin)
                    {
                        mWinSound.play();   //游戏胜利音效
                        //执行胜利图片动画
                        winLabelAnimation.start();
                    }
                };
                QTimer::singleShot(500, onDelayFlipAroundCoins);
            };
            connect(coinBtn, &QCoinFlipPushBtn::clicked, onCoinBtnClicked);
        }
    }
}

void QPlayScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, this->width(), this->height(), *mPlayLevelSceneBgPixmap);
    painter.drawPixmap(15, 40, *mTitlePixmap);
}
