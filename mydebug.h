#ifndef MYDEBUG_H
#define MYDEBUG_H

#include <chrono>
#include <iostream>
#ifdef __WINNT
#include <windows.h>
enum ConsoleColor
{
        Black         = 0,
        Blue          = 1,
        Green         = 2,
        Cyan          = 3,
        Red           = 4,
        Magenta       = 5,
        Brown         = 6,
        LightGray     = 7,
        DarkGray      = 8,
        LightBlue     = 9,
        LightGreen    = 10,
        LightCyan     = 11,
        LightRed      = 12,
        LightMagenta  = 13,
        Yellow        = 14,
        White         = 15
};
#else
enum ConsoleColor
{};
#endif

class myDebug;
class SingletonDestroyer
{
  private:
    myDebug* p_instance;
  public:
    ~SingletonDestroyer();
    void initialize( myDebug* p );
};

class myDebug
{
private:
    static myDebug *p_instance;
    static SingletonDestroyer destroyer;
    static std::chrono::steady_clock::time_point start;
    static std::chrono::steady_clock::time_point end;
    static int _x;
    static int startLine;
    static int endLine;
    static double allTime;
#ifdef __WINNT
    static WORD consoleMode;
    static void SetColor(ConsoleColor text, ConsoleColor background = Black);
    static void ressetStyle();
#endif

protected:
    myDebug( const myDebug& );
    myDebug &operator = ( myDebug& );
    myDebug();
   ~myDebug();
    friend class SingletonDestroyer;

public:
    void startPoint();
    void endPoint();
    double getLastTime() const;
    static myDebug *getInstance(int x = 0);
    template <typename T>
    static void outTrace(int l, T x)
    {
        end = std::chrono::steady_clock::now();
#ifdef __WINNT
        SetColor(Blue);
#endif
        std::cout << "<---TRACE " << l << " line. Value is: " << x << std::endl;
#ifdef __WINNT
        ressetStyle();
#endif
        start = std::chrono::steady_clock::now();
    }
};

#define debug myDebug::getInstance(__LINE__)
#define trace(x) myDebug::outTrace(__LINE__, x)


#endif // MYDEBUG_H
