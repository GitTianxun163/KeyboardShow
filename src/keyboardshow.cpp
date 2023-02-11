#include <keyboardshow.h>
#include <global.h>
using namespace std;

KeyboardShow::KeyboardShow() : QWidget() {
    this->initUI();
}

KeyboardShow::~KeyboardShow() {

}

void KeyboardShow::initUI() {
    /*
        初始化UI
    */
    QDesktopWidget *desktop = QApplication::desktop();  // 获取桌面
    if (desktop->width() < WIDTH || desktop->height() < HEIGHT) {
        // 如果桌面太小弹窗
        QMessageBox::information(this,"Error","Unable to finish initializing UI because the window is too small.");
        exit(1); // 异常退出
    }
    this->setGeometry(desktop->width()-WIDTH-SPACED,desktop->height()-HEIGHT-SPACED,WIDTH,HEIGHT);  // 设置桌面大小

    // 设置窗口样式、调色板
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::SplashScreen);  // 设置 隐藏标题栏 | 置顶 | 任务栏不显示
    this->setAttribute(Qt::WA_TranslucentBackground,true);
    QPalette windowPalette = QPalette();
    this->setStyleSheet(Styles::WINDOW_STYLE);
    // windowPalette.setBrush(QPalette::All,QPalette::Window,QColor(0,0,0,140)); // 背景颜色
    windowPalette.setBrush(QPalette::All,QPalette::WindowText,QBrush(QColor(255,255,255,255))); // 文字颜色
    windowPalette.setBrush(QPalette::All,QPalette::Text,QBrush(QColor(255,255,255,255))); // 文字颜色
    this->setPalette(windowPalette);

    // 添加控件
    this->bg = new QLabel(this);
    this->bg->setGeometry(0,0,1024,1024);
    this->bg->setPixmap(QPixmap("resources/window_background.png"));
    this->bg->setScaledContents(true);
    this->addKeyButtons();
}

