#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct card getNextCard();
int isTheSameCard();
int isSet();
void generateGrid();
void chooseCards();
void playerPlays();
int gameIsOver();
void showPlayersData();

struct card {
	char color;
	char shape;
	int number;
	char texture;
};

struct player {
	char name[17];
	unsigned int score: 8;
	char id;
};

int triggerGenerateGrid; //Kathorizei an to programma dimiourgei nea 12ada karton (an 1 dimiourgei)
struct card cardsChoosed[3]; //Oi kartes pou exei epileksi o paixtis
struct card allCardsDisplayed[3][4]; //Oi kartes tis 12adas

struct player player1 = {"Marina Andreou", 0, 'a'};
struct player player2 = {"Kostas Grammenos", 0, 'g'};
struct player player3 = {"Maria Perdika", 0, 'p'};

int main() {

	char c;
	triggerGenerateGrid=1;

	do{
		if(gameIsOver(player1, player2, player3)==1){

			return 0;
		}

		if(triggerGenerateGrid == 1){

			generateGrid();
		}
		fflush (stdin);
		triggerGenerateGrid = 1;
		printf("Give the id of the player, 0 to exit the game or press any key for new card grid\n");
		c = getchar();

		if(c=='a'){

			playerPlays(&player1);
			continue;
		}
		if(c=='g'){

			playerPlays(&player2);
			continue;
		}
		if(c=='p'){

			playerPlays(&player3);
			continue;
		}
	}while (c!='0');

	showPlayersData();
	return 0;
}

/**
Dimiourgei mia karta me ti voithia tis rand()
*/
struct card getNextCard(){

	struct card actualCard;
	int color =(rand() % 3) + 1;

    switch(color) {

      case 1 :
		actualCard.color = 'r';
		break;
	  case 2 :
		actualCard.color = 'g';
		break;
	  case 3 :
		actualCard.color = 'b';
		break;
	}

	int shape =(rand() % 3) + 1;

	switch(shape) {

      case 1 :
		actualCard.shape = 'c';
		break;
	  case 2 :
		actualCard.shape = 't';
		break;
	  case 3 :
		actualCard.shape = 'r';
		break;
	}

	int number =(rand() % 3) + 1;

	actualCard.number = number;

	int texture =(rand() % 3) + 1;

	switch(texture) {

      case 1 :
		actualCard.texture = 'b';
		break;
	  case 2 :
		actualCard.texture = 'h';
		break;
	  case 3 :
		actualCard.texture = 'e';
		break;
	}

	return actualCard;
}

/**
Elegxei an dyo kartes einai idies. Xrisimopoieitai toso kata
tin dimiourgia tis 12adas ton karton oso kai kata tin epilogi
ton karton apo ton paixti (an 1 oi kartes einai idies)
*/
int isTheSameCard(struct card card1, struct card card2){

	if(card1.color!=card2.color){

		return 0;
	}
	if(card1.shape!=card2.shape){

		return 0;
	}
	if(card1.number!=card2.number){

		return 0;
	}
	if(card1.texture!=card2.texture){

		return 0;
	}
	return 1;
}

/**
Dimiourgei to plegma tis 12adas karton
*/
void generateGrid(){

	int i=0;
	srand(time(NULL));

	while(i<3){
		int j=0;
		while(j<4){

			struct card card = getNextCard();

			if(i==1 && j==1){

				printf("[%c, %c, %d, %c]", card.color, card.shape, card.number, card.texture);
				allCardsDisplayed[0][0] = card;
				j++;
			}
			else {

				if(isTheSameCard(card, allCardsDisplayed[i][j])==1){

					continue;
				}
				else {
					if(j<3){

						printf("[%c, %c, %d, %c]", card.color, card.shape, card.number, card.texture);
					}
					else {

						printf("[%c, %c, %d, %c]\n", card.color, card.shape, card.number, card.texture);
					}

					allCardsDisplayed[i][j] = card;
					j++;
				}
			}
		}
		i++;
	}
}

/**
Ekteleite kata tin epilogi karton apo ton paikti. Zitaei tis sintetagnenes tis kartas
kai elegxei an oi sintetagmenes pou dinei o xristis exoun epilegei idi.
*/
void chooseCards(){

	int i=1;
	int x, y;

	while(i<=3){

		printf("Give the coordinates of the card number %d\n", i);
		printf("Give X \n");
		scanf("%d", &x);
		if(x<0 || x>2){

			printf("The value of X has to be between 0 and 2. Please try again\n");
			continue;
		}
		printf("Give Y \n");
		scanf("%d", &y);
		if(y<0 || y>3){

			printf("The value of Y has to be between 0 and 3. Please try again\n");
			continue;
		}
		if(i==2 && isTheSameCard(cardsChoosed[i-2], allCardsDisplayed[x][y])){

			printf("You have already chosen this card. Please choose another one.\n");
			continue;
		}
		if(i==3 && (isTheSameCard(cardsChoosed[i-2], allCardsDisplayed[x][y]) || isTheSameCard(cardsChoosed[i-3], allCardsDisplayed[x][y]))){

			printf("You have already chosen this card. Please choose another one.\n");
			continue;
		}
		cardsChoosed[i-1] = allCardsDisplayed[x][y];
		i++;
	}
}

