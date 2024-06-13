extern crate ncurses;

use ncurses::*;

fn main() {
    initscr();
    addstr("Hello World!").unwrap();
    refresh();
    getch();
    endwin();
}
