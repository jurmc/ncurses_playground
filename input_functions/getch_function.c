#include<stdio.h>
#include<ncurses.h>
#include<unistd.h>

int main()
{
    initscr();
    //raw();
    //timeout(0);
    keypad(stdscr, TRUE);
    noecho();

    int maxy, maxx;
    getmaxyx(stdscr, maxy, maxx);

    mvprintw(0, 0, "getch: ");
    refresh();

    int ch;
    while ('q' != (ch = getch())) {
        if (ch == ERR) {
            usleep(1000 * 100);
            //sleep(1);
            continue;
        } else {
            clear();
            mvprintw(1, 0, "ch: %c (%d)", ch, ch);
            refresh();
        }
    }

    endwin();

    return 0;
}
