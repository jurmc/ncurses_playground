#include<stdio.h>
#include<stdlib.h>
#include<ncurses.h>

/* Copyleft: Michal Jurek */

int main(int argc, char **argv) {
    if (2 != argc) {
        printf("Usage: %s filename\n", argv[0]);
        exit(1);
    }

    FILE *fp = fopen(argv[1], "r");
    if (NULL == fp) {
        printf("Cannot open file: %s\n", argv[1]);
        exit(1);
    }

    int maxy, maxx;
    int y, x;

    initscr();
    getmaxyx(stdscr, maxy, maxx);

    /* Main loop */
    char ch, prev;
    while (EOF != (ch = fgetc(fp))) {
            getyx(stdscr, y, x);
            if (y == maxy-1) {
                mvprintw(maxy-1, 0, "<-Press-any-key->");
                refresh();
                getch();
                clear();
                move(0, 0);
            }

            if ('/' == prev && '*' == ch) {
                attron(A_REVERSE);
                mvaddch(y, x-1, prev);
            }

            addch(ch);

            if ('*' == prev && '/' == ch) {
                attroff(A_REVERSE);
            }

            refresh();
            prev = ch;
    }

    mvprintw(maxy-1, 0, "<-End-of-buffer--Press-any-key->");
    refresh();
    getch();

    fclose(fp);
    return 0;
}
