#ifndef KEYBOARDSHOW_H
#define KEYBOARDSHOW_H

#include <QtWidgets/QtWidgets>
#include <QtGui/QtGui>
#include <QtCore/QtCore>
#define setHover(x) this->keys[x]->setStyleSheet(QString("border-image:url(resources/label_background_hover.png);"))
#define setNoHover(x) this->keys[x]->setStyleSheet(QString("border-image:url(resources/label_background.png);"))

// short keymaps[]= {
//     Qt::Key_Escape,
//     Qt::Key_F1,
//     Qt::Key_F2,
//     Qt::Key_F3,
//     Qt::Key_F4,
//     Qt::Key_F5,
//     Qt::Key_F6,
//     Qt::Key_F7,
//     Qt::Key_F8,
//     Qt::Key_F9,
//     Qt::Key_F10,
//     Qt::Key_F11,
//     Qt::Key_F12,
//     Qt::Key_ScrollLock,
//     Qt::Key_Insert,
//     Qt::Key_Tab,
//     Qt::Key_Q,Qt::Key_W,Qt::Key_E,Qt::Key_R,Qt::Key_T,Qt::Key_Y,Qt::Key_U,Qt::Key_I,Qt::Key_O,Qt::Key_P
// };

class KeyboardShow : public QWidget {
    // Q_OBJECT;
    QLabel* bg;
    QLabel* keys[128];
    int lmx,lmy;
public:
    KeyboardShow();
    ~KeyboardShow();
    void mouseReleaseEvent(QMouseEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void keyReleaseEvent(QKeyEvent*);
    void keyPressEvent(QKeyEvent*);
private:
    void initUI(); // 初始化UI
    void addKeyButtons();
    void addKeyButton(const QString,const QRect,const int);
private slots:
    void updateKeys();
};

#endif