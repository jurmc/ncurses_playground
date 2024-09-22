extern crate ncurses;
extern crate core;

use ncurses::*;
use std::ffi::c_int;
use std::ffi::c_uint;

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
    fn drops_main(drops: *mut DropsStruct);
    fn dump_drop_data(y: c_int, drop: &DropStruct);
    fn dump_drops_data(len: c_int, drops: *const DropStruct);
    fn dump_drops_data2(s: *const DropsStruct);
    fn dump_array(drops: &DropsStruct);
}

fn drops_init(len: usize) -> Vec<DropStruct> {
    let mut retval = Vec::with_capacity(len);

    for i in 1..len {
        let d = DropStruct { x: i as i32, y: 0, live: false };
        retval.push(d);
    }

    retval
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
    let d3 = DropStruct{x: 5, y: 7, live: true};
    let d4 = DropStruct{x: 10, y: 14, live: false};
    unsafe {
        dump_drop_data(1, &d1);
        dump_drop_data(2, &d2);
    }
    let array: [DropStruct; 2] = [d1, d2];
    let array2: [DropStruct; 2] = [d3, d4];
    let mut y = 0;
    for item in array.iter() {
        let s = String::from("x: ");
        mvprintw(32+y, 20, format!("[Rust] x: {}, y: {}, live: {}", item.x, item.y, item.live).as_str()).unwrap();
        y += 1;
    }
    unsafe {
        dump_drops_data(2, array.as_ptr());
    }
    let drops = DropsStruct{
        len: 2,
        drops: array2.as_ptr()};
    unsafe {
        dump_drops_data2(&drops);
        std::mem::forget(drops);
    }
    /////

    let new_drops = drops_init(COLS() as usize);
    let mut drops = DropsStruct {
        len: new_drops.len() as c_int,
        drops: new_drops.as_ptr(),
    };
    unsafe {
        drops_main(&mut drops);
    }

    endwin();
}
