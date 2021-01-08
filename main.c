#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "poker.h"
#include "player.h"
#include "deck.h"
#include "card.h"
#include "evaluator7.h"  
// evaluate_7cards(converter(card1),converter(card2),converter(card3),converter(card4),...)
// retorna o rank dessa combinação de cartas, sendo que quanto menor o rank melhor a combinação

#define maxx 1000
#define tamPop 10

typedef struct ind{
  double coef[4];
}Ind;

float TaxMut = 1;
int mutCount = 0;
float delta = 1; 

double coefInd[4];          // Cromossomos
Ind populacao[tamPop];      // População
double fit[tamPop];         // Fitness
Ind bestInd;                // Melhor individuo
double maxFit;
int maxi;
int gen = 0;


void setVariables();
void finalizaRound();
void decisaoCromossomo(Ind individuo, Player* player, int *maxBet, int *pool,Card mesa[]);

Player players[4];
Deck deck;
Card tmpCard;
Card mesa[5];

bool ehUltimaCarta = false;
bool gameLoop = true;
bool newGame = true;
bool roundLoop = true;
bool everyonePlayed = false;
int pool=0, numFolded, numFalidos, maxBet=0;
int roundC=0, opcao=0;
int gameC=0;

void initPop(Ind *pop){
  for(int i=0; i<tamPop; i++)
    for(int j=0; j<4; j++)
      pop[i].coef[j] = (double) (rand() % maxx);
}

void avalie(Player player, int i){
	  fit[i] = player.money;
		printf("\tFitness %d: %f\n", i, fit[i]);
}

void selecionaEmuta(){
  maxFit = fit[0];
  maxi   = 0;

  for(int i=1; i<tamPop; i++){
    if(fit[i] > maxFit){
      maxFit = fit[i];
      maxi   = i;
    }
  }

  for(int i=1; i<tamPop; i++){
    if (i == maxi)        // Protege o melhor individuo
      continue;
    int dist=0;
    for(int j=0; j<4; j++){
      populacao[i].coef[j] = (populacao[i].coef[j] + populacao[maxi].coef[j])/ 2.0;
    
      // Mutacao variada
      if(fit[i-1] - fit[i] < delta)
        mutCount++;
      else
        mutCount = 0;
      if(mutCount > 10)
        TaxMut /= 10;
      else if(mutCount > 20)
        TaxMut /= 10;
      else if(mutCount > 30)
        TaxMut *= 1000;
      else if(mutCount > 31)
        TaxMut *= 40;
      else if(mutCount > 90)
        TaxMut = 1; // original

      // Chance de mutação diminui para cada gene mutado
      int muta = rand()%(2+dist);
      if(muta==0){
        dist++;
        populacao[i].coef[j] += populacao[i].coef[j]*TaxMut/100.0f;
      }
    } // Fim do for
    if(dist == 0){ // Se não mutou nenhum gene escolhe um aleatrio pra mutar
      int muta = rand()%(4);
      populacao[i].coef[muta] += populacao[i].coef[muta]*TaxMut/100.0f;
    }
  }
}

