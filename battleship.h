#ifndef battleship_h
#define battleship_h
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

Board* initBoard();

Player* initPlayer(char *name);

void assignBoard(Player *p, Board *b);

Game* initGame(Player *p1, Player *p2);

#endif
