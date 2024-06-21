#include<nc_window.hpp>

#include<ncurses.h>

#include<unistd.h>
#include<assert.h>
#include<thread>
#include<signal.h>

#include<chrono>
#include<sstream>
#include<iomanip>
#include<string>

using namespace std;

static bool sigwinch = false;

static void sigwinch_handler(int sig) {
    if (SIGWINCH == sig) {
        sigwinch = true;
    }
}

string get_time()
{
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
    return ss.str();
}

int main()
{
    int w1 = 25;
    int w2 = 10;
    int h = 5;

    int w1_y = 0;
    int w1_x = 0;

    int w2_y = w1_y;
    int w2_x = w1_x + w1;

    Geometry::Point p1 = {w1_y, w1_x};
    Geometry::Size s1 = {h, w1};

    Geometry::Point p2 = {w2_y, w2_x};
    Geometry::Size s2 = {h, w2};

    NcWindow win1(p1, s1);
    NcWindow win2(p2, s2);

    initscr();
    raw();
    timeout(0);
    keypad(stdscr, TRUE);
    noecho();

    signal(SIGWINCH, sigwinch_handler);

    int ch = getch();

    int maxy, maxx;
    getmaxyx(stdscr, maxy, maxx);

    while ('q' != ch ) {
        if (true == sigwinch) {
            sigwinch = false;
            
            endwin(); 
            refresh();

            getmaxyx(stdscr, maxy, maxx);
        }

        win1.draw();
        win2.draw();

        auto time = get_time();
        mvprintw(5, 1, "last ch: ");
        addch(ch);
        mvprintw(6, 1, "sigwinch flag: ");
        addch(sigwinch == true ? '1' : '0');
        mvprintw(7, 1, "maxy: %d, maxx: %d", maxy, maxx);
        win1.add_line(time);

        refresh();
        std::this_thread::sleep_for(200ms) ;
        ch = getch();
    }

    endwin();

    return 0;
}
