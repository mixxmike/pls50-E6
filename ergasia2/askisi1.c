#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

const char EMPTY_SEAT[40]={'\0'}; //Xrisimopoieitai stous elegxous kenis thesis

void readBusTxt();
void showMenu();
void showEmptySeats();
void bookSeat();
void seatIsBooked();
void cancelBooking();
void showBookedSeats();
void saveToBusTxt();

struct seat {
   char  name[40];
   unsigned short  phone[10];
   unsigned int  seatNumber;
};

struct seat busSeats[]; //Pinakas me oles tis theseis tou leoforeiou
char busNumber[7]={0}; //To noumero tou leoforeiou
int numberOfSeats; //O arithmos theseon tou leoforeiou

int main() {

    int action;
	readBusTxt();

	int n=0;
    if(numberOfSeats==0){

    //Arxikopoisi tou pinaka theseon tou leoforeiou
        while(n<numberOfSeats){

            struct seat currentSeat = {'\0',0,0};
            busSeats[n]=currentSeat;
            n++;
        }
    }

    int seatNumber;

    do {

        showMenu();
        fflush (stdin);
        scanf("%d", &action);

        if(action == 1){

            showEmptySeats(busSeats, numberOfSeats);
        }
        if(action == 2){

            printf("Give the number of the seat you want to book\n");
            scanf("%d", &seatNumber);

            if(seatNumber > numberOfSeats || numberOfSeats <= 0){

                printf("The number of the seat you have given does not exist\n");
            }
            else{

                bookSeat(busSeats[seatNumber-1], seatNumber);
            }

        }
        if(action == 3){

            seatIsBooked(busSeats, numberOfSeats);
        }
        if(action == 4){

            printf("Give the number of the seat you want to cancel\n");
            scanf("%d", &seatNumber);

            if(seatNumber > numberOfSeats || seatNumber <= 0){

                printf("The number of the seat you have given does not exist\n");
            }
            else {

                cancelBooking(busSeats[seatNumber-1], seatNumber);
            }
        }
        if(action == 5){

            showBookedSeats(busSeats, numberOfSeats);
        }
        if(action == 0){

            saveToBusTxt(busSeats, numberOfSeats);
            return 0;
        }
       if(action<0 || action>5) {

            printf("Wrong input. Please try again\n");
        }
    } while(action!=0);

    return 0;
}

/**
Diavazei to morfopoiimeno arxeio bus.txt kai ananeoinei
ton pinaka bus.txt me tis kratimenes theseis pou vriskontai
sto arxeio. Diavazei episeis tin pinakida tou leoforeiou
kai ton arithmo theseon.
*/
void readBusTxt(){

    FILE *fp;
    fp = fopen("bus.txt", "r");
    char line[60]; //String pou periexei tin grammi pou diavazei i fgets()
    char *token; //Dinamikos pinakas pou periexei ta strings meta apo split tis line
    char *name= (char *) malloc(40 * sizeof(char)), *phone; //To onomateponimo kai til tou epivati
    int seatNumber, temp;

    if (fp) {

        fscanf(fp,"%s %d", busNumber, &numberOfSeats);
        printf("%s %d\n", busNumber, numberOfSeats);
        while (fgets(line, sizeof(line), fp) != NULL){
            if(line[0]!='\n'){

                strtok(line, "\n");
                token = strtok(line, " ");
                int i=0;
                strcpy(name, token);
                strcat(name," ");
                   while( token != NULL)
                   {
                      token = strtok(NULL, " ");
                      if(i==0){
                        strcat(name,token);
                      }
                      if(i==1){
                        seatNumber = atoi(token);
                      }
                      if(i==2){
                        phone = token;
                      }
                      i++;
                   }
                busSeats[seatNumber-1].seatNumber = seatNumber;
                strcpy(busSeats[seatNumber-1].name, name);
                int n=0;
                while(n<10){

                    if(n<strlen(phone)/sizeof(char)){
                        int temp = phone[n]-'0';
                        busSeats[seatNumber-1].phone[n] = (unsigned short) temp;
                    }
                    else{
                        busSeats[seatNumber-1].phone[n] = 10;
                    }
                    n++;
                }
             }
        }

        fclose(fp);

    }
    else {

        printf("\nFile bus.txt not found\n");
        numberOfSeats = 0;
    }
}

