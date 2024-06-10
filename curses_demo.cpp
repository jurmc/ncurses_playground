#include<ncurses.h>
#include<unistd.h>

int main()
{
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();

    wprintw(stdscr, "Type any character to see it in bold\n");
    int ch = wgetch(stdscr);

    if (ch == KEY_F(1)) {
        wprintw(stdscr, "F1 Key pressed");
    } else {
        wprintw(stdscr, "The pressed key is ");
        attron(A_BOLD);
        printw("%c", ch);
        attroff(A_BOLD);
    }

    wrefresh(stdscr);
    getch();
    endwin();

    return 0;
}
