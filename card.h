#include <stdio.h>

#pragma once

typedef struct card{
  int rank;
  int suit;
}Card;

void cardInit(Card* card, int i, int rank, int suit);
int card_toString(Card card);