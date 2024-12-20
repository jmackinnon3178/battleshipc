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


int main() {
  Board *b1 = initBoard();
  Board *b2 = initBoard();

  Player *p1 = initPlayer("bob");
  printf("%s\n", p1->name);
  printf("%hd\n", p1->ships.submarine.size);
  assignBoard(p1, b1);

  Player *p2 = initPlayer("bill");
  printf("%s\n", p2->name);
  printf("%hd\n", p2->ships.carrier.size);
  assignBoard(p2, b2);

  Game *game = initGame(p1, p2);

  b1->tiles[0][0].ship = carrier;
  b1->tiles[0][1].ship = carrier;
  b1->tiles[0][2].ship = carrier;
  b1->tiles[0][3].ship = carrier;
  b1->tiles[0][4].ship = carrier;


  printBoard(b1);

  free(b1);
  free(b2);
  free(p1);
  free(p2);
  free(game);

  return 0;
}


// orientation calcOri(Point bow, Point stern) {
//   orientation ori;
//   if (bow.y < stern.y) {
//     ori = up;
//   }
//   if (bow.y > stern.y) {
//     ori = down;
//   }
//   if (bow.x < stern.x) {
//     ori = left;
//   }
//   if (bow.x > stern.x) {
//     ori = right;
//   }
//   return ori;
// }
//
// bool validPlacement(Board board, Ship ship, orientation ori, Point bow,
//                     Point stern) {
//
//   switch (ori) {
//   case up:
//     if ((bow.y + ship.size - 1) != stern.y) {
//       printf("%hd", bow.y);
//       printf("%hd", stern.y);
//       printf("%hd", ship.size);
//       printf("here");
//       return false;
//     }
//     for (int i = bow.y; i > stern.y; i++) {
//       if (board.tiles[i][bow.x]->ship != none) {
// 					printf("here");
//         return false;
//       }
//     }
//   case down:
//       printf("%hd", bow.y);
//       printf("%hd", stern.y);
//       printf("%hd", ship.size);
//       printf("here");
//     if ((stern.y + ship.size) != bow.y) {
//       return false;
//     }
//     for (int i = stern.y; i > bow.y; i++) {
//       if (board.tiles[i][stern.x]->ship != none) {
//         return false;
//       }
//     }
//   case left:
//     if ((bow.x + ship.size) != stern.x) {
//       return false;
//     }
//     for (int i = bow.x; i > stern.x; i++) {
//       if (board.tiles[bow.y][i]->ship != none) {
//         return false;
//       }
//     }
//   case right:
//     if ((stern.x + ship.size) != bow.x) {
//       return false;
//     }
//     for (int i = stern.x; i > bow.x; i++) {
//       if (board.tiles[stern.y][i]->ship != none) {
//         return false;
//       }
//     }
//   }
//
//   return true;
// }
//
// int placeShip(Board *board, Ship *ship, Point bow, Point stern) {
//   orientation ori = calcOri(bow, stern);
//
//   if (!validPlacement(*board, *ship, ori, bow, stern)) {
//     return -1;
//   }
//
//   ship->orientation = ori;
//
//   switch (ori) {
//   case up:
//     for (int i = bow.y; i > stern.y; i++) {
//       board->tiles[i][bow.x]->ship = ship->type;
//     }
//   case down:
//     for (int i = stern.y; i > bow.y; i++) {
//       board->tiles[i][stern.x]->ship = ship->type;
//     }
//   case left:
//     for (int i = bow.x; i > stern.x; i++) {
//       board->tiles[bow.y][i]->ship = ship->type;
//     }
//   case right:
//     for (int i = stern.x; i > bow.x; i++) {
//       board->tiles[stern.y][i]->ship = ship->type;
//     }
//   }
//   return 0;
// }
//
// Tile *isHit(Board *b, Point p) {
//   if (b->tiles[p.y][p.x]->hit) {
//     return NULL;
//   }
//   if (b->tiles[p.y][p.x]->ship) {
//     return b->tiles[p.y][p.x];
//   }
//   return NULL;
// }
//
// void updateHits(Tile *tile, Ship *ship) {
//   ship->hits += 1;
//   tile->hit = true;
// }
//
// bool isSank(Ship *ship) {
//   if (ship->sank == true) {
//     return true;
//   }
//   if (ship->hits >= ship->size) {
//     ship->sank = true;
//   }
//   return false;
// }
