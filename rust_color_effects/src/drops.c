#include"drops.h"
#include"get_rand.h"

#include<unistd.h>
#include<stdlib.h>
#include<curses.h>


//////////////////
void dump_drop_data(int y, drop_t *drop) {
    mvprintw(20+y, 15, "[C] dump_drop_data: x: %i, y: %i, live: %b", drop->x, drop->y, drop->live);
}
void dump_drops_data(int len, drop_t *drops) {
    mvprintw(26, 15, "dump_drops_data: len: %i", len);
    for (int i = 0; i < len; ++i) {
        mvprintw(27+i, 17, "drop_data[%i]: x: %i, y: %i", i, drops[i].x, drops[i].y);
    }
}
//////////////////
drops_t* drops_init(uint32_t len) {
    drops_t *drops = malloc(sizeof(drop_t) + len * sizeof(drop_t));

    drops->len = len;
    for (uint32_t i = 0; i < len; ++i) {
        drops->drops[i].live = false;
        drops->drops[i].y = 0;
        drops->drops[i].x = i;
    }

    return drops;
}

void drops_destroy(drops_t *drops) {
free(drops);
}

void _spawn_drops(drops_t *drops);
void _kick_drops(drops_t *drops);
void _print_drops(drops_t *drops);

void process_drops(drops_t *drops) {
    _spawn_drops(drops);
    _kick_drops(drops);
//    _clean_drops(drops);
    _print_drops(drops);
}

/* one drop */
void _kick_drop(drop_t *drop);
void _print_drop(drop_t *drop);
/* one drop */

void _spawn_drops(drops_t *drops) {
    uint32_t empty_slots = 0;
    for (uint32_t i = 0; i < drops->len; ++i) {
        if (false == drops->drops[i].live) {
            ++empty_slots;
        }
    }

    if (0 == empty_slots) {
        return;
    }

    uint32_t toss = get_rand(empty_slots);

    for (uint32_t i = 0; i < drops->len; i++) {
        if (false == drops->drops[i].live) {
            if (toss == 0) {
                drops->drops[i].live = true;
                break;
            }
            --toss;
        }
    }
}

void _kick_drops(drops_t *drops) {
    for (uint32_t i = 0; i < drops->len; i++) {
        if (true == drops->drops[i].live) {
            _kick_drop(&(drops->drops[i]));
        }
    }
}

void _print_drops(drops_t *drops) {
    for (uint32_t i = 0; i < drops->len; i++) {
        if (true == drops->drops[i].live) {
            _print_drop(&drops->drops[i]);
        }
    }
}

void _kick_drop(drop_t *drop) {
    ++drop->y;

    if (LINES + 7 < drop->y) {
        drop->live = false;
    }
}

void _print_drop(drop_t *drop) {
    int col = 1;
    for (int i=drop->y; i>=0; --i) {
        attron(COLOR_PAIR(col));
        mvaddch(i, drop->x, ' ');
        attroff(COLOR_PAIR(col));
        ++col;
        if (col > 8) {
            break;
        }
    }
}

int drops_main() {
    init_pair(1, COLOR_BLACK, COLOR_RED);
    init_pair(2, COLOR_BLACK, COLOR_GREEN);
    init_pair(3, COLOR_BLACK, COLOR_YELLOW);
    init_pair(4, COLOR_BLACK, COLOR_BLUE);
    init_pair(5, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(6, COLOR_BLACK, COLOR_CYAN);
    init_pair(7, COLOR_BLACK, COLOR_WHITE);
    init_pair(8, COLOR_WHITE, COLOR_BLACK);

    drops_t *drops = drops_init(COLS);

    int cnt = 0;
    int ch;
    bool stop = false;
    int usleep_time = 1000 * 100;
    while ((ch = getch()) != 'q')
    {
        if (ch == 's') {
            stop = stop ? false : true;
        }

        if (stop == true) {
            usleep(usleep_time);
            continue;
        }

        mvprintw(LINES-1, 0, "cnt: %d", cnt++);
        process_drops(drops);
        refresh();
        usleep(usleep_time);
    }

    drops_destroy(drops);

    return 0;

}
