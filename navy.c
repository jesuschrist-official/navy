#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


enum boat_type {
        BOAT_DESTROYER,
        BOAT_CRUISER,
        BOAT_BATTLESHIP,
        BOAT_CARRIER,
        BOAT_MAX,
};


int boat_sizes[BOAT_MAX] = {
        2, 3, 4, 5
};


struct boat {
        enum boat_type type;
        int x1, y1;
        int x2, y2;
};


#define MAX_BOATS       5
struct game {
        size_t nboats;
        struct boat boats[MAX_BOATS];
        int grid[10][10];
};


int boat_init(struct game* g, enum boat_type type, int x, int y, bool vert, int boat)
{
        int size = boat_sizes[type];
        int x2 = vert ? x : x + size;
        int y2 = vert ? y + size : y;
        if (x < 0 || y < 0 || x2 > 9 || y2 > 9) {
                return 0;
        }
        int xstep = x < x2;
        int ystep = y < y2;
        for (int i = 0; i < size; i++) {
                if (g->grid[y + i * ystep][x + i * xstep] != -1) {
                        return 0;
                }
        }
        for (int i = 0; i < size; i++) {
                g->grid[y + i * ystep][x + i * xstep] = boat;
        }
        g->boats[boat] = (struct boat){
                .type = type,
                .x1 = x, .x2 = x2,
                .y1 = y, .y2 = y2,
        };
        return 1;
}


void game_init(struct game* g) {
        for (int y = 0; y < 10; y++) {
                for (int x = 0; x < 10; x++) {
                        g->grid[y][x] = -1;
                }
        }

        enum boat_type types[5] = {
                BOAT_DESTROYER, BOAT_CRUISER, BOAT_CRUISER, BOAT_BATTLESHIP, BOAT_CARRIER
        };
        int curtype = 0;
        while (curtype < 5) {
                int x = rand() % 10;
                int y = rand() % 10;
                bool vert = rand() % 2;
                if (boat_init(g, types[curtype], x, y, vert, curtype)) {
                        curtype++;
                }
        }
}


void game_print(const struct game* g) {
        for (int x = 0; x < 10; x++) {
                printf("%d ", x);
        }
        printf("\n");
        for (int y = 0; y < 10; y++) {
                for (int x = 0; x < 10; x++) {
                        if (g->grid[y][x] != -1) {
                                printf("%d ", g->grid[y][x]);
                        } else {
                                printf("  ");
                        }
                }
                printf("%d\n", y);
        }
}


int main(int argc, char** argv) {
        srand(time(NULL));

        struct game g = {0};
        game_init(&g);
        game_print(&g);

        return 0;
}
