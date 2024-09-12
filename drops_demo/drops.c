#include"drops.h"
#include"get_rand.h"

#include<unistd.h>
#include<stdlib.h>
#include<curses.h>

drops_t* drops_init(uint32_t len) {
    drops_t *drops = malloc(sizeof(drop_t) + len * sizeof(drop_t));

    drops->len = len;
    for (int i = 0; i < len; ++i) {
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

void kick_drops(drops_t *drops) {
}

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

