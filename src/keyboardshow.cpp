#include <keyboardshow.h>
#include <global.h>
using namespace std;

KeyboardShow::KeyboardShow() : QWidget() {
    memset(this->keys,0,sizeof(this->keys));
    lmx = -1;
    lmy = -1;
    this->initUI();
    // connect(this->act,SIGNAL(timeout()),this,SLOT(ac()));
    // this->act->start(1000);
    // QMessageBox::information(this,"Test","test");
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
    this->addKeyButton("Insert",QRect(x,y,50,BKEY_H),14);x += 50+5;
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
        if (i == 10) s.append("\n[");
        if (i == 11) s.append("\n]");
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
    this->addKeyButton("Shift",QRect(x,y,HKEY_W*3+10-HKEY_W/2,HKEY_W),61);x += HKEY_W*3+15-HKEY_W/2;
    char z3s[] = "ZXCVBNM";
    for (int i = 0;i<7;i++) {
        QString s;
        s.append(z3s[i]);
        this->addKeyButton(s,QRect(x,y,HKEY_W,HKEY_W),62+i);x += HKEY_W+5;
    }
    this->addKeyButton("<\n,",QRect(x,y,HKEY_W,HKEY_W),69);x += HKEY_W+5;
    this->addKeyButton(">\n.",QRect(x,y,HKEY_W,HKEY_W),70);x += HKEY_W+5;
    this->addKeyButton("?\n/",QRect(x,y,HKEY_W,HKEY_W),84);x += HKEY_W+5;
    this->addKeyButton("Shift",QRect(x,y,HKEY_W*3+10-HKEY_W/2,HKEY_W),71);x += HKEY_W*3+15-HKEY_W/2;
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
    this->lmx = -1;
    this->lmy = -1;
}

void KeyboardShow::mouseMoveEvent(QMouseEvent* event) {
    if (min(this->lmx,this->lmy) != -1) this->setGeometry(this->x()+(event->x()-this->lmx),this->y()+(event->y()-this->lmy),WIDTH,HEIGHT);
}

void KeyboardShow::mousePressEvent(QMouseEvent* event) {
    this->lmx = event->x();
    this->lmy = event->y();
}

