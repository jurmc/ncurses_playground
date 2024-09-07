#include<curses.h>

typedef struct win_border_struct {
    int ls, rs, ts, bs;
    int tl, tr, bl, br;
} WIN_BORDER;

typedef struct win_struct {
    int heigth, width;
    int beg_y, beg_x;
    WIN_BORDER border;
} WIN;

WIN int_win_params() {
    WIN win;

    win.heigth = 5;
    win.width = 10;
    win.beg_y = 1;
    win.beg_x = 2;

    win.border.ls = ACS_VLINE;
    win.border.rs = ACS_VLINE;
    win.border.ts = ACS_HLINE;
    win.border.bs = ACS_HLINE;

    win.border.tl = ACS_ULCORNER;
    win.border.tr = ACS_URCORNER;
    win.border.bl = ACS_LLCORNER;
    win.border.br = ACS_LRCORNER;

    return win;
}

void print_win_params() {
}

void draw_win(WIN *win, bool flag) {

    static WIN_BORDER b_off = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    WIN_BORDER* border = &win->border;

    if (!flag) {
    border = &b_off;
    }

    mvhline(win->beg_y, win->beg_x+1, border->ts, win->width-2);
    mvhline(win->beg_y + win->heigth -1, win->beg_x+1, border->bs, win->width-2);

    mvvline(win->beg_y+1, win->beg_x, border->ls, win->heigth-2);
    mvvline(win->beg_y+1, win->beg_x+ win->width - 1, border->rs, win->heigth-2);

    mvaddch(win->beg_y, win->beg_x, border->tl);
    mvaddch(win->beg_y, win->beg_x + win->width - 1, border->tr);
    mvaddch(win->beg_y + win->heigth - 1, win->beg_x, border->bl);
    mvaddch(win->beg_y + win->heigth - 1, win->beg_x + win->width - 1, border->br);
}


int main(int argc, char **argv) {
    int ch;
    int heigth = 5;
    int width = 12;

    initscr();
    start_color();
    cbreak();
    curs_set(0);
    init_pair(1, COLOR_CYAN, COLOR_BLACK);

    keypad(stdscr, TRUE);
    noecho();

    attron(COLOR_PAIR(1));
    printw("Press 'F1' to quit");
    attroff(COLOR_PAIR(1));
    refresh();

    WIN win = int_win_params();
    print_win_params(&win);
    draw_win(&win, TRUE);
    refresh();

    while ((ch = getch()) != KEY_F(1))
    {
        switch (ch)
        {
            case KEY_LEFT:
                draw_win(&win, FALSE);
                --win.beg_x;
                draw_win(&win, TRUE);
                break;
            case KEY_RIGHT:
                draw_win(&win, FALSE);
                ++win.beg_x;
                draw_win(&win, TRUE);
                break;
            case KEY_UP:
                draw_win(&win, FALSE);
                --win.beg_y;
                draw_win(&win, TRUE);
                break;
            case KEY_DOWN:
                draw_win(&win, FALSE);
                ++win.beg_y;
                draw_win(&win, TRUE);
                break;
        }
    }

    endwin();
    return 0;
}
