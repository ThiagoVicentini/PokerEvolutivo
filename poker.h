#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "player.h"
#include "card.h"
#include "deck.h"
#include "evaluator7.h"  

#pragma once

#define HAND_SIZE 2
#define NUMPLAYERS 4
#define HUMANPLAYER 0

void decideVencedor(Player *player, int *pool, Card *mesa);
void everyonePlay(Player *player, bool *everyonePlayed, int *numFolded, int *numFalido, int maxBet);
void getBets(Player *player, int maxBet, int pool);
void darDinheiroInicial(Player *players);