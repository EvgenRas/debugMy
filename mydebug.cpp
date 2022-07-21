#include "mydebug.h"

int myDebug::_x = 0;
int myDebug::startLine = 0;
int myDebug::endLine = 0;
double myDebug::allTime = 0;
std::chrono::steady_clock::time_point myDebug::start = std::chrono::steady_clock::now();
std::chrono::steady_clock::time_point myDebug::end = std::chrono::steady_clock::now();
myDebug *myDebug::p_instance = nullptr;
#ifdef __WINNT
    WORD myDebug::consoleMode = 0;
#endif
SingletonDestroyer myDebug::destroyer;

SingletonDestroyer::~SingletonDestroyer() {
    delete p_instance;
}
void SingletonDestroyer::initialize( myDebug *p ) {
    p_instance = p;
}

void myDebug::startPoint()
{
    startLine = _x;
    end = std::chrono::steady_clock::now();
    start = std::chrono::steady_clock::now();
}

void myDebug::endPoint()
{
    endLine = _x;
    end = std::chrono::steady_clock::now();
    allTime +=  getLastTime();
#ifdef __WINNT
    SetColor(Red);
#endif
    std::cout << "<---Block " << startLine << " - " << endLine << " lines:";
    std::cout << "Time has passed: " << getLastTime() << " ms" << std::endl;
#ifdef __WINNT
    ressetStyle();
#endif
    start = std::chrono::steady_clock::now();
}

double myDebug::getLastTime() const
{
    return static_cast<double>(std::chrono::duration <double, std::milli> (end - start).count());
}

myDebug *myDebug::getInstance(int x)
{
    _x = x;
    if(!p_instance)
    {
        p_instance = new myDebug();
        destroyer.initialize( p_instance);
    }
    return p_instance;
}
#ifdef __WINNT
void myDebug::SetColor(ConsoleColor text, ConsoleColor background)
{
    HANDLE handleOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbInfo;
    GetConsoleScreenBufferInfo(handleOut, &csbInfo);
    consoleMode = csbInfo.wAttributes;
    SetConsoleTextAttribute(handleOut, static_cast<WORD>((background << 4) | text));

}

void myDebug::ressetStyle()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), consoleMode);
}
#endif

myDebug::myDebug()
{
}

myDebug::~myDebug()
{
    end = std::chrono::steady_clock::now();
    allTime +=  getLastTime();
#ifdef __WINNT
    SetColor(Green);
#endif
    std::cout << "\nProgram is ended. Time has passed: " << allTime << " ms.\n" << std::endl;
#ifdef __WINNT
    ressetStyle();
#endif
}
