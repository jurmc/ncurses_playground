extern crate ncurses;
extern crate core;

use ncurses::*;
use core::ffi::c_int;

extern "C" {
    fn multiply(a: c_int, b: c_int) -> c_int;
    fn drops_main();
}

use std::{time};

fn main() {
    initscr();

    let mut y: i32 = 0;
    let mut x: i32 = 0;

    getmaxyx(stdscr(), &mut y, &mut x);

    let s: String = String::from(format!("y: {}, x: {}", y, x));
    addstr(&s).unwrap();
    refresh();
    let mut ch = getch();

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

    unsafe {
        drops_main();
    }

    println!("[Rust] Hello from Rust:  🦀\n");
    unsafe {
        let result = multiply(4, 5);
        println!("[Rust] Result: {}\n", result);
    }

}
