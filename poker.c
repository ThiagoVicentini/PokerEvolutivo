#include "poker.h"
#include "card.h"

void decideVencedor(Player *player, int *pool, Card *mesa){
  int indiceVencedor;
  int rankAux = 99999999;
  int tmp;

  printf("Cartas da mesa: \n");
  for(int i=0; i<5; i++)
    card_toString(mesa[i]);

  for(int i = 0; i < NUMPLAYERS; i++){
    if(player[i].folded) continue;
    
    tmp = evaluate_7cards(
    converter(player[i].hand.cards[0]),
    converter(player[i].hand.cards[1]),
    converter(mesa[0]),
    converter(mesa[1]),
    converter(mesa[2]),
    converter(mesa[3]),
    converter(mesa[4])
    );

  
    printf("\nJogador %d:\n", i);

    for(int j=0; j<2; j++)
      card_toString(player[i].hand.cards[j]);

    if(tmp < rankAux) {
      indiceVencedor = i;
      rankAux = tmp;
    }
  }

  printf("Jogador %d ganhou $%d!!!\n\n", indiceVencedor, *pool);
	player[indiceVencedor].money += *pool;
  *pool = 0;
}

void everyonePlay(Player *player, bool *everyonePlayed, int *numFolded, int *numFalido, int maxBet){
  (*everyonePlayed) = true;
  (*numFolded) = 0;
  (*numFalido) = 0;
  for(int i=0; i<NUMPLAYERS; i++){
    if(player[i].folded || player[i].money <= 0){
      if(player[i].money <= 0)
        (*numFalido)++;
      else
        (*numFolded)++;
      continue;
    }
    if(player[i].bet != maxBet)
      (*everyonePlayed) = false;
  }
}

void getBets(Player *player, int maxBet, int pool){
  printf("\n\nInformações do round:\n\n");
  
  for(int i=0; i<NUMPLAYERS; i++){
    printf("Bet jogador %d: $%d\n", i, player[i].bet);
  }
  printf("\n");
  for(int i=0; i<NUMPLAYERS; i++){
    printf("Fold jogador %d: %d\n", i, player[i].folded);
  }
  printf("MaxBet: $%d\n", maxBet);
  printf("Pool: $%d\n\n", pool);
}

void darDinheiroInicial(Player *players){
  for(int i=0; i<NUMPLAYERS; i++){
    players[i].money = 100;
  }
}