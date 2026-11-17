#ifndef CONSOLE_H
#define CONSOLE_H
#include <iostream>

#ifdef _WIN32
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
#endif

using namespace std;

namespace Ansi {
    inline constexpr char SEP = ';';
    inline constexpr char COLOR_CODE = 'm';
    inline constexpr char CURSOR_POS = 'H';
    inline constexpr string_view CSI = "\033[";
    inline constexpr string_view RESET_COLOR = "\033[0m";
    inline constexpr string_view CLEAR_SCREEN = "\033[2J\033[H";
};

enum class Color {
    Default = 0,
    Red     = 31,
    Green   = 32,
    Yellow  = 33,
    Blue    = 34,
    Magenta = 35,
    Cyan    = 36,
    White   = 37
};

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        cout << Ansi::CLEAR_SCREEN;
    #endif
}

void goToXY(int x, int y) {
    cout << Ansi::CSI << y << Ansi::SEP << x << Ansi::CURSOR_POS;
}

void setColor(Color color) {
    if (color == Color::Default)
        cout << Ansi::RESET_COLOR;
    else
        cout << Ansi::CSI << (int)(color) << Ansi::COLOR_CODE;
}

void printAt(int x, int y, const string& text, bool isSelected=false, Color color=Color::Default) {
    goToXY(x, y);
    if (isSelected) setColor(color);
    else setColor(Color::Default);
    cout << text;
    setColor(Color::Default);
    cout << endl;
}

#ifdef _WIN32

char getArrowKey() {
    char key = _getch();
    if (key == 0 || key == (char)0xE0) {
        switch (_getch()) {
            case 72: return 'A';  // up
            case 80: return 'B';  // down
            case 77: return 'C';  // right
            case 75: return 'D';  // left
            case 71: return 'H';  // home
            case 79: return 'F';  // end
        }
        return 0;
    }
    return key;
}

#else

char getch_linux(int vtime = 0) {
    char buf{};
    struct termios old = {};
    tcgetattr(0, &old);
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = (vtime == 0) ? 1 : 0;
    old.c_cc[VTIME] = vtime;
    tcsetattr(0, TCSANOW, &old);
    int n = read(0, &buf, 1);
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    tcsetattr(0, TCSADRAIN, &old);
    return (n > 0) ? buf : 0;
}

char getArrowKey() {
    char key = getch_linux();
    if (key == '\033') { // 27
        char nextByte = getch_linux(1);
        if (nextByte == 0) {
            return 27;
        }
        if (nextByte == '[') {
            return getch_linux(1);
        }
        return nextByte;
    }
    return key;
}
#endif

inline bool isEscPressed(char* input, int maxSize) {
    int i = 0;
    while (true) {
        char ch = getArrowKey();

        if (ch == 27) {
            return false;
        } 
        else if (ch == '\r' || ch == '\n') {
            input[i] = '\0';
            cout << endl;
            return true;
        } 
        else if (ch == '\b' || ch == 127) {
            if (i > 0) {
                i--;
                cout << "\b \b" << flush;
            }
        } 
        else if (i < maxSize - 1 && ch >= 32 && ch <= 126) {
            input[i++] = ch;
            cout << ch << flush;
        }
    }
}

#endif