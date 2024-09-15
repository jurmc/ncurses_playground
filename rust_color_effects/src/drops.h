#include<stdbool.h>
#include<stdint.h>

typedef struct drop_struct {
    int x;
    int y;
    bool live;
} drop_t;

typedef struct drops_struct {
    uint32_t len;
    drop_t drops[];
} drops_t;

////
void dump_drop_data(drop_t *drop);
void dump_drops_data(drops_t *drops);
////
int drops_main();

drops_t* drops_init(uint32_t len);
void drops_destroy(drops_t *drops);

void process_drops(drops_t *drops);


