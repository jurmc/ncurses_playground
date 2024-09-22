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

#[repr(C)]
pub struct SomeStruct {
    size: usize,
    fields: *mut c_int,
}


extern "C" {
    fn drops_main(drops: *mut DropsStruct);
    fn dump_drop_data(y: c_int, drop: &DropStruct);
    fn dump_drops_data(len: c_int, drops: *const DropStruct);
    fn dump_drops_data2(s: *const DropsStruct);
    fn dump_array(drops: &DropsStruct);

    fn dump_c_array(arr: *const SomeStruct);
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
    }
    /////

    unsafe {
        let d1 = DropStruct{x: 5, y: 5, live: true};
        let d2 = DropStruct{x: 6, y: 6, live: true};
        let drops_vec = vec![d1, d2];
        let mut drops = DropsStruct {
            len: drops_vec.len() as c_int,
            drops: drops_vec.as_ptr(),
        };
        drops_main(&mut drops);
    }

    endwin();

    let mut arr: [c_int; 8] = [1, 2, 3, 4, 5, 6, 7, 8];
    let mut some_struct = SomeStruct {
        size: 8,
        fields: arr.as_mut_ptr(),
    };
    unsafe {
        dump_c_array(&some_struct);
    }
}
