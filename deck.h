#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "card.h"

#pragma once

#define DECK_SIZE 52

typedef struct deck{
  Card cards[DECK_SIZE];
  int topCardIndex;
}Deck;

void initDeck(Deck *deck);
void deckFill(Deck *deck);
void dequeueCard(Deck *deck, Card *data);
void viraProximaCarta(Deck *deck, Card *mesa, int *i);
void shuffle(Deck *deck, int shuffles);
int swap_card(Deck *deck, int s, int t);
int converter(Card c);