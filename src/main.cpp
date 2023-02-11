/*
本作品由：哔哩哔哩-天寻Game 制作，本作品使用GPLv3开源协议，请您遵守
哔哩哔哩首页：https://space.bilibili.com/627871340
github仓库：
*/
#include <bits/stdc++.h>
#include <QtWidgets/QApplication>
#include <keyboardshow.h>
using namespace std;

int main(int argc, char *argv[]) {
    QApplication app(argc,argv);
    KeyboardShow win;
    win.show();
    return app.exec();
}