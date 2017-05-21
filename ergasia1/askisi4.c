#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_SEATS 53

void showMenu();
void showEmptySeats();
void bookSeat();
void bookFirstSeatAtWindow();
void cancelBooking();
void seatIsBooked();
void showBookedSeats();
void saveDiagram();
void showDiagram();

int main() {

    int action;
    int numberOfSeats;
    char busNumber[10];
    FILE *fp;
    fp = fopen("bus.txt", "r");

    if (fp) {

        fscanf(fp,"%s %d", busNumber, &numberOfSeats);
        fclose(fp);
    }
    else {

        printf("\nFile bus.txt not found\n");

        return 0;
    }

    if (numberOfSeats>MAX_SEATS || ((numberOfSeats-5)%4) != 0 ){

        printf("\nInvalid number of seats\n");

        return 0;
    }

    int seats[numberOfSeats];
    int n=0;

    while(n<numberOfSeats){

        seats[n]=0;
        n++;
    }

    do {

        showMenu();
        scanf("%d", &action);

        if(action == 1){

            showEmptySeats(seats, numberOfSeats);
        }
        if(action == 2){

            bookSeat(seats, numberOfSeats);
        }
        if(action == 3){

            bookFirstSeatAtWindow(seats, numberOfSeats);
        }
        if(action == 4){

            cancelBooking(seats, numberOfSeats);
        }
        if(action == 5){

            seatIsBooked(seats, numberOfSeats);
        }
        if(action == 6){

            showBookedSeats(seats ,numberOfSeats);
        }
        if(action == 7){

            showDiagram(busNumber,seats, numberOfSeats);
        }
        if(action == 8){

            saveDiagram(busNumber, seats, numberOfSeats);
        }
        if(action == 0){

            return 0;
        }
       if(action<0 || action>8) {

            printf("Wrong input. Please try again\n");
        }
    } while(action!=0);

    return 0;
}

void showMenu(){

            printf("\nChoose action:\n");
            printf("1: Show total empty seats and number of seat\n");
            printf("2: Book a seat\n");
            printf("3: Show and book the first empty seat at window\n");
            printf("4: Cancel booking\n");
            printf("5: Search if seat is already booked\n");
            printf("6: Show list of booked seats\n");
            printf("7: Show bus number and diagram\n");
            printf("8: Save bus number and diagram\n");
            printf("0: Exit program\n");
            printf("\nGive action code:\n");
}

void showEmptySeats(int seats[], int arrayLength){

            int emptySeats=0;
            int i;
			
            for(i=0; i<arrayLength; i++){

                if(seats[i]==0){
                    emptySeats++;
                    printf("Seat number %d is empty\n", i+1);
                }
            }
			
            printf("There are %d empty seats\n", emptySeats);
}

void bookSeat(int seats[], int arrayLength){

    int seatNumber;

    printf("Give the number of the seat you want to book\n");
    scanf("%d", &seatNumber);

    if(seatNumber > arrayLength || seatNumber <= 0){

        printf("The number of the seat you have given does not exist\n");
    }
    else {

        if (seats[seatNumber-1] == 0){

            seats[seatNumber-1] = 1;
            printf("Seat number %d was successfully booked\n", seatNumber);
        }
        else{

            printf("Seat number %d is already booked. Please choose another seat.\n", seatNumber);
        }
    }
}

void bookFirstSeatAtWindow(int seats[], int arrayLength){

    int i=0;

    while(seats[i]!=0){

        if(i%2==0){

            if(i +5<arrayLength){

                i = i +3;
            }
            else {

                i = i +4;
            }
        }
        else{

            i++;
        }
    }

    if(i<arrayLength){

        seats[i] = 1;
        printf("Seat number %d was successfully booked\n", i+1);
    }
    else {
        printf("All seats at window are already booked\n");
    }
}

void cancelBooking(int seats[], int arrayLength){

    int seatNumber;

    printf("Give the number of the seat you want to cancel\n");
    scanf("%d", &seatNumber);
    if(seatNumber > arrayLength || seatNumber <= 0){

        printf("The number of the seat you have given does not exist\n");
    }
    else {

        if (seats[seatNumber-1]==0){

            printf("The number of the seat you have given is not booked\n");
        }
        else {

            seats[seatNumber-1]=0;
            printf("Your booking (seat number %d) is canceled\n", seatNumber);
        }
    }
}

void seatIsBooked(int seats[], int arrayLength) {

    int seatNumber;

    printf("Give the number of the seat you want to search\n");
    scanf("%d", &seatNumber);

    if(seatNumber > arrayLength || seatNumber <= 0){

        printf("The number of the seat you have given does not exist\n");
    }
    else {

       if (seats[seatNumber-1]==0) {

            printf("The seat with number %d is not booked\n", seatNumber);
       }
       else {

            printf("The seat with number %d is booked\n", seatNumber);
       }
    }

}

void showBookedSeats(int seats[], int arrayLength){

    int i=0;
    int bookedSeats=0;

    while(i<arrayLength){

        if(seats[i]==1){

            printf("Seat number %d is booked\n", i+1);
            bookedSeats++;
        }
        i++;
    }

    if(bookedSeats == 0){

        printf("There are no booked seats\n");
    }
}

void showDiagram(char busNumber[],int seats[], int arrayLength){

    int i=0;
    int character=1;

    printf("%s\n", busNumber);
    while(i<arrayLength){

        if(character==3 && (i+5 <= arrayLength)){

           printf(" ");
        }
        if(character==5 && (i+5 <= arrayLength) ){

           printf("\n");
           character=1;
        }
        if(seats[i]==0){

            printf("_");
        }
        else{

            printf("*");
        }
        i++;
        character++;
    }
}

void saveDiagram(char busNumber[],int seats[], int arrayLength){

    FILE *fpointer;
    fpointer = fopen("layout.txt", "w");
    int i=0;
    int character=1;

    fprintf(fpointer, busNumber);
    fprintf(fpointer, "\n");

    while(i<arrayLength){

        if(character==3 && (i+5 <= arrayLength)){

           fprintf(fpointer, " ");
        }
        if(character==5 && (i+5 <= arrayLength) ){

           fprintf(fpointer, "\n");
           character=1;
        }
        if(seats[i]==0){

            fprintf(fpointer, "_");
        }
        else{

            fprintf(fpointer, "*");
        }
        i++;
        character++;
    }
    fclose(fpointer);
    printf("Bus diagram was saved in layout.txt\n");
}

