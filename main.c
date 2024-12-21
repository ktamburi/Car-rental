#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#define MAX_DAMAGES 100
#include "structures.h"

int main()
{
    srand(time(0));
    int cnt_V=0,cnt_R=0,cnt_C=0;
    int option=0,todaydate,todaymonth,curryear;
    struct Vehicle *head_V=NULL;
    struct Reservation *head_R=NULL;
    struct Client *head_C=NULL;

    struct Damage damages[MAX_DAMAGES];
    int damageCount = 0;

    int choice;
    int damageID;


    system("cls");
    do{printf("\n\
//////////////////////////////////////////////////////////////////////////\n\
//                               Welcome!                               //\n\
//      Before proceeding please insert today's date (use numbers)      //\n\
//////////////////////////////////////////////////////////////////////////\n");
        printf("\nThe month: ");
        scanf("%d",&todaymonth);
        while(todaymonth<0||todaymonth>12){
            printf("\nIncorrect month! Insert month again: ");
            scanf("%d",&todaymonth);
        }
        printf("\nThe date: ");
        scanf("%d", &todaydate);
        while(todaydate <= 0 || todaydate > 31 || ((todaymonth == 4 || todaymonth == 6 || todaymonth == 9 || todaymonth == 11) && todaydate == 31) || (todaymonth == 2 && todaydate > 28)) {
            printf("\nIncorrect date! Insert date again: ");
            scanf("%d", &todaydate);
        }
        printf("\nThe year: ");
        scanf("%d",&curryear);
        printf("\nThank you!\nYou can now press 0 to access the Menu or press 1 to insert date once more!\n");
        scanf("%d",&option);
        while(option!=0&&option!=1){
            printf("\nThe input is incorrect! Please try again.\n");
            scanf("%d",&option);
        }
        system("cls");}while(option==1);

        readReservationsFromFile(&head_R,&cnt_R);
        readVehiclesFromFile(&head_V,&cnt_V);
        ReadClientsFile(&head_C,&cnt_C);
        loadDataFromFile(damages, &damageCount);
        delay(3);
        system("cls");

        struct tm day={0, 0, 0, todaydate, todaymonth-1, curryear-1900 };
        time_t today_time=mktime(&day);

    while(option==0){
        printf("\n\nMENU:\n");
        printf("1-  Add a vehicle\n\
2-  Display all vehicle\n\
3-  Display all vehicles based on daily rental price\n\
4-  Display details for a specific vehicle\n\
5-  Display available vehicles currently (with no reservations at all)\n\
6-  Display available vehicles at a future time\n\
7-  Display top 3 most reserved vehicles at the moment\n\
8-  Modify vehicle information\n\
9-  Remove vehicle from database\n\
10- Create a new reservation\n\
11- Display all reservations\n\
12- Display a reservation details using reservation ID\n\
13- Display reservation calendar for a vehicle\n\
14- Cancel reservation\n\
15- Display all clients\n\
16- Display data for a specific client\n\
17- Display clients who have more than 3 rents\n\
18- Modify client's data\n\
19- Save all reservation exceeding a certain price to a file\n\
20- Damage report\n");

        printf("\n\nEnter an option or press -1 to close:");
        scanf("%d",&option);

        if(option==-1){
            system("cls");
            printf("\n\
//////////////////////////////////////////////////////////////////////////\n\
//                 Thank you for using our program!                     //\n\
//////////////////////////////////////////////////////////////////////////");
            return 0;
        }

        system("cls");
        switch(option)
        {
        case 1:{
            addNewVehicle(&head_V,&cnt_V);
            saveVehiclestoFile(head_V,cnt_V);
            break;}
        case 2:
            displayVehicles(head_V);
            break;
        case 3:{
            sortVehiclesByPrice(head_V);
            saveVehiclestoFile(head_V,cnt_V);
            displayVehicles(head_V);
            break;}
        case 4:
            SearchLicensePlate(head_V);
            break;
        case 5:
            AvailableVehiclesCurr(head_V);
            break;
        case 6:
            vehiclesAvailFuture(head_R,head_V,today_time);
            break;
        case 7:{
            sortVehicle_top3(head_V);
            saveVehiclestoFile(head_V,cnt_V);
            break;}
        case 8:{
            modifyvehicle(head_V);
            saveVehiclestoFile(head_V,cnt_V);
            break;}
        case 9: {
            deleteVehicle(&head_V,&head_R,head_C,&cnt_V,&cnt_R);
            saveVehiclestoFile(head_V,cnt_V);
            saveREStoFile(head_R,cnt_R);
            SaveClientsToFile(head_C,cnt_C);
            break;}
        case 10:{
            newReservation(&head_C,head_V,&head_R,&cnt_R,&cnt_C,today_time);
            bubbleSortRES(head_R);
            saveVehiclestoFile(head_V,cnt_V);
            saveREStoFile(head_R,cnt_R);
            SaveClientsToFile(head_C,cnt_C);
            break;}
        case 11:
            displayReservation(head_R);
            break;
        case 12:
            searchResID(head_R);
            break;
        case 13:
            displayResCalendarForVehicle(head_V,head_R,today_time);
            break;
        case 14: {
            deleteReservation(&head_R,head_V,head_C,&cnt_R);
            saveVehiclestoFile(head_V,cnt_V);
            saveREStoFile(head_R,cnt_R);
            SaveClientsToFile(head_C,cnt_C);
            break;}
        case 15:
            displayClients(head_C);
            break;
        case 16:
            searchclientbyID(head_C);
            break;
        case 17: display3rents(head_C);
            break;
        case 18: {
            modifyClient(head_C);
            SaveClientsToFile(head_C,cnt_C);
            break;}
        case 19:
            exceedingcost(head_R);
            break;
        case 20: {
            int t=1;
            while (t) {
                printf("\n\nVehicle Rental System\n");
                printf("1. Report Damage\n");
                printf("2. Display Damage History\n");
                printf("3. Update or Resolve Damage\n");
                printf("4. Exit Report\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);
                system("cls");
                switch (choice) {
                    case 1:
                        reportDamage(damages, &damageCount,head_V);
                        break;
                    case 2:
                        displayDamageHistory(damages, damageCount);
                        break;
                    case 3:
                        printf("Enter the damage ID to update or resolve: ");
                        scanf("%d", &damageID);
                        updateDamage(damages, damageCount, damageID);
                        break;
                    case 4:
                        t=0;
                        saveDataToFile(damages, damageCount);
                        break;
                    default:
                        printf("Invalid choice. Please try again.\n");
                }
            }
            break;}
        default:{
            printf("Error! Option is not correct! Insert again!");}
        }

        printf("\n\nInsert 0 to return to MENU or -1 to close:");
        scanf("%d",&option);
        system("cls");

        if(option==-1){
            printf("\n\
//////////////////////////////////////////////////////////////////////////\n\
//                 Thank you for using our program!                     //\n\
//////////////////////////////////////////////////////////////////////////");
            return 0;
        }
    }
    return 0;
}