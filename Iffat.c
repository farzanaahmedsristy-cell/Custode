#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int tripID;
    char source[15];
    char destination[15];
    int availableSeats;
    float fare;
} Trip;

typedef struct {
    int bookingID;
    int tripID;
    char passengerName[15];
    int seatsBooked;
} Booking;

Trip trips[5] = {
    {1, "Dhaka", "Chittagong", 40, 500},
    {2, "Dhaka", "Sylhet", 30, 600},
    {3, "Chittagong", "Cox's Bazar", 20, 300},
    {4, "Dhaka", "Khulna", 50, 450},
    {5, "Rajshahi", "Dhaka", 25, 550}
};

Booking bookings[10];
int bookingCount = 0;

void showBookings(char *name) {
    int found = 0;
    for(int i=0;i<bookingCount;i++){
        if(strcmp(bookings[i].passengerName,name)==0){
            found=1;
            printf("BookingID:%d TripID:%d Seats:%d\n",bookings[i].bookingID,bookings[i].tripID,bookings[i].seatsBooked);
        }
    }
    if(found==0) printf("No bookings\n");
}

void cancelBooking(int id) {
    int found=0;
    for(int i=0;i<bookingCount;i++){
        if(bookings[i].bookingID==id){
            found=1;
            for(int j=0;j<5;j++){
                if(trips[j].tripID==bookings[i].tripID){
                    trips[j].availableSeats+=bookings[i].seatsBooked;
                    break;
                }
            }
            for(int k=i;k<bookingCount-1;k++){
                bookings[k]=bookings[k+1];
            }
            bookingCount--;
            printf("Booking %d cancelled\n",id);
            break;
        }
    }
    if(found==0) printf("Booking not found\n");
}

void adminReport() {
    int total=0;
    for(int i=0;i<5;i++){
        int booked=0;
        for(int j=0;j<bookingCount;j++){
            if(bookings[j].tripID==trips[i].tripID) booked+=bookings[j].seatsBooked;
        }
        total+=booked*trips[i].fare;
        printf("TripID:%d %s->%s Passengers:%d Revenue:%.2f\n",trips[i].tripID,trips[i].source,trips[i].destination,booked,booked*trips[i].fare);
    }
    printf("Total Revenue:%.2f\n",(float)total);
}

void addBooking() {
    char name[15];
    int trip,seats;
    printf("Your name:");
    scanf("%s",name);
    printf("TripID:");
    scanf("%d",&trip);
    printf("Seats:");
    scanf("%d",&seats);
    for(int i=0;i<5;i++){
        if(trips[i].tripID==trip){
            if(trips[i].availableSeats>=seats){
                trips[i].availableSeats-=seats;
                bookings[bookingCount].bookingID=bookingCount+1;
                bookings[bookingCount].tripID=trip;
                strcpy(bookings[bookingCount].passengerName,name);
                bookings[bookingCount].seatsBooked=seats;
                bookingCount++;
                printf("Booking done! ID:%d\n",bookingCount);
            }else{
                printf("Not enough seats\n");
            }
            return;
        }
    }
    printf("Trip not found\n");
}

int main(){
    int choice;
    while(1){
        printf("\n_Booking System_\n");
        printf("1. Book Tickets\n");
        printf("2. My Bookings\n");
        printf("3. Cancel Booking\n");
        printf("4. Admin Report\n");
        printf("5. Exit\n");
        printf("Choice:");
        scanf("%d",&choice);
        if(choice==1) addBooking();
        else if(choice==2){
            char name[15];
            printf("Your name:");
            scanf("%s",name);
            showBookings(name);
        }
        else if(choice==3){
            int id;
            printf("BookingID:");
            scanf("%d",&id);
            cancelBooking(id);
        }
        else if(choice==4) adminReport();
        else if(choice==5) break;
        else printf("Invalid\n");
    }
    return 0;
}