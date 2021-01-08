#include "card.h"

void cardInit(Card* card, int i, int rank, int suit){
  card[i].suit = suit;
  card[i].rank = rank;
}

int card_toString(Card card){
  switch(card.rank){
  case 9:
    printf("J");
    break;
  case 10:
    printf("Q");
    break;
  case 11:
    printf("K");
    break;
  case 12:
    printf("A");
    break;
  default:
    printf("%d",card.rank+2);
    break;
  }
  
  printf(" of ");

  switch(card.suit){
  case 0:
    printf("Spades");
    break;
  case 1:
    printf("Hearts");
    break;
  case 2:
    printf("Diamonds");
    break;
  case 3:
    printf("Clubs");
    break;
  default:
    printf("%d",card.suit);
    break;
  }
  
  putchar('\n');
  return 0;
}