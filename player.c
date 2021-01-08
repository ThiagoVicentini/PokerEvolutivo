#include "player.h"

void robotBet(Player* robot, int i, int *maxBet, int *pool){
  //Tomar decisão (Aumentar: 0, Check: 1, Fugir: 2)
  int rd;
  while(true){
    if(robot[i].aumentou){
      rd = 1;
    }
    else{
      if(robot[i].bet != *maxBet){ // ou ele aumenta '0' ou foge '2'
        if(*maxBet > robot[i].money)  
          rd = 2;
        else{
          //
          if(robot[i].hand.cards[0].suit == robot[i].hand.cards[1].suit || 
            robot[i].hand.cards[0].rank == robot[i].hand.cards[1].rank){
              rd = 0;
          }
          else{
            rd = rand()%3;
            if(rd == 1)  
              rd = 0;
          }  
        }    
      } else{                     // ou ele aumenta '0'  ou mantem '1'
        if(robot[i].hand.cards[0].suit == robot[i].hand.cards[1].suit || 
          robot[i].hand.cards[0].rank == robot[i].hand.cards[1].rank){
            rd = rand()%3;
            if(rd == 2)  
              rd = 0;
        }
        else{
          rd = rand()%3;
          if(rd == 2)  
            rd = 1;
        }
      }
    }
    if(rd == 0){ // Aumenta
      int bet;
      if(robot[i].bet != *maxBet)
        bet = *maxBet - robot[i].bet;
      else{
        if(!(robot[i].money/2))
          bet = rand()%(robot[i].money/2);    
        else rd = 1;
        robot[i].aumentou = 1; 
        for(int j = 1; j < 4; j++){
          if(i == j)  continue;
          robot[j].aumentou = 0;
        }
      }
      if(rd == 0){
        printf("Jogador %d vai aumentar $%d\n", i, bet);
        robot[i].bet += bet;
        robot[i].money -= bet;
        if(robot[i].bet > *maxBet){
          (*maxBet) += bet;
        }
        *pool += bet;
        break;
      }
    }else if(rd == 1){ // Check
      printf("Jogador %d quer dar check\n", i);
      if(robot[i].bet < *maxBet){
        printf("É necessario cobrir o valor %d!\n", *maxBet - robot[i].bet);
      }else break;
    }else{  // Fugir
      printf("Jogador %d fugiu\n", i);
      robot[i].folded = true;
      break;
    }
  }

}

void playerBet(Player* player, int i, int *maxBet, int *pool){
  int opcao;
  //Tomar decisão (Aumentar: 0, Check: 1, Fugir: 2)
  while(true){
    printf("Entre com sua jogada: Aumentar (0), Check (1) ou Fugir (2)\n");
    scanf("%d%*c", &opcao);
    if(opcao == 0){ // Aumenta
      int bet;
      printf("Informe a quantia que deseja aumentar:");
      scanf("%d", &bet);
      if(bet > player[i].money){
        printf("Você não possui essa quantia\n");
        break;
      }
      player[i].bet += bet;
      player[i].money -= bet;
      if(player[i].bet > *maxBet){
        (*maxBet) += bet;
      }
      *pool += bet;
      break;
    }else if(opcao == 1){ // Check
      if(player[i].bet < *maxBet){
        printf("Você precisa cobrir o valor %d!\n", *maxBet - player[i].bet);
      }else break;
    }else{  // Fugir
      player[i].folded = true;
      break;
    }
  }

}

void initPlayer(Player *player, int i){
  player[i].bet = 0;
  player[i].folded = false;
  player[i].aumentou = 0;
  player[i].hand.topo = 0;
}


void addCard(Player *player, int i, Card card){
  player[i].hand.cards[player[i].hand.topo] = card;
  player[i].hand.topo++;
}