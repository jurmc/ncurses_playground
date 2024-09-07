#include<curses.h>

WINDOW *draw_window(int heigth, int width, int start_y, int start_x) {
    WINDOW *win = newwin(heigth, width ,start_y, start_x);
    box(win, ACS_VLINE, ACS_HLINE);
    wrefresh(win);
    return win;
}

void destroy_win(WINDOW *win) {
    wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(win);
    delwin(win);
}

int main(int argc, char **argv) {
    int ch;
    int heigth = 5;
    int width = 12;

    initscr();
    cbreak();
    curs_set(0);

    int start_y = LINES / 2 - heigth / 2;
    int start_x = COLS / 2 - width / 2;

    keypad(stdscr, TRUE); /* I need that nifty F1 */
    refresh();
    noecho();

    printw("Press 'F1' to quit");
    WINDOW *win = draw_window(heigth, width, start_y, start_x);

    while ((ch = getch()) != KEY_F(1))
    {
        switch (ch)
        {
            case KEY_LEFT:
                --start_x;
                break;
            case KEY_RIGHT:
                ++start_x;
                break;
            case KEY_UP:
                --start_y;
                break;
            case KEY_DOWN:
                ++start_y;
                break;
        }

        destroy_win(win);
        win = draw_window(heigth, width, start_y, start_x);
    }

    endwin();
    return 0;
}