void KeyboardShow::keyPressEvent(QKeyEvent* event) {
    printf("Press: %d\n",event->key());
    switch (event->key()) {
        case Qt::Key_Escape:setHover(0);break;
        case Qt::Key_F1:setHover(1);break;
        case Qt::Key_F2:setHover(2);break;
        case Qt::Key_F3:setHover(3);break;
        case Qt::Key_F4:setHover(4);break;
        case Qt::Key_F5:setHover(5);break;
        case Qt::Key_F6:setHover(6);break;
        case Qt::Key_F7:setHover(7);break;
        case Qt::Key_F8:setHover(8);break;
        case Qt::Key_F9:setHover(9);break;
        case Qt::Key_F10:setHover(10);break;
        case Qt::Key_F11:setHover(11);break;
        case Qt::Key_F12:setHover(12);break;
        case Qt::Key_ScrollLock:setHover(13);break;
        case Qt::Key_Insert:setHover(14);break;
        case 96:case Qt::Key_AsciiTilde:setHover(15);break;
        case '!':case Qt::Key_1:setHover(16);break;
        case '@':case Qt::Key_2:setHover(17);break;
        case '#':case Qt::Key_3:setHover(18);break;
        case '$':case Qt::Key_4:setHover(19);break;
        case '%':case Qt::Key_5:setHover(20);break;
        case '^':case Qt::Key_6:setHover(21);break;
        case '&':case Qt::Key_7:setHover(22);break;
        case '*':case Qt::Key_8:setHover(23);break;
        case '(':case Qt::Key_9:setHover(24);break;
        case ')':case Qt::Key_0:setHover(25);break;
        case '_':case Qt::Key_Minus:setHover(26);break;
        case Qt::Key_Plus:case Qt::Key_Equal:setHover(27);break;
        case Qt::Key_Backspace:setHover(28);break;
        case Qt::Key_Home:setHover(29);break;
        case Qt::Key_End:setHover(30);break;
        case Qt::Key_Tab:setHover(31);break;
        case Qt::Key_Q:setHover(32);break;
        case Qt::Key_W:setHover(33);break;
        case Qt::Key_E:setHover(34);break;
        case Qt::Key_R:setHover(35);break;
        case Qt::Key_T:setHover(36);break;
        case Qt::Key_Y:setHover(37);break;
        case Qt::Key_U:setHover(38);break;
        case Qt::Key_I:setHover(39);break;
        case Qt::Key_O:setHover(40);break;
        case Qt::Key_P:setHover(41);break;
        case '{':case '[':setHover(42);break;
        case '}':case ']':setHover(43);break;
        case '|':case '\\':setHover(44);break;
        case Qt::Key_Delete:setHover(45);break;
        case Qt::Key_PageUp:setHover(46);break;
        case Qt::Key_CapsLock:setHover(47);break;
        case Qt::Key_A:setHover(48);break;
        case Qt::Key_S:setHover(49);break;
        case Qt::Key_D:setHover(50);break;
        case Qt::Key_F:setHover(51);break;
        case Qt::Key_G:setHover(52);break;
        case Qt::Key_H:setHover(53);break;
        case Qt::Key_J:setHover(54);break;
        case Qt::Key_K:setHover(55);break;
        case Qt::Key_L:setHover(56);break;
        case ':':case ';':setHover(57);break;
        case '\"':case '\'':setHover(58);break;
        case Qt::Key_Enter:case Qt::Key_Return:setHover(59);break;
        case Qt::Key_PageDown:setHover(60);break;
        case Qt::Key_Shift:{setHover(61);setHover(71);};break;
        case Qt::Key_Z:setHover(62);break;
        case Qt::Key_X:setHover(63);break;
        case Qt::Key_C:setHover(64);break;
        case Qt::Key_V:setHover(65);break;
        case Qt::Key_B:setHover(66);break;
        case Qt::Key_N:setHover(67);break;
        case Qt::Key_M:setHover(68);break;
        case '<':case ',':setHover(69);break;
        case '>':case '.':setHover(70);break;
        case '?':case '/':setHover(84);break;
        case Qt::Key_Up:setHover(72);break;
        case Qt::Key_Control:{setHover(73);setHover(80);};break;
        case Qt::Key_Finance:setHover(74);break;
        case Qt::Key_Meta:setHover(75);break;
        case Qt::Key_Alt:{setHover(76);setHover(78);};break;
        case Qt::Key_Space:setHover(77);break;
        case Qt::Key_Menu:setHover(79);break;
        case Qt::Key_Left:setHover(81);break;
        case Qt::Key_Down:setHover(82);break;
        case Qt::Key_Right:setHover(83);break;
        default:break;
    }
}

