#ifndef COLOROUT_H
#define COLOROUT_H

#ifdef _WIN32
#define ALLOW_COLOR
#elif __linux__
#define ALLOW_COLOR
#endif

#ifdef ALLOW_COLOR
#ifdef _WIN32
    #include <windows.h>
    #define FOREGROUND_YELLOW (FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY)
    #define FOREGROUND_WHITE (FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY)
    void color(int color){
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(handle, color);
    }
#else
    #define FOREGROUND_WHITE "\033[0m"
    #define FOREGROUND_RED "\033[0;31m"
    #define FOREGROUND_YELLOW "\033[0;33m"
    void color(const char* color){
        cout << color;
    }
#endif
#else
    #define FOREGROUND_WHITE 1
    #define FOREGROUND_RED 1
    #define FOREGROUND_YELLOW 1
    void color(int){}
#endif
#endif // COLOROUT_H
