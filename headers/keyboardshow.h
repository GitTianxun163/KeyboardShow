#ifndef KEYBOARDSHOW_H
#define KEYBOARDSHOW_H

#include <QtWidgets/QtWidgets>
#include <QtGui/QtGui>
#include <QtCore/QtCore>

class KeyboardShow : public QWidget {
    // Q_OBJECT;
    QLabel* bg;
    QLabel* keys[128];
public:
    KeyboardShow();
    ~KeyboardShow();
    void mouseReleaseEvent(QMouseEvent*);
private:
    void initUI(); // 初始化UI
    void addKeyButtons();
    void addKeyButton(const QString,const QRect,const int);
};

#endif