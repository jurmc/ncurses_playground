extern crate ncurses;
extern crate core;

use ncurses::*;
use std::ffi::c_int;

#[repr(C)]
pub struct DropStruct {
    x: c_int,
    y: c_int,
    live: bool,
}

#[repr(C)]
pub struct DropsStruct {
    len: c_int,
    drops: *const DropStruct,
}

extern "C" {
    fn drops_main();
    fn dump_drop_data(drop: &DropStruct);
    fn dump_drops_data(drops: &DropsStruct);
}

fn main() {
    initscr();
    start_color();
    timeout(0);
    cbreak();
    noecho();
    curs_set(CURSOR_VISIBILITY::CURSOR_INVISIBLE);

    /////
    let d1 = DropStruct{x: 5, y: 7, live: true};
    let d2 = DropStruct{x: 10, y: 14, live: false};
    let array = [d1, d2];
    let mut y = 0;
    for item in array.iter() {
        let s = String::from("x: ");
        mvprintw(32+y, 20, format!("x: {}, y: {}", item.x, item.y).as_str()).unwrap();
        y += 1;
    }
    let drops = DropsStruct{len: array.len() as i32, drops: array.as_ptr() as *const DropStruct};
    /////


    unsafe {
        let drop = DropStruct{x: 5, y: 7, live: true};
        dump_drop_data(&drop);
        dump_drops_data(&drops);
        drops_main();
    }

    endwin();
}
