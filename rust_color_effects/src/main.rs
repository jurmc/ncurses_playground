extern crate ncurses;

use ncurses::*;
use std::{thread, time};
use rand::prelude::*;

#[derive(Copy, Clone)]
struct Coord {
    y: i32,
    x: i32,
}

struct DropStruct {
    tail: Vec<Coord>,
    live: bool,
}

fn drops_init(len: usize) -> Vec<DropStruct> {
    let mut retval = Vec::with_capacity(len);

    for i in 0..len {
        let d = DropStruct { tail: vec![Coord{y: 5, x: i as i32}], live: false };
        retval.push(d);
    }

    retval
}

fn spawn_drops(drops: &mut Vec<DropStruct>) {
    let len = drops.len();

    let empty_slots = drops.iter().filter(|item| item.live == false).count();

    if 0 == empty_slots {
        return;
    }

    let mut rng = thread_rng();
    let toss = rng.gen_range(0..empty_slots);
    mvprintw(1, 1, &format!("len: {}, toss: {}", len, toss));
    refresh();

    let tossed = drops.iter_mut().filter(|item| item.live == false).nth(toss).unwrap();
    tossed.live = true;

    //for (uint32_t i = 0; i < drops->len; i++) {
    //    if (false == drops->drops[i].live) {
    //        if (toss == 0) {
    //            drops->drops[i].live = true;
    //            break;
    //        }
    //        --toss;
    //    }
    //}

}

fn kick_drops(drops: &mut Vec<DropStruct>) {
    for d in drops.iter_mut() {
        let mut new_cell: Option<Coord> = None;
        if d.tail.len() < 7 {
            new_cell = Some(d.tail.iter().last().copied().unwrap());
        }
        for c in d.tail.iter_mut() {
            c.y += 1;
        }

        match new_cell {
            Some(nc) => d.tail.push(nc),
            _ => (),
        }
    }
}

fn print_drops(drops: &Vec<DropStruct>) {
    for d in drops.iter().filter(|drop| drop.live) {
        for (i, cell) in d.tail.iter().enumerate() {
            let col = i as i16 + 1;
            attron(COLOR_PAIR(col as i16));
            mvaddch(cell.y, cell.x, '.' as u32);
            attroff(COLOR_PAIR(col as i16));
        }
    }
}

fn main() {
    initscr();
    start_color();
    timeout(0);
    cbreak();
    noecho();
    curs_set(CURSOR_VISIBILITY::CURSOR_INVISIBLE);

    init_pair(1, COLOR_BLACK, COLOR_RED);
    init_pair(2, COLOR_BLACK, COLOR_GREEN);
    init_pair(3, COLOR_BLACK, COLOR_YELLOW);
    init_pair(4, COLOR_BLACK, COLOR_BLUE);
    init_pair(5, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(6, COLOR_BLACK, COLOR_CYAN);
    init_pair(7, COLOR_BLACK, COLOR_WHITE);
    init_pair(8, COLOR_WHITE, COLOR_BLACK);

    let mut drops = drops_init(COLS() as usize); // TODO: should be cols

    let sec = time::Duration::from_secs(1);
    let mut ch = getch();
    let q = 113 as i32;
    while ch != q {
        kick_drops(&mut drops);
        clear();
        print_drops(&drops);
        spawn_drops(&mut drops);
        refresh();

        thread::sleep(sec);
        ch = getch();
    }

    endwin();
}
