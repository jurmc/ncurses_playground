#include<ncurses.h>
#include<unistd.h>

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
    mvaddch(p1.y, p1.x, 'o');
    mvaddch(p2.y, p2.x, 'o');
}

int main()
{
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();

    int w1 = 15;
    int l2 = 20;
    int h = 2;

    mvaddch(0, 0, '+');
    for ( int x = 0; x <= w1; ++x ) {
        addch('-');
    }
    addch('+');

    int beg_y = 1;
    int end_y = beg_y + h;
    int r_border = 2+w1;
    for ( int y = beg_y; y < end_y; y++ ) {
        mvaddch(y, 0, '|');
        mvaddch(y, r_border, '|');
    }

    mvaddch(h+1, 0, '+');
    for ( int x = 0; x <= w1; ++x ) {
        addch('-');
    }
    addch('+');

    point p1 = {2, 2};
    point p2 = {4, 4};
    draw_win(p1, p2);

    int ch = wgetch(stdscr);
    endwin();

    return 0;
}
