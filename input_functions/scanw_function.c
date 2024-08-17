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

    char str_buff[255] = "buff content";
    int int_buff = 666;

    while (0 != strncmp("quit", str_buff, 255)) {
        clear();
        mvprintw(0, 0, "scanw: [s: %s], [i: %d]", str_buff, int_buff);
        scanw("%s %d", str_buff, &int_buff);
        refresh();
        usleep(1000 * 100);
    }

    endwin();

    return 0;
}