void KeyboardShow::keyReleaseEvent(QKeyEvent* event) {
    switch (event->key()) {
        case Qt::Key_Escape:setNoHover(0);break;
        case Qt::Key_F1:setNoHover(1);break;
        case Qt::Key_F2:setNoHover(2);break;
        case Qt::Key_F3:setNoHover(3);break;
        case Qt::Key_F4:setNoHover(4);break;
        case Qt::Key_F5:setNoHover(5);break;
        case Qt::Key_F6:setNoHover(6);break;
        case Qt::Key_F7:setNoHover(7);break;
        case Qt::Key_F8:setNoHover(8);break;
        case Qt::Key_F9:setNoHover(9);break;
        case Qt::Key_F10:setNoHover(10);break;
        case Qt::Key_F11:setNoHover(11);break;
        case Qt::Key_F12:setNoHover(12);break;
        case Qt::Key_ScrollLock:setNoHover(13);break;
        case Qt::Key_Insert:setNoHover(14);break;
        case 96:case Qt::Key_AsciiTilde:setNoHover(15);break;
        case '!':case Qt::Key_1:setNoHover(16);break;
        case '@':case Qt::Key_2:setNoHover(17);break;
        case '#':case Qt::Key_3:setNoHover(18);break;
        case '$':case Qt::Key_4:setNoHover(19);break;
        case '%':case Qt::Key_5:setNoHover(20);break;
        case '^':case Qt::Key_6:setNoHover(21);break;
        case '&':case Qt::Key_7:setNoHover(22);break;
        case '*':case Qt::Key_8:setNoHover(23);break;
        case '(':case Qt::Key_9:setNoHover(24);break;
        case ')':case Qt::Key_0:setNoHover(25);break;
        case '_':case Qt::Key_Minus:setNoHover(26);break;
        case Qt::Key_Plus:case Qt::Key_Equal:setNoHover(27);break;
        case Qt::Key_Backspace:setNoHover(28);break;
        case Qt::Key_Home:setNoHover(29);break;
        case Qt::Key_End:setNoHover(30);break;
        case Qt::Key_Tab:setNoHover(31);break;
        case Qt::Key_Q:setNoHover(32);break;
        case Qt::Key_W:setNoHover(33);break;
        case Qt::Key_E:setNoHover(34);break;
        case Qt::Key_R:setNoHover(35);break;
        case Qt::Key_T:setNoHover(36);break;
        case Qt::Key_Y:setNoHover(37);break;
        case Qt::Key_U:setNoHover(38);break;
        case Qt::Key_I:setNoHover(39);break;
        case Qt::Key_O:setNoHover(40);break;
        case Qt::Key_P:setNoHover(41);break;
        case '{':case '[':setNoHover(42);break;
        case '}':case ']':setNoHover(43);break;
        case '|':case '\\':setNoHover(44);break;
        case Qt::Key_Delete:setNoHover(45);break;
        case Qt::Key_PageUp:setNoHover(46);break;
        case Qt::Key_CapsLock:setNoHover(47);break;
        case Qt::Key_A:setNoHover(48);break;
        case Qt::Key_S:setNoHover(49);break;
        case Qt::Key_D:setNoHover(50);break;
        case Qt::Key_F:setNoHover(51);break;
        case Qt::Key_G:setNoHover(52);break;
        case Qt::Key_H:setNoHover(53);break;
        case Qt::Key_J:setNoHover(54);break;
        case Qt::Key_K:setNoHover(55);break;
        case Qt::Key_L:setNoHover(56);break;
        case ':':case ';':setNoHover(57);break;
        case '\"':case '\'':setNoHover(58);break;
        case Qt::Key_Enter:case Qt::Key_Return:setNoHover(59);break;
        case Qt::Key_PageDown:setNoHover(60);break;
        case Qt::Key_Shift:{setNoHover(61);setNoHover(71);};break;
        case Qt::Key_Z:setNoHover(62);break;
        case Qt::Key_X:setNoHover(63);break;
        case Qt::Key_C:setNoHover(64);break;
        case Qt::Key_V:setNoHover(65);break;
        case Qt::Key_B:setNoHover(66);break;
        case Qt::Key_N:setNoHover(67);break;
        case Qt::Key_M:setNoHover(68);break;
        case '<':case ',':setNoHover(69);break;
        case '>':case '.':setNoHover(70);break;
        case '?':case '/':setNoHover(84);break;
        case Qt::Key_Up:setNoHover(72);break;
        case Qt::Key_Control:{setNoHover(73);setNoHover(80);};break;
        case Qt::Key_Finance:setNoHover(74);break;
        case Qt::Key_Meta:setNoHover(75);break;
        case Qt::Key_Alt:{setNoHover(76);setNoHover(78);};break;
        case Qt::Key_Space:setNoHover(77);break;
        case Qt::Key_Menu:setNoHover(79);break;
        case Qt::Key_Left:setNoHover(81);break;
        case Qt::Key_Down:setNoHover(82);break;
        case Qt::Key_Right:setNoHover(83);break;
        default:break;
    }
}