void game(int k){
  darDinheiroInicial(players);
  while(gameLoop){
    printf("\n\nNovo jogo começando!\n\n");
    setVariables();  

    for(int i=0; i<NUMPLAYERS; i++)
      for(int j=0; j<HAND_SIZE; j++)
        if(players[i].money > 0 && deck.topCardIndex > 0){
          dequeueCard(&deck, &tmpCard);
          addCard(players, i, tmpCard);
        }
    card_toString(players[0].hand.cards[0]);
    card_toString(players[0].hand.cards[1]);

    while(roundLoop){
      if(roundC == 6) ehUltimaCarta = true;
      while(!everyonePlayed){
        printf("O caixa tem: %d\n", pool);
        if(numFalidos==NUMPLAYERS-numFolded || numFolded == NUMPLAYERS-1 || numFalidos+numFolded == NUMPLAYERS-1)
          break;
        printf("\n\n%d\n\n", roundC);
        for(int i=0; i<NUMPLAYERS; i++){
          printf("Jogador %d jogando:\n", i);
          if(!players[i].folded && players[i].money > 0){
            if(i == HUMANPLAYER){        
              //decisaoCromossomo(populacao[k], players, &maxBet, &pool, mesa);
              playerBet(players, i, &maxBet, &pool);
            }else{
              robotBet(players, i, &maxBet, &pool);  // precisa alterar dps
            }
          }else if(players[i].folded){
            printf("Jogador %d fugiu!\n", i);
          }else{
            printf("Jogador %d faliu!\n", i);
          }
        }
        getBets(players, maxBet, pool);
        everyonePlay(players, &everyonePlayed, &numFolded, &numFalidos, maxBet);
      }

      if(numFolded == NUMPLAYERS-1){ // Todos jogadores fugiram
        for(int i=0; i<NUMPLAYERS; i++){
          if(!players[i].folded){
            printf("Todos fugiram exceto pelo Jogador %d!\n", i);
            printf("Jogador %d ganhou $%d!!!\n", i, pool);
            players[i].money += pool; 
            roundLoop = false;
          }
        }
      }else{
        if(numFalidos == NUMPLAYERS-numFolded){
          for(int i=roundC; i<5; i++)
            viraProximaCarta(&deck, mesa, &roundC);
          decideVencedor(players, &pool, mesa);
          roundLoop = false;
          break;
        }
        if(ehUltimaCarta){
          decideVencedor(players, &pool, mesa);
          roundLoop = false;
        }else{
          for(int i=0; i<5; i++)
            viraProximaCarta(&deck, mesa, &roundC);
          printf("Cartas da mesa: \n");
          for(int i=0; i<5; i++)
            card_toString(mesa[i]);
        }
      }
      finalizaRound();
    }
    
    gameC++;
    if(gameC == 5){ // Sexta partida encerra a geração
      gameLoop = false;
      gameC=0;
    }
  }
  printf("\n-----------------------\n");
  for(int i=0; i<NUMPLAYERS; i++){
    printf("Money Jogador %d: $%d\n", i, players[i].money);
  }
  printf("-----------------------\n");
  avalie(players[1], k);
}


int main(void) {
  printf("==== Bem vindo ao Poker evolutivo! ====\n\n");
  srand(time(NULL));
  initPop(populacao);
  scanf("%*c");
  while(true){
    printf("Generation %d\n", gen);
    for(int i=0; i<tamPop; i++){
      game(i); // Chama a função de avaliação para o ind i no final
      setVariables();
      gameLoop = true;
      scanf("%*c");
    }
    selecionaEmuta();
    gen++;
  }
  printf("Fim!\n");
  return 0;
}

void setVariables(){
  newGame = true;
  roundLoop = true;

  ehUltimaCarta = false;
  everyonePlayed = false;

  pool=0;
  maxBet=0;

  numFolded=0;
  numFalidos=0;
  
  roundC=0;
  
  initDeck(&deck);
  deckFill(&deck);
  shuffle(&deck, 2000);
  for(int i = 0; i < 5; i++){
    mesa[i].suit = -1;
    mesa[i].rank = -1;  
  }
  for(int i=0; i < NUMPLAYERS; i++)
    initPlayer(players, i);
} 

void finalizaRound(){
  everyonePlayed = false;
  maxBet = 0;
  roundC++;
  for(int i=0; i<NUMPLAYERS; i++)
    players[i].bet = 0;
}

void decisaoCromossomo(Ind individuo, Player* player, int *maxBet, int *pool, Card mesa[]){
  //    cartas
  if(mesa[0].suit == -1){
    if((*maxBet) > player[0].bet){
        int bet = (*maxBet)-player[0].bet;
        player[0].bet += bet;
        player[0].money -= bet;
        *pool += bet;
    }
  }else{
      int valor = individuo.coef[0]*evaluate_7cards(
      converter(player[0].hand.cards[0]), 
      converter(player[0].hand.cards[1]), 
      converter(mesa[0]), converter(mesa[1]), 
      converter(mesa[2]), converter(mesa[3]), 
      converter (mesa[4]));
    if(valor > individuo.coef[1]){
        player[0].folded = true;
    }
    else{
      if((*maxBet) > player[0].bet){
        int bet = (*maxBet)-player[0].bet;
        player[0].bet += bet;
        player[0].money -= bet;
        *pool += bet;
      }
      else{
        if(valor < individuo.coef[2]){
          int bet = (int) individuo.coef[3];
          if(bet > player[0].money){
            bet = player[0].money;
          }
          player[0].bet += bet;
          player[0].money -= bet;
          if(player[0].bet > *maxBet){
            (*maxBet) = player[0].bet;
          }
          *pool += bet;        
        }
      }
    }
  }
}

