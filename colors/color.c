#include<curses.h>
#include<unistd.h>

int main()
{
    initscr();
    start_color();
    cbreak();
    noecho();
    curs_set(0);

    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_BLACK);
    init_pair(8, COLOR_BLACK, COLOR_WHITE);

    for (int col = 1; col <= 8; ++col) {
        attron(COLOR_PAIR(col));
        printw("Color test\n");
        attroff(COLOR_PAIR(col));
    }

    refresh();
    getch();
    endwin();

    return 0;
}
