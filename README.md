# Poker evolutivo
by:
Thiago Henrique Vicentini - 11234270
Rafael Kuhn Takano - 11200459

## Execução
Apos baixados os arquivos, no terminal digite:
make all
make run

## Objetivos
Em um jogo de poker a cada round podem ser feitas 3 ações: Check, Rise e Run. O Objetivo desse algoritmo é evoluir um cromossomo que representa a jogada de um player a cada round, buscando otimizar a melhor escolha, aumentando e fugindo quando necessário e lucrando o máximo possivel em cada Round.

## Programas de terceiros
Foi utilizada uma ferramenta de terceiros chamada "Hand-Evaluator" para obter um valor numerico para a mão de cada jogador e assim poder decidir o verncedor do round. A biblioteca é encontrada em: https://github.com/HenryRLee/PokerHandEvaluator

## Versão simplificada
1 player contra 2 máquinas e 1 robô.
Maquinas possuem inteligência mínima, ou seja, não fogem em situações favoráveis:
 - Se tiver um par na mão
 - Se todos anteriores já deram check
 - Se já tiver apostado muito na rodada anterior
   
## Inicializando População
A população é inicializada com a geração de indivíduos aleatórios, onde cada indivíduo possui um cromossomo composto por 4 coeficientes numéricos que são utilizados para calcular a ação do player.

## Cálculo do fitness
A cada geração, os indivíduos devem ser avaliados. Seu valor de fitness é obtido a partir da quantia final de dinheiro após jogar 6 partidas. Isso foi feito pois como Poker é um jogo de azar se fosse jogado apenas uma partida, correria o risco de sorte interferir na escolha e portanto não geraria um fitness tão preciso.
	
## Seleção
A seleção é feita de acordo com o fitness dos indivíduos. É escolhido o melhor individuo da população (com maior fitness) e este faz uma média com o restante da população (elitismo).

## Mutação 
A mutação foi feita baseada na estrátegia do professor Simões, onde uma taxa de mutação original é escolhida e esta varia quando o fitness da população não está aumentando tanto quanto desejado (mutação veriada). Além disso, todos os individuos da população mutam e sobre os genes, inicialmente tem-se uma chance de 50% de mutação para cada gene que vai diminuindo a medida que algum gene muta (mutação distribuida).