/**
Deixnei to menu epilogon
*/
void showMenu(){

            printf("\nChoose action:\n");
            printf("1: Show total empty seats and number of seat\n");
            printf("2: Book a seat\n");
            printf("3: Search if seat is already booked\n");
			printf("4: Cancel booking\n");
            printf("5: Show list of booked seats\n");
            printf("0: Exit program\n");
            printf("\nGive action code:\n");
}

/**
Deixnei tis kenes theseis kai to sinolo tous
*/
void showEmptySeats(struct seat seats[], int arrayLength){

        int emptySeats=0; // To sinolo kenon theseon
        int i;

        for(i=0; i<arrayLength; i++){

            if(strcmp(seats[i].name,EMPTY_SEAT)==0){
                emptySeats++;
                printf("Seat number %d is empty\n", i+1);
            }
        }

        printf("There are %d empty seats\n", emptySeats);
}

/**
Kanei kratisi tis thesis.
*/
void bookSeat(struct seat seatToBeBooked, int seatNumber){

	char inputPhoneChar[11]; //O pinakas exei mikos 11 oste na periexei 10 psifia tou tilefonou kai ton xaraktira '\n'

        if (strcmp(seatToBeBooked.name, EMPTY_SEAT)==0){

        fflush (stdin);
        seatToBeBooked.seatNumber = seatNumber;
        printf("Give your surname and first name:\n");
        fgets(seatToBeBooked.name, 41, stdin);
        char* nChar = strstr(seatToBeBooked.name, "\n");
        * nChar = '\0';

        printf("Give your phone number:\n");
        fflush (stdin);
        fgets(inputPhoneChar, 11, stdin);

        int i=0;
        while(i<10){

            int temp = inputPhoneChar[i]-'0';
            if(temp>=0 && temp<=9){
                seatToBeBooked.phone[i] = (unsigned short) temp;
            }
            else{
                seatToBeBooked.phone[i] = 10;
            }
            i++;
        }
        printf("Seat number %d was successfully booked with the following booking data:\n", seatNumber);
        printf("Name: %s\n", seatToBeBooked.name);
        printf("Phone number: ", seatToBeBooked.phone);

        int n=0;
        while(n<10){
            if(seatToBeBooked.phone[n]<=9){

                printf("%d", seatToBeBooked.phone[n]);
            }
            n++;
        }
        busSeats[seatNumber-1] = seatToBeBooked;
    }
    else{

        printf("Seat number %d is already booked. Please choose another seat.\n", seatNumber);
    }
}

/**
Akironei tin kratisi me dedomeno noumero thesis
*/
void cancelBooking(struct seat seatToBeCnaceled, int seatNumber){

        if (strcmp(seatToBeCnaceled.name, EMPTY_SEAT)==0){

            printf("The number of the seat you have given is not booked\n");
        }
        else {

            memset(seatToBeCnaceled.name, '\0', 40);
            int n=0;
            while (n<10){
                seatToBeCnaceled.phone[n]=0;
                n++;
            }
            seatToBeCnaceled.seatNumber = 0;
            busSeats[seatNumber-1] = seatToBeCnaceled;
            printf("Your booking (seat number %d) is canceled\n", seatNumber);
        }
}