void KeyboardShow::addKeyButtons() {
    int x = 5,y = 5;
    this->addKeyButton("Esc",QRect(x,y,55,BKEY_H),0);
    x += 55+5;
    char cs[] = "!@#$%^&*()";
    for (int i = 1;i<=12;i++) {
        QString s = "F";
        if (i >= 10) s.append(49);
        s.append(char(48+i%10));
        this->addKeyButton(s,QRect(x,y,45,BKEY_H),i);
        x += 45+5;
    }
    this->addKeyButton("ScrLk",QRect(x,y,50,BKEY_H),13);x += 50+5;
    this->addKeyButton("PrtSc",QRect(x,y,50,BKEY_H),14);x += 50+5;
    // this->addKeyButton("Pause",QRect(x,y,50,BKEY_H),13);x += 50+5;
    // this->addKeyButton("Insert",QRect(x,y,50,BKEY_H),13);x += 50+5;
    y += BKEY_H+5;x = 5;
    this->addKeyButton("~",QRect(x,y,HKEY_W,HKEY_W),15);x += HKEY_W+5;
    for (int i = 1;i<=10;i++) {
        QString s = "";
        s.append(cs[i-1]);
        s.append('\n');
        s.append(char(48+i%10));
        this->addKeyButton(s,QRect(x,y,HKEY_W,HKEY_W),15+i);x += HKEY_W+5;
    }
    this->addKeyButton("-\n_",QRect(x,y,HKEY_W,HKEY_W),26);x += HKEY_W+5;
    this->addKeyButton("+\n=",QRect(x,y,HKEY_W,HKEY_W),27);x += HKEY_W+5;
    this->addKeyButton("Backspace",QRect(x,y,2*HKEY_W+10,HKEY_W),28);x += 2*HKEY_W+15;
    this->addKeyButton("Home",QRect(x,y,HKEY_W,HKEY_W),29);x += HKEY_W+5;
    this->addKeyButton("End",QRect(x,y,HKEY_W,HKEY_W),30);x += HKEY_W+5;
    x = 5;y += HKEY_W+5;

    this->addKeyButton("Tab",QRect(x,y,HKEY_W+HKEY_W/2+5,HKEY_W),31);x += HKEY_W+HKEY_W/2+10;
    char z1s[] = "QWERTYUIOP{}";
    for (int i = 0;i<12;i++) {
        QString s;
        s.append(z1s[i]);
        this->addKeyButton(s,QRect(x,y,HKEY_W,HKEY_W),32+i);x += HKEY_W+5;
    }
    this->addKeyButton("|\n\\",QRect(x,y,HKEY_W+HKEY_W/2+5,HKEY_W),44);x += HKEY_W+HKEY_W/2+10;
    this->addKeyButton("Del",QRect(x,y,HKEY_W,HKEY_W*2+5),45);x += HKEY_W+5;
    this->addKeyButton("PgUp",QRect(x,y,HKEY_W,HKEY_W),46);x += HKEY_W+5;

    x = 5;y += HKEY_W+5;
    this->addKeyButton("CapsLock",QRect(x,y,HKEY_W+HKEY_W/2+20,HKEY_W),47);x += HKEY_W+HKEY_W/2+25;
    char z2s[] = "ASDFGHJKL";
    for (int i = 0;i<9;i++) {
        QString s;
        s.append(z2s[i]);
        this->addKeyButton(s,QRect(x,y,HKEY_W,HKEY_W),48+i);x += HKEY_W+5;
    }
    this->addKeyButton(":\n;",QRect(x,y,HKEY_W,HKEY_W),57);x += HKEY_W+5;
    this->addKeyButton("'\n\"",QRect(x,y,HKEY_W,HKEY_W),58);x += HKEY_W+5;
    this->addKeyButton("Enter",QRect(x,y,HKEY_W+HKEY_W/2+35,HKEY_W),59);x += HKEY_W+HKEY_W/2+40+HKEY_W+5;
    this->addKeyButton("PgDn",QRect(x,y,HKEY_W,HKEY_W),60);x += HKEY_W+5;

    x = 5;y += HKEY_W+5;
    this->addKeyButton("Shift",QRect(x,y,HKEY_W*3+12,HKEY_W),61);x += HKEY_W*3+17;
    char z3s[] = "ZXCVBNM";
    for (int i = 0;i<7;i++) {
        QString s;
        s.append(z3s[i]);
        this->addKeyButton(s,QRect(x,y,HKEY_W,HKEY_W),62+i);x += HKEY_W+5;
    }
    this->addKeyButton("<\n,",QRect(x,y,HKEY_W,HKEY_W),69);x += HKEY_W+5;
    this->addKeyButton(">\n.",QRect(x,y,HKEY_W,HKEY_W),70);x += HKEY_W+5;
    this->addKeyButton("Shift",QRect(x,y,HKEY_W*3+12,HKEY_W),71);x += HKEY_W*3+18;
    this->addKeyButton("Up",QRect(x,y,HKEY_W,HKEY_W),72);x += HKEY_W+5;

    x = 5;y += HKEY_W+5;
    this->addKeyButton("Ctrl",QRect(x,y,HKEY_W*2+7,HKEY_W),73);x += HKEY_W*2+12;
    this->addKeyButton("Fn",QRect(x,y,HKEY_W,HKEY_W),74);x += HKEY_W+5;
    this->addKeyButton("Win",QRect(x,y,HKEY_W,HKEY_W),75);x += HKEY_W+5;
    this->addKeyButton("Alt",QRect(x,y,HKEY_W,HKEY_W),76);x += HKEY_W+5;
    this->addKeyButton("Space",QRect(x,y,HKEY_W*6,HKEY_W),77);x += HKEY_W*6+5;
    this->addKeyButton("Alt",QRect(x,y,HKEY_W,HKEY_W),78);x += HKEY_W+5;
    this->addKeyButton("Menu",QRect(x,y,HKEY_W,HKEY_W),79);x += HKEY_W+5;
    this->addKeyButton("Ctrl",QRect(x,y,HKEY_W*2-12,HKEY_W),80);x += HKEY_W*2-7;
    this->addKeyButton("Left",QRect(x,y,HKEY_W,HKEY_W),81);x += HKEY_W+5;
    this->addKeyButton("Down",QRect(x,y,HKEY_W,HKEY_W),82);x += HKEY_W+5;
    this->addKeyButton("Right",QRect(x,y,HKEY_W,HKEY_W),83);x += HKEY_W+5;

}

void KeyboardShow::addKeyButton(const QString name,const QRect rect,const int index) {
    this->keys[index] = new QLabel(name,this);
    this->keys[index]->setStyleSheet(QString("border-image:url(resources/label_background.png);"));
    this->keys[index]->setGeometry(rect);
    this->keys[index]->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

void KeyboardShow::mouseReleaseEvent(QMouseEvent* event) {
    this->close();
    exit(0);
}