keyboardshow: main.o keyboardshow.o
	g++ build/main.o build/keyboardshow.o D:/Qt/5.14.2/5.14.2/mingw73_64/lib/*.a -Wl,--subsystem,windows -o bin/keyboardshow.exe
	bin/keyboardshow

main.o: src/main.cpp
	g++ src/main.cpp -c -o build/main.o -I headers -I D:/Qt/5.14.2/5.14.2/mingw73_64/include

keyboardshow.o: src/keyboardshow.cpp headers/keyboardshow.h
	g++ src/keyboardshow.cpp -c -o build/keyboardshow.o -I headers -I D:/Qt/5.14.2/5.14.2/mingw73_64/include