/**
Elegxei an i thesei me dedomeno onoma i tilefono einai idi kratimeni
*/
void seatIsBooked(struct seat seats[], int arrayLength) {

//Oi pinakes userInput kai phoneToChar exoun mikos 41 kai 11 antisoixa oste na periexoun kai to '\n'
    char userInput[41], *dataToBeSearched, *dataOfBooking, searchBy, phoneToChar[11];

    printf("How do you want to search the booking?\n");
    printf("By name (code 1)\n");
    printf("By phone number (code 2)\n");
    fflush (stdin);
    fgets(&searchBy, 11, stdin);

    if (searchBy == '1'){

        printf("Give the exact name you have used to make the booking:\n");
        fflush (stdin);
        fgets(&userInput, sizeof(userInput), stdin);
        dataToBeSearched = strtok(&userInput,"\n");

        int n=0;

        while (n<arrayLength){

            if(strcmp(seats[n].name, EMPTY_SEAT) != 0){
                int i=0;
                while(i<10){
                    phoneToChar[i] = seats[n].phone[i]+'0';
                    i++;
                }
                dataOfBooking = strtok(seats[n].name,"\0");
                if(strcmp(dataToBeSearched, dataOfBooking) == 0){

                    printf("The seat with number %d is booked under the following booking data\n", n+1);
                    printf("Name: %s\n", dataOfBooking);
                    dataOfBooking = strtok(phoneToChar,":");
                    printf("Phone number: %s\n", dataOfBooking);
                    break;
                }
            }
            n++;
        }
        if(n==arrayLength){

            printf("There is no booking under the given data\n");
        }

    }
    if (searchBy == '2'){

        printf("Give the phone number:\n");
        fgets(&userInput, sizeof(userInput), stdin);
		dataToBeSearched = strtok(&userInput,"\n");
        int n=0;

        while (n<arrayLength){

            if(strcmp(seats[n].name, EMPTY_SEAT) != 0){
                int i=0;
                while(i<10){
                    phoneToChar[i] = seats[n].phone[i]+'0';
                    i++;
                }
                dataOfBooking = strtok(phoneToChar,":");

                if(strcmp(dataToBeSearched, dataOfBooking) == 0){

                    printf("The seat with number %d is booked under the following booking data\n", n+1);
                    printf("Name: %s\n", seats[n].name);
                    dataOfBooking = strtok(phoneToChar,":");
                    printf("Phone number: %s\n", dataOfBooking);
                    break;
                }
            }
            n++;
        }
        if(n==arrayLength){

            printf("There is no booking under the given data\n");
        }
    }
    if(searchBy != '1' && searchBy != '2')
    {

        printf("Wrong input\n");
    }
}

/**
Deixnei tis kratimenes theseis
*/
void showBookedSeats(struct seat seats[], int arrayLength){

    int i=0;
    int bookedSeats=0;

    while(i<arrayLength){

        if(seats[i].seatNumber != 0){

            printf("Seat number %d is booked with the following booking data:\n", i+1);
            printf("Name: %s \n", seats[i].name);
            printf("Phone number: ");
            int n=0;
            while(n<10){
                if(seats[i].phone[n]<10){
                    printf("%d", seats[i].phone[n]);
                }
                n++;
            }
            printf("\n");
            bookedSeats++;
        }
        i++;
    }

    if(bookedSeats == 0){

        printf("There are no booked seats\n");
    }
}

/**
Apothikevei ta dedomena, katalila morfopoiimena sto arxeio bus.txt
*/
void saveToBusTxt(struct seat seats[], int arrayLength){

    FILE *fpointer;
    fpointer = fopen("bus.txt", "w");
	int i=0;
    fprintf(fpointer, "%s %d\n", busNumber, arrayLength);
	while(i<arrayLength){


		if (strcmp(seats[i].name, EMPTY_SEAT)!=0){

            int n=0;
            while(n<40){
                if(seats[i].name[n]=='\0'){
                    n=0;
                    break;
                }

                fprintf(fpointer, "%c", seats[i].name[n]);
                n++;
            }
			fprintf(fpointer," %d ", seats[i].seatNumber);

            while(n<10){
                if(seats[i].phone[n]==10){
                    n=0;
                    break;
                }
                fprintf(fpointer, "%d", seats[i].phone[n]);
                n++;
            }
            fprintf(fpointer,"\n");
		}
		i++;
	}
	fclose(fpointer);
}





