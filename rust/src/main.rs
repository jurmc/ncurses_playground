extern crate ncurses;

use ncurses::*;

use std::{thread, time};

struct Point {
    y: i32,
    x: i32,
}

struct Size {
    h: i32,
    w: i32,
}

static SIGWINCH: bool = false;

fn main() {
    initscr();

    let mut y: i32 = 0;
    let mut x: i32 = 0;

    getmaxyx(stdscr(), &mut y, &mut x);

    let s: String = String::from(format!("y: {}, x: {}", y, x));
    addstr(&s).unwrap();
    refresh();
    let mut ch = getch();
    let mut cnt = 1;

    while 'q'.to_ascii_lowercase() as i32 != ch {
        let s = String::from(format!("s: {}", s));
        mvaddstr(2, 2, &s).unwrap();
        let s = String::from(format!("ch: {}", ch));
        mvaddstr(3, 2, &s).unwrap();
        let s = String::from(format!("q(ascii): {}", 'q'.to_ascii_lowercase() as u8));
        mvaddstr(4, 2, &s).unwrap();
        std::thread::sleep(time::Duration::from_millis(100));
        ch = getch();
    }

    endwin();
}
