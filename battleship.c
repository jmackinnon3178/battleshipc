#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  short x;
  short y;
} Point;

typedef enum {
  up,
  down,
  left,
  right,
} orientation;

typedef enum {
  none,
  carrier,
  battleship,
  cruiser,
  submarine,
  destroyer,
} ship_t;

typedef struct {
  ship_t type;
  short size;
  Point bowPos;
  Point sternPos;
  bool sank;
  short hits;
  orientation orientation;
} Ship;

typedef struct {
  ship_t ship;
  bool hit;
} Tile;

typedef struct {
  Tile tiles[10][10];
} Board;

typedef struct {
  Ship carrier;
  Ship battleship;
  Ship cruiser;
  Ship submarine;
  Ship destroyer;
} Ships;

typedef struct {
  char *name;
  Board *board;
  Ships ships ;
} Player;

typedef struct {
  Player p1;
  Player p2;
  bool turn;
} Game;

Board* initBoard() {
  Board *b = malloc(sizeof(Board));
  
  if (b == NULL) {
    printf("error");
  }

  return b;
}

Player* initPlayer(char *name) {
  Player *p = malloc(sizeof(Player));
  if (p == NULL) {
    printf("error");
  }
  p->name = name;
  p->ships.carrier = (Ship){.type = carrier, .size = 5, .sank = false, .hits = 0};
  p->ships.battleship = (Ship){.type = battleship, .size = 4, .sank = false, .hits = 0};
  p->ships.cruiser = (Ship){.type = cruiser, .size = 3, .sank = false, .hits = 0};
  p->ships.submarine = (Ship){.type = submarine, .size = 3, .sank = false, .hits = 0};
  p->ships.destroyer = (Ship){.type = destroyer, .size = 3, .sank = false, .hits = 0};
  return p;
}

void assignBoard(Player *p, Board *b) {
  p->board = b;
}

Game* initGame(Player *p1, Player *p2) {
  Game *g = malloc(sizeof(Game));

  if (g == NULL) {
    printf("error");
  }

  g->p1 = *p1;
  g->p2 = *p2;
  g->turn = true;
  return g;
}

void printBoard(Board *b) {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      switch (b->tiles[i][j].ship) {
        case none:
          printf("*");
          break;
        case carrier:
          printf("1");
          break;
        case battleship:
          printf("2");
          break;
        case cruiser:
          printf("3");
          break;
        case submarine:
          printf("4");
          break;
        case destroyer:
          printf("5");
          break;
      }
    }
    printf("\n");
  }
}