/**
Ektelei tin diadikasia tou paixnidiou gia energo paixti.
Tiponei odigies gia tin ektelesi tou paixnidiou kathos kai
tis plirofories tou paixti (id, onoma, score).
Ananeonei to score tou paixti analoga me tin epilogi tou.
*/
void playerPlays(struct player *activePlayer){

		printf("The player with id %c is now active\n", activePlayer->id);
		printf("The player name is %s and the score is %d points\n", activePlayer->name, activePlayer->score);
		chooseCards();

		if(isSet(cardsChoosed)==1){

            activePlayer->score = activePlayer->score + 2;
			printf("Your choose is a set!\n", activePlayer->id, activePlayer->score);
			printf("The score of the player with id %c is %d points\n", activePlayer->id, activePlayer->score);
		}
		else {

            if(activePlayer->score > 0){

                activePlayer->score = activePlayer->score - 1;
				printf("Your choose is not a set\n", activePlayer->id, activePlayer->score);
				printf("The score of the player with id %c is %d points\n", activePlayer->id, activePlayer->score);
                triggerGenerateGrid = 0; //Den dimiourgeitai nea 12ada karton
            }
			else{

				printf("Your choose is not a set\n", activePlayer->id, activePlayer->score);
				printf("The score of the player with id %c is 0 points\n", activePlayer->id);
			}
		}
		triggerGenerateGrid=1; //Dimiourgeitai nea 12ada karton
}

/**
Elegxei an iparxei nikitis kai tiponei katallila minimata (an 1 iparxei nikitis)
*/
int gameIsOver(struct player player1,struct player player2,struct player player3){

	if(player1.score >=10){

		showPlayersData();
		printf("The winner is %s \n", player1.name);
		return 1;
	}
	if(player2.score >=10){

		showPlayersData();
		printf("The winner is %s \n", player2.name);
		return 1;
	}
	if(player3.score >=10){

		showPlayersData();
		printf("The winner is %s \n", player3.name);
		return 1;
	}
	return 0;
}

/**
Tiponei ta stoixeia ton paikton
*/
void showPlayersData(){

	printf("The player %s with id %c has %d points\n", player1.name,player1.id, player1.score);
	printf("The player %s with id %c has %d points\n", player2.name,player2.id, player2.score);
	printf("The player %s with id %c has %d points\n", player3.name,player3.id, player3.score);
}

/**
Elegxei an oi epilegmenes apo ton paixti kartes apoteloun set (an 1 apoteloun set).
An oi dio kartes exoun tin idiotita idia eno i triti oxi tote den einai set.
*/
int isSet(struct card cards[]){

	if(cards[1].color != cards[2].color && cards[1].color == cards[3].color && cards[2].color == cards[3].color){

		return 0;
	}
	if(cards[1].color == cards[2].color && cards[1].color != cards[3].color && cards[2].color == cards[3].color){

		return 0;
	}
	if(cards[1].color == cards[2].color && cards[1].color == cards[3].color && cards[2].color != cards[3].color){

		return 0;
	}
	if(cards[1].shape != cards[2].shape && cards[1].shape == cards[3].shape && cards[2].shape == cards[3].shape){

		return 0;
	}
	if(cards[1].shape == cards[2].shape && cards[1].shape != cards[3].shape && cards[2].shape == cards[3].shape){

		return 0;
	}
	if(cards[1].shape == cards[2].shape && cards[1].shape == cards[3].shape && cards[2].shape != cards[3].shape){

		return 0;
	}
	if(cards[1].number != cards[2].number && cards[1].number == cards[3].number && cards[2].number == cards[3].number){

		return 0;
	}
	if(cards[1].number == cards[2].number && cards[1].number != cards[3].number && cards[2].number == cards[3].number){

		return 0;
	}
	if(cards[1].number == cards[2].number && cards[1].number == cards[3].number && cards[2].number != cards[3].number){

		return 0;
	}
	if(cards[1].texture != cards[2].texture && cards[1].texture == cards[3].texture && cards[2].texture == cards[3].texture){

		return 0;
	}
	if(cards[1].texture == cards[2].texture && cards[1].texture != cards[3].texture && cards[2].texture == cards[3].texture){

		return 0;
	}
	if(cards[1].texture == cards[2].texture && cards[1].texture == cards[3].texture && cards[2].texture != cards[3].texture){

		return 0;
	}

	return 1;
}
