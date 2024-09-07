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

void get_geometry_for_windows(int maxy, int maxx,
        Geometry::Point &p1,
        Geometry::Size  &s1,
        Geometry::Point &p2,
        Geometry::Size  &s2)
{
    int w1 = maxx / 2;
    int w2 = maxx / 4;
    int h = maxy - 3;

    int w1_y = 0;
    int w1_x = 0;

    int w2_y = w1_y;
    int w2_x = w1_x + w1;

    p1 = {w1_y, w1_x};
    s1 = {h, w1};

    p2 = {w2_y, w2_x};
    s2 = {h, w2};
}

int main()
{
    initscr();
    raw();
    timeout(0);
    keypad(stdscr, TRUE);
    noecho();

    int maxy, maxx;
    getmaxyx(stdscr, maxy, maxx);

    Geometry::Point p1, p2;
    Geometry::Size s1, s2;

    get_geometry_for_windows(maxy, maxx, p1, s1, p2, s2);

    NcWindow win1(p1, s1);
    NcWindow win2(p2, s2);

    signal(SIGWINCH, sigwinch_handler);

    int ch = getch();

    win1.draw();
    win2.draw();
    refresh();

    while ('q' != ch ) {
        if (true == sigwinch) {
            sigwinch = false;

            clear();
            endwin();
            refresh();

            getmaxyx(stdscr, maxy, maxx);
            get_geometry_for_windows(maxy, maxx, p1, s1, p2, s2);
            win1.update_geometry(p1, s1);
            win2.update_geometry(p1, s2);

            win1.draw();
            win2.draw();

            refresh();
        }

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
