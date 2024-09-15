extern crate ncurses;
extern crate core;

use ncurses::*;

extern "C" {
    fn drops_main();
}

fn main() {
    initscr();
    start_color();
    timeout(0);
    cbreak();
    noecho();
    curs_set(CURSOR_VISIBILITY::CURSOR_INVISIBLE);

    unsafe {
        drops_main();
    }

    endwin();
}
