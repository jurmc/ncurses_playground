#include"drops.h"

#include<unistd.h>
#include<stdlib.h>
#include<curses.h>

int main()
{
    initscr();
    start_color();
    timeout(0);
    cbreak();
    noecho();
    curs_set(0);

    init_pair(1, COLOR_BLACK, COLOR_RED);
    init_pair(2, COLOR_BLACK, COLOR_GREEN);
    init_pair(3, COLOR_BLACK, COLOR_YELLOW);
    init_pair(4, COLOR_BLACK, COLOR_BLUE);
    init_pair(5, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(6, COLOR_BLACK, COLOR_CYAN);
    init_pair(7, COLOR_BLACK, COLOR_WHITE);
    init_pair(8, COLOR_WHITE, COLOR_BLACK);

    drops_t *drops = drops_init(COLS);

    int cnt = 0;
    int ch;
    bool stop = false;
    int usleep_time = 1000 * 100;
    while ((ch = getch()) != 'q')
    {
        if (ch == 's') {
            stop = stop ? false : true;
        }

        if (stop == true) {
            usleep(usleep_time);
            continue;
        }

        mvprintw(LINES-1, 0, "cnt: %d", cnt++);
        process_drops(drops);
        refresh();
        usleep(usleep_time);
    }

    drops_destroy(drops);
    refresh();
    endwin();

    return 0;
}
