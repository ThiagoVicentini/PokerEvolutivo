#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "card.h"

#pragma once

typedef struct hand{
  Card cards[2];
  int topo; 
}Hand;

typedef struct player{
  Hand hand;
  int money;
  int bet;
  int aumentou;
  bool folded;
}Player;

void initPlayer(Player *player, int i);
void robotBet(Player* robot, int i, int *maxBet, int *pool);
void playerBet(Player* player, int i, int *maxBet, int *pool);
void addCard(Player *player, int i, Card card);