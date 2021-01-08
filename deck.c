#include "deck.h"

void initDeck(Deck* deck){
  deck->topCardIndex = 51;
} 

void deckFill(Deck* deck){
  int rank;
  int suit;
  int i = 0;
  for(rank=0; rank<13; rank++){
    for(suit=0; suit<4; suit++){
      deck->cards[i].suit = suit;
      deck->cards[i].rank = rank;
      i++;
    }
  }
}

//take the top card off the deck
void dequeueCard(Deck *deck, Card *data){
  (*data) = deck->cards[deck->topCardIndex];
  deck->topCardIndex = deck->topCardIndex - 1;
}

void viraProximaCarta(Deck *deck, Card *mesa, int *i){
  Card tmp;
  dequeueCard(deck, &tmp);
  mesa[*i] = tmp;
  (*i)++;
}

void shuffle(Deck *deck, int shuffles){
  int a;
  int b;
  int i; 
  srand(time(NULL));
  a = rand()%DECK_SIZE;
  b = rand()%DECK_SIZE;
  for(i=0; i<shuffles; i++){ 
    swap_card(deck, a, b);
    a = rand()%DECK_SIZE;
    b = rand()%DECK_SIZE;
  }
}

int swap_card(Deck *deck, int s, int t){
  Card tmp;
  tmp = deck->cards[t];
  deck->cards[t] = deck->cards[s];
  deck->cards[s] = tmp;
  return 0; 
}

int converter(Card c){
  int resultadoConvertido;
  resultadoConvertido = c.rank*4;
  resultadoConvertido += c.suit; 
  return resultadoConvertido;
}