#include<nc_window.hpp>

#include<ncurses.h>

#include<iostream>

using namespace std;

NcWindow::NcWindow(Point origin, Size size) : origin(origin), size(size), buff(vector<string>()) {};

void NcWindow::draw() {
    Point dest = {origin.y + size.height - 1, origin.x + size.width - 1};

    mvaddch(origin.y, origin.x, ACS_ULCORNER);
    mvaddch(origin.y, dest.x, ACS_URCORNER);
    mvaddch(dest.y, origin.x, ACS_LLCORNER);
    mvaddch(dest.y, dest.x, ACS_LRCORNER);

    for ( int x = origin.x + 1; x < dest.x; ++x ) {
        mvaddch(origin.y, x, ACS_HLINE);
        mvaddch(dest.y, x,ACS_HLINE);
    }

    for ( int y = origin.y + 1; y < dest.y; y++ ) {
        mvaddch(y, origin.x, ACS_VLINE);
        mvaddch(y, dest.x, ACS_VLINE);
    }
}

void NcWindow::add_line(string line) {
    buff.push_back(line);
    mvprintw(origin.y+1, origin.x+1, line.c_str());
}
