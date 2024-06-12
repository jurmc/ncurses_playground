#include<ncurses.h>
#include<unistd.h>
#include<assert.h>

//      1  15 px     1    20 px      1
//      +------------+---------------+
// 2 px | Win1       |  Win2         |
//      +------------+---------------+

struct point_struct {
    int x;
    int y;
};
typedef point_struct point;

void draw_win(point p1, point p2) {
    mvaddch(p1.y, p1.x, ACS_ULCORNER);
    mvaddch(p1.y, p2.x, ACS_URCORNER);
    mvaddch(p2.y - 1, p1.x, ACS_LLCORNER);
    mvaddch(p2.y - 1, p2.x, ACS_LRCORNER);

    for ( int x = p1.x + 1; x < p2.x - 1; ++x ) {
        mvaddch(p1.y, x, ACS_HLINE);
        mvaddch(p2.y - 1, x,ACS_HLINE);
    }

    for ( int y = p1.y + 1; y < p2.y - 1; y++ ) {
        mvaddch(y, p1.x, ACS_VLINE);
        mvaddch(y, p2.x, ACS_VLINE);
    }
}

int main()
{
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();

    int w1 = 17;
    int w2 = 22;
    int h = 4;

    const int beg_x = 0;
    const int end_x = beg_x + w1;
    const int beg_y = 0;
    const int end_y = beg_y + h;

    point w1_p1 = {beg_x, beg_y};
    point w1_p2 = {end_x, end_y};
    draw_win(w1_p1, w1_p2);

    int w2_beg_x = end_x + 1;
    int w2_end_x = w2_beg_x + w2;

    point w2_p1 = {w2_beg_x, beg_y};
    point w2_p2 = {w2_end_x, end_y};
    draw_win(w2_p1, w2_p2);

    int ch = wgetch(stdscr);
    endwin();

    return 0;
}
