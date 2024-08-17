#include<stdio.h>
#include<ncurses.h>
#include<unistd.h>
#include<string.h>

int main()
{
    initscr();
    //raw();
    //timeout(0);
    keypad(stdscr, TRUE);
    noecho();

    char buff[255] = "buff content";

    while (0 != strncmp("quit", buff, 255)) {
        clear();
        mvprintw(0, 0, "getstr: [%s]", buff);
        getstr(buff);
        refresh();
        usleep(1000 * 100);
    }

    endwin();

    return 0;
}
