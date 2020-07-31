#ifndef QMYHEADERVIEW_H
#define QMYHEADERVIEW_H

#include <QHeaderView>

class QMyHeaderView : public QHeaderView
{
    Q_OBJECT
public:
    explicit QMyHeaderView(QWidget *parent = nullptr);
public slots:
    void slot_stateChanged(Qt::CheckState state);
protected:
    void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
signals:
    void stateChanged(Qt::CheckState state);
private:
    Qt::CheckState mState;
    bool mIsPressed;
};

#endif // QMYHEADERVIEW_H
