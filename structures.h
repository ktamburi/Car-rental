#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

struct Person{
    char name[50];
    char state[4];
    char phone[20];
    char passportID[10];
};

struct Client{
    char clientID[11];
    struct Person info;
    int rents;
    struct Client *next;
};

struct Reservation{
    int resID;
    char clientID[11];
    char plateNumber[8];
    int days;
    int date;
    int month;
    int year;
    time_t time_start;
    time_t time_end;
    float price;
    struct Reservation *next;
};

struct Vehicle{
    char plateNumber[8];
    int year;
    char model[20];
    char fuel[20];
    float consumption;
    int seats;
    int dailyPrice;
    int reserved;
    struct Vehicle *next;
};

struct Damage {
    int damageID;
    char plateNumber[20];
    char description[200];
    char dateReported[20];
    bool resolved;
};

void addNewVehicle(struct Vehicle **head,int *cnt) {
    struct Vehicle *newVehicle, *curr;
    curr=*head;
    newVehicle = (struct Vehicle*)malloc(sizeof(struct Vehicle));
    int found=0;
    do{
        char menu[]="stop";
        printf("Enter plate number: ");
        scanf("%s", newVehicle->plateNumber);
        if(strcmpi(newVehicle->plateNumber,menu)==0){
            free(newVehicle);
            return;
        }
        struct Vehicle *check=*head;
        found=0;
        while (check != NULL) {
            if (strcmp(check->plateNumber, newVehicle->plateNumber) == 0){
                printf("You already have a car with this liscence plate number.\n\
Insert the liscense once more or insert \"stop\" to stop adding a new vehicle.\n\n");
                found++;
                break;
            }
            check=check->next;
        }
    }while(found!=0);
    printf("Enter year: ");
    scanf("%d", &(newVehicle->year));
    printf("Enter model: ");
    scanf("%s", newVehicle->model);
    printf("Enter fuel type: ");
    scanf("%s", newVehicle->fuel);
    printf("Enter fuel consumption (liters per km): ");
    scanf("%f", &(newVehicle->consumption));
    printf("Enter number of seats: ");
    scanf("%d", &(newVehicle->seats));
    printf("Enter daily price: ");
    scanf("%d", &(newVehicle->dailyPrice));
    newVehicle->reserved = 0;
    (*cnt)++;
    newVehicle->next = NULL;
    if (*head == NULL) {
        *head = newVehicle;
        printf("\nNew car added successfully!");
        return;
    }
    while(curr->next!=NULL) {
        curr = curr->next;
    }
    curr->next = newVehicle;
    printf("\nNew car added successfully!");
}

void readVehiclesFromFile(struct Vehicle** head,int *cnt) {
    FILE *fp = fopen("vehicles.txt", "r");
    if (fp == NULL) {
        printf("\nUnable to open the file.");
        return;
    }
    fscanf(fp,"%d\n",cnt);
    if (*cnt==0){
        printf("\nNo vehicles saved in file! File is empty!");
        fclose(fp);
        return;
    }

    struct Vehicle* current = *head;
    struct Vehicle* newVehicle;

    while (!feof(fp)) {
        newVehicle = (struct Vehicle*)malloc(sizeof(struct Vehicle));
    	newVehicle->next = NULL;
        fscanf(fp, "%s %d %s %s %f %d %d %d\n",
               newVehicle->plateNumber,
               &newVehicle->year,
               newVehicle->model,
               newVehicle->fuel,
               &newVehicle->consumption,
               &newVehicle->seats,
               &newVehicle->dailyPrice,
               &newVehicle->reserved);

        if (*head == NULL) {
        	*head = newVehicle;
    	} else {
		current->next = newVehicle;
        }
        current = newVehicle;
    }
    printf("\nAll vehicles were saved from file!");
    fclose(fp);
}

void saveVehiclestoFile(struct Vehicle *head, int cnt){
    FILE *fp=NULL;
    fp=fopen("vehicles.txt", "w");
    if(fp==NULL)
    {
        printf("\nCannot open file!");
        return;
    }
    fprintf(fp,"%d\n",cnt);
    if(cnt!=0)
    {
        while(head!=NULL)
        {
            fprintf(fp,"%s %d %s %s %.3f %d %d %d\n",
                    head->plateNumber,
                    head->year,
                    head->model,
                    head->fuel,
                    head->consumption,
                    head->seats,
                    head->dailyPrice,
                    head->reserved);
            head=head->next;
        }
    }
    fclose(fp);
}

void displayVehicles(struct Vehicle *head){
    if(head==NULL){
        printf("\nThere are no vehicles saved at the moment!\n");
    }
    while(head!=NULL){
        printf("\nPlate Number:%s\
\tYear: %d\
\tModel: %-16s\
\tFuel: %-8s\
\tConsumption: %.3f\
\tSeats: %d\
\tDaily Price (EUR): %d\
\tReservations: %d",head->plateNumber,head->year,head->model,head->fuel,head->consumption,head->seats,head->dailyPrice,head->reserved);
        head=head->next;
    }
}

void sortVehiclesByPrice(struct Vehicle *head_V){

    if(head_V==NULL){
        printf("\nThere are no vehicles saved! Add vehicle data first!");
        return;
    }
    printf("\nThe vehicles are sorted in ascending order based on their daily price!\n\n");
    //sort vehicle ascending order
     while(head_V!=NULL){
        struct Vehicle *curr=head_V->next;
        while(curr!=NULL){
            if(head_V->dailyPrice>curr->dailyPrice){
                char plateNumber[8];
                strcpy(plateNumber,curr->plateNumber);
                int year=curr->year;
                char model[20];
                strcpy(model,curr->model);
                char fuel[20];
                strcpy(fuel,curr->fuel);
                float consumption=curr->consumption;
                int seats=curr->seats;
                int dailyPrice=curr->dailyPrice;
                int reserved=curr->reserved;

                strcpy(curr->plateNumber,head_V->plateNumber);
                curr->year=head_V->year;
                strcpy(curr->model,head_V->model);
                strcpy(curr->fuel,head_V->fuel);
                curr->consumption=head_V->consumption;
                curr->seats=head_V->seats;
                curr->dailyPrice=head_V->dailyPrice;
                curr->reserved=head_V->reserved;

                strcpy(head_V->plateNumber,plateNumber);
                head_V->year=year;
                strcpy(head_V->model,model);
                strcpy(head_V->fuel,fuel);
                head_V->consumption=consumption;
                head_V->seats=seats;
                head_V->dailyPrice=dailyPrice;
                head_V->reserved=reserved;
            }
            curr=curr->next;
        }
        head_V=head_V->next;
    }
}

void modifyClient(struct Client *head){

    printf("\nInsert Client ID: ");
    char ID[11];
    scanf("%s",ID);
    while(head!= NULL)
    {
        if (strcmp(ID,head->clientID)==0)
        break;
        head=head->next;

    }
    if(head==NULL)
    {
        printf("\nNo client with this ID was found.\n");
        return;
    }
    else
    {
        int n=0;
        while(1){
            printf("\n1-Modify Full Name\n2-Modify State\n3-Modify Phone Number\n4-Modify Passport ID\n0-Stop modifying");
            printf("\n\n\nEnter option: ");
            scanf("%d", &n);
            system("cls");//clears the terminal

            printf("\nClient ID: %s ",head->clientID);
            printf("\nName: %s ",head->info.name);
            printf("\nState: %s ",head->info.state);
            printf("\nPhone number: %s ",head->info.phone);
            printf("\nPassport ID: %s ",head->info.passportID);
            char enter;
            scanf("%c",&enter);

            switch(n){
            case 0:
                return;
            case 1:{
                printf("\n\nModifying full name\n\nInsert the correct full name: \n");
                scanf("%[^\n]%*c",head->info.name);
                break;}
            case 2:{
                printf("\n\nModifying state\n\nInsert your state: \n");
                scanf("%s",head->info.state);
                break;}
            case 3:{
                printf("\n\nModifying phone number\n\nInsert your name: \n");
                scanf("%s",head->info.phone);
                break;}
            case 4:{
                printf("\n\nModifying passport ID\n\nInsert your passport ID: \n");
                scanf("%s",head->info.passportID);
                break;}
            default:{
                printf("\nWrong option!\nInsert again.");
                break;}
            }

        }
        system("cls");
    }
}

void delay(int number_of_seconds){
    int milli_seconds = 1000 * number_of_seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds);
}

void ADDclient(struct Client ***head,char ID[]) {
    struct Client *NewClientNode, *curr,*prev;
    NewClientNode = (struct Client*)malloc(sizeof(struct Client));
    strcpy(NewClientNode->clientID,ID);
    printf("\nThe client's ID:");
    printf(" %s\n",NewClientNode->clientID);
    printf("\nEnter the name and surname:");
    scanf("%[^\n]%*c",NewClientNode->info.name);
    printf("\nEnter the client's passport ID:");
    scanf("%s",NewClientNode->info.passportID);
    printf("\nEnter the state:");
    scanf("%s",NewClientNode->info.state);
    printf("\nEnter the phone number:");
    scanf("%s", NewClientNode->info.phone);
    NewClientNode->rents=0;
    NewClientNode->next = NULL;
    curr = prev = *(*head);

    if(*head==NULL) {
        *(*head) = NewClientNode;
        printf("\nNew client data saved successfully!\n");
        return;
    }
    if (strcmpi(curr->clientID,NewClientNode->clientID)>0) {
        NewClientNode->next = curr;
        *(*head)= NewClientNode;
    }
    else{
        while ((curr != NULL) && (strcmpi(curr->clientID,NewClientNode->clientID)<0)) {
            prev = curr;
            curr = curr->next;
        }
        if (curr == NULL) {
            prev->next = NewClientNode;
        }
        else{
            prev->next = NewClientNode;
            NewClientNode->next = curr;
        }
    }
    printf("\nNew client data saved successfully!\n");
}

void SaveClientsToFile(struct Client *head, int cnt_client){
    FILE *fp=NULL;
    fp=fopen("clients.txt", "w");
    if(fp==NULL)
    {
        printf("\nCannot open file!");
        return;
    }
    fprintf(fp,"%d\n",cnt_client);
    if(cnt_client!=0)
    {
        while(head!=NULL)
        {
            fprintf(fp,"%s %s; %s %s %s %d\n",
                head->clientID,
                head->info.name,
                head->info.state,
                head->info.phone,
                head->info.passportID,
                head->rents);
            head=head->next;
        }
    }
    fclose(fp);
}

void ReadClientsFile(struct Client** head, int *cnt_client){
    FILE *fp = fopen("clients.txt", "r");
    if (fp == NULL) {
        printf("\nUnable to open the file.");
        return;
    }
    fscanf(fp,"%d\n",cnt_client);
    if (*cnt_client==0){
        printf("\nNo client's data saved in file! File is empty!");
        return;
    }

    struct Client* current = *head;
    struct Client* ADDclient;

    while (!feof(fp)) {
        ADDclient = (struct Client*)malloc(sizeof(struct Client));
    	ADDclient->next = NULL;
        fscanf(fp, "%s %[^;]%*c %s %s %s %d\n",
               ADDclient->clientID,
               ADDclient->info.name,
               ADDclient->info.state,
               ADDclient->info.phone,
               ADDclient->info.passportID,
               &ADDclient->rents);

        if (*head == NULL) {
        	*head = ADDclient;
    	} else {
		current->next = ADDclient;
        }
        current = ADDclient;
    }
    printf("\nAll client's data were saved from file!");
    fclose(fp);
}

void AvailableVehiclesCurr(struct Vehicle *head) {
    int availvcnt = 0;
    struct Vehicle *curr = head;

    printf("The available vehicles are:\n");

    while (curr != NULL) {
        if(curr->reserved==0){
            printf("Model: %-16s\t", curr->model);
            printf("Plate Number: %s\t", curr->plateNumber);
            printf("Year: %d\t", curr->year);
            printf("Fuel: %-8s\t", curr->fuel);
            printf("Consumption: %.3f\t", curr->consumption);
            printf("Seats: %d\t", curr->seats);
            printf("Daily Price (EUR): %d\n", curr->dailyPrice);
            availvcnt++;
        }
        curr = curr->next;
    }

    if(availvcnt==0)
        printf("Currently all vehicles have at least one reservation. :/ \n");
    else
        printf("There are currently %d vehicles with zero reservations!\n", availvcnt);
}

void SearchLicensePlate(struct Vehicle* head) {
    char licensefromuser[8];
    printf("Enter the license plate of the car you need: \n");
    scanf("%s", licensefromuser);

    struct Vehicle* curr = head;

    while (curr != NULL) {
        if (strcmp(curr->plateNumber, licensefromuser) == 0) {
            printf("\nWe have found your car!\n");
            printf("\nModel: %s\n", curr->model);
            printf("Plate Number: %s\n", curr->plateNumber);
            printf("Year: %d\n", curr->year);
            printf("Fuel: %s\n", curr->fuel);
            printf("Consumption: %.3f\n", curr->consumption);
            printf("Seats: %d\n", curr->seats);
            printf("Daily Price (EUR): %d", curr->dailyPrice);
            return;
        }
        curr = curr->next;
    }

    printf("\nVehicle not found. Check the entered license plate again!");
}

void sortVehicle_top3(struct Vehicle *head_V){

    struct Vehicle *print=head_V;

    if(head_V==NULL){
        printf("\nThere are no vehicles saved! Add vehicle data first!");
        return;
    }
    printf("\nThese are the top 3 most reserved cars at the moment:\n\n");
    //sort vehicle descending order
     while(head_V!=NULL){
        struct Vehicle *curr=head_V->next;
        while(curr!=NULL){
            if(head_V->reserved<curr->reserved){
                char plateNumber[8];
                strcpy(plateNumber,curr->plateNumber);
                int year=curr->year;
                char model[20];
                strcpy(model,curr->model);
                char fuel[20];
                strcpy(fuel,curr->fuel);
                float consumption=curr->consumption;
                int seats=curr->seats;
                int dailyPrice=curr->dailyPrice;
                int reserved=curr->reserved;

                strcpy(curr->plateNumber,head_V->plateNumber);
                curr->year=head_V->year;
                strcpy(curr->model,head_V->model);
                strcpy(curr->fuel,head_V->fuel);
                curr->consumption=head_V->consumption;
                curr->seats=head_V->seats;
                curr->dailyPrice=head_V->dailyPrice;
                curr->reserved=head_V->reserved;

                strcpy(head_V->plateNumber,plateNumber);
                head_V->year=year;
                strcpy(head_V->model,model);
                strcpy(head_V->fuel,fuel);
                head_V->consumption=consumption;
                head_V->seats=seats;
                head_V->dailyPrice=dailyPrice;
                head_V->reserved=reserved;
            }
            curr=curr->next;
        }
        head_V=head_V->next;
    }
    for(int i=0;i<3;i++){
        if(print!=NULL)
            printf("Plate Number:%s\tReservations:%d\n",print->plateNumber,print->reserved);
        print=print->next;
    }

}

void displayClients(struct Client *head){
    if(head==NULL){
        printf("\nNo client data saved at the moment!\n");
    }
    while(head!=NULL){
        printf("\n\tClientID:%s\
\tName: %-24s\
\tPassportID: %s\
\tState: %s\
\tPhone: %s\
\tRents: %d",head->clientID,head->info.name,head->info.passportID,head->info.state,head->info.phone,head->rents);
        head=head->next;
    }
}

void saveDataToFile(struct Damage damages[], int damageCount) {
    FILE *file = fopen("damages.txt", "w");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return;
    }
    for (int i = 0; i < damageCount; i++) {
        fprintf(file, "%d %s %s; %s %d\n", damages[i].damageID, damages[i].plateNumber,
                damages[i].description, damages[i].dateReported, damages[i].resolved);
    }
    fclose(file);
}

void display3rents(struct Client *head){
    int i=0;

    while(head!=NULL)
    {
        if(head->rents>=3)
        {
            printf("\n%s\t%-24s\t%d", head->clientID, head->info.name, head->rents);
            i++;
        }

        head=head->next;
    }
    if(i==0)
    {
        printf("\nAll current clients have less than 3 rents.\n");
    }
}

void searchResID(struct Reservation *head){
    printf("\nInsert your reservation ID: ");
    int ID;
    scanf("%d", &ID);

    while (head!= NULL)
    {
        if(ID==head->resID){
            printf("\nWe found your reservation\n");
            printf("\nReservaton ID: %d", head->resID);
            printf("\nClient ID: %s", head->clientID);
            printf("\nBooked car: %s", head->plateNumber);
            printf("\nStart: %s",asctime(gmtime(&head->time_start)));
            printf("End: %s",asctime(gmtime(&head->time_end)));
            printf("Duration of your reservation: %d days", head->days);
            printf("\nReservation Price: %.3f EUR", head->price);
            return ;
        }
        head=head->next;
    }
    if ( head==NULL)
        printf("\nThere was no reservation found for this ID.\nCheck�again.\n");
}

void deleteReservation(struct Reservation **head_R, struct Vehicle *head_V, struct Client *head_C, int *cnt){
    if (head_R==NULL){
        printf("\nThere are no reservations on the system! There is nothing to delete!\n");
        return;
    }
    printf("\nInsert the reservation ID: ");
    int ID,x=0;
    scanf("%d",&ID);
    struct Reservation *searching,*curr,*prev;
    searching=curr=prev=*head_R;
    while(searching!=NULL){
        x++;
        if(ID==searching->resID)
            break;
        searching=searching->next;
    }
    if (searching==NULL){
        printf("\nNo reservation with such ID was found! Double check the reservation code.\n");
        return;
    }
    if (x==1){
        curr=(*head_R);
        (*head_R)=(*head_R)->next;
    }
    else {
        for(int i=1; i<x; i++){
            prev=curr;
            curr=curr->next;
        }
        prev->next=curr->next;
        curr->next=NULL;
    }
    while(head_V!=NULL){
        if (strcmp(curr->plateNumber,head_V->plateNumber)==0){
            (head_V->reserved)--;
            break;
        }
        head_V=head_V->next;
    }
    while(head_C!=NULL){
        if(strcmp(curr->clientID,head_C->clientID)==0){
            (head_C->rents)--;
            break;
        }
        head_C=head_C->next;
    }
    free(curr);
    (*cnt)--;
    printf("\nThe reservation was deleted!");
}

void exceedingcost(struct Reservation *head){
    printf("\nEnter the cost: ");
    float cost;
    scanf("%f", &cost);
    FILE *fp=NULL;
    fp=fopen("cost.txt","w");
    if(fp==NULL){
        printf("\nCannot open file");
        return;
    }
    while(head!=NULL){
        if(cost<head->price)
            fprintf(fp,"%d %s %s %d %d %d %d %lld %lld %f\n",
                    head->resID,
                    head->clientID,
                    head->plateNumber,
                    head->days,
                    head->date,
                    head->month,
                    head->year,
                    head->time_start,
                    head->time_end,
                    head->price);
        head=head->next;
    }
     fclose(fp);
     printf("\nData saved in file. Open file cost.txt to view data after closing program.");
}

void modifyvehicle(struct Vehicle *head){
    printf("\nInsert the plate number: ");
    char number[8];
    scanf("%s",number);
    while(head!= NULL)
    {
        if (strcmpi(number,head->plateNumber)==0)
        break;
        head=head->next;

    }
    if(head==NULL)
    {
        printf("\nNo vehicle with this plate number was found\n");
        return;
    }
    else
    {
        int n=0;
        while(1)
        {
            printf("\n1-Modify Model\n2-Modify Year\n3-Modify Fuel\n4-Modify Consumption\n5-Modify Seats\n6-Modify Daily Price\n0-Stop modifying\n");
            printf("\n\n\nEnter option: ");
            scanf("%d", &n);
            system("cls");

            printf("\nPlate number: %s ",head->plateNumber);
            printf("\nModel: %s ",head->model);
            printf("\nYear: %d ",head->year);
            printf("\nFuel: %s ",head->fuel);
            printf("\nConsumption: %.3f ",head->consumption);
            printf("\nSeats: %d ",head->seats);
            printf("\nDaily Price (EUR): %d ",head->dailyPrice);


            switch(n)
            {
                case 0:
                    return;
                case 1: {
                    printf("\n\nModifying model\n\nInsert the new model type: \n");
                    scanf("%s",head->model);
                    break;}
                case 2: {
                    printf("\n\nModifying year\n\nInsert the new year: \n");
                    scanf("%d",&head->year);
                    break;}
                case 3: {
                    printf("\n\nModifying fuel\n\nInsert the new fuel type: \n");
                    scanf("%s",head->fuel);
                    break;}
                case 4: {
                    printf("\n\nModifying consumption\n\nInsert consumption: \n");
                    scanf("%f",&head->consumption);
                    break;}
                case 5: {
                    printf("\n\nModifying seats\n\nInsert the new number of seats: \n");
                    scanf("%d",&head->seats);
                    break;}
                case 6: {
                    printf("\n\nModifying price. Existing reservations will not be affected by the price change.\n\nInsert the new daily price: \n");
                    scanf("%d",&head->dailyPrice);
                    break;}
                default:{
                    printf("\n\nWrong option!\nInsert again.");
                    break;}
            }
            system("cls");
        }
    }
}

void searchclientbyID(struct Client *head){
    struct Client *search_C=NULL;
    struct Client *left, *right=NULL;
    left=head;
    char ID[11];
    int found=0;
    printf("\nInsert your ID: ");
    scanf("%s", ID);
    while (left != right)
    {
        struct Client* middle = left;
        struct Client* last = left;

        while (last != right && last->next != right)
        {
            middle = middle->next;
            last = last->next->next;
        }
        search_C=middle;
        if (strcmpi(search_C->clientID,ID)==0)
        {
            search_C = middle;
            search_C->rents++;
            found++;
            break;
        }
        else if (strcmpi(search_C->clientID,ID)<0)
        {
            left = middle->next;
        }
        else
        {
            right = middle;
        }
    }
    if(found==0)
    {
        printf("\nCouldn't find any client data with this ID!\n");
        return;
    }
    else
    {
        printf("\nWe found your data!\n");
        printf("\nClient ID: %s", search_C->clientID);
        printf("\nClient Name: %s", search_C->info.name);
        printf("\nClient State: %s", search_C->info.state);
        printf("\nClient Phone number: %s", search_C->info.phone);
        printf("\nClient Passport ID: %s", search_C->info.passportID);
    }
}

void reportDamage(struct Damage damages[], int *damageCount,struct Vehicle *head) {
    if (*damageCount >= MAX_DAMAGES) {
        printf("Maximum damage report limit reached. Unable to report more damages.\n");
        return;
    }

    struct Damage newDamage;

    printf("Enter the vehicle plate number: ");
    scanf("%s", newDamage.plateNumber);
        while(head!= NULL)
    {
        if (strcmpi(newDamage.plateNumber,head->plateNumber)==0)
        break;
        head=head->next;

    }
    if(head==NULL)
    {
        printf("\nNo vehicle with this plate number was found\n");
        return;
    }
    printf("Enter the description of the damage: ");
    scanf(" %[^\n]%*c", newDamage.description);

    printf("Enter the date reported (DD/MM/YYYY): ");
    scanf("%[^\n]%*c", newDamage.dateReported);

    newDamage.damageID = *damageCount + 1;
    newDamage.resolved=false;
    damages[*damageCount] = newDamage;
    (*damageCount)++;
}

void displayDamageHistory(struct Damage damages[], int damageCount) {
    printf("Damage History\n");
    printf("--------------\n");

    for (int i = 0; i < damageCount; i++) {
        printf("Damage ID: %d\n", damages[i].damageID);
        printf("Vehicle Plate Number: %s\n", damages[i].plateNumber);
        printf("Description: %s\n", damages[i].description);
        printf("Date Reported: %s\n", damages[i].dateReported);
        printf("Status: %s\n", damages[i].resolved ? "Resolved" : "Unresolved");
        printf("--------------\n");
    }
}

void updateDamage(struct Damage damages[], int damageCount, int damageID) {
    char temp[200],no[]="no";
    for (int i = 0; i < damageCount; i++) {
        if (damages[i].damageID == damageID) {
            printf("Enter the updated description of the damage (or enter 'no' to keep the existing description): ");
            scanf(" %[^\n]%*c", temp);
            if(strcmpi(temp,no)!=0)
                strcpy(damages[i].description,temp);
            printf("Is the damage resolved? (1 for Yes, 0 for No): ");
            scanf("%d", &damages[i].resolved);
            printf("Damage record updated successfully.\n");
            return;
        }
    }
    printf("Invalid damage ID. Unable to update damage record.\n");
}

void bubbleSortRES(struct Reservation *head){
    struct Reservation *head_R=head;
    while(head_R!=NULL){
        struct Reservation *curr=head_R->next;
        while(curr!=NULL){
            if(strcmpi(curr->plateNumber,head_R->plateNumber)<0){
                char clientID[11];
                strcpy(clientID,curr->clientID);
                int resID=curr->resID;
                char plateNumber[8];
                strcpy(plateNumber,curr->plateNumber);
                int days=curr->days;
                int date=curr->date;
                int month=curr->month;
                int year=curr->year;
                time_t time_start=curr->time_start;
                time_t time_end=curr->time_end;
                float price=curr->price;

                strcpy(curr->clientID,head_R->clientID);
                curr->resID=head_R->resID;
                strcpy(curr->plateNumber,head_R->plateNumber);
                curr->days=head_R->days;
                curr->date=head_R->date;
                curr->month=head_R->month;
                curr->year=head_R->year;
                curr->time_start=head_R->time_start;
                curr->time_end=head_R->time_end;
                curr->price=head_R->price;

                strcpy(head_R->clientID,clientID);
                head_R->resID=resID;
                strcpy(head_R->plateNumber,plateNumber);
                head_R->days=days;
                head_R->date=date;
                head_R->month=month;
                head_R->year=year;
                head_R->time_start=time_start;
                head_R->time_end=time_end;
                head_R->price=price;
            }
            curr=curr->next;
        }
        head_R=head_R->next;
    }
        head_R=head;
        while(head_R!=NULL){
        struct Reservation *curr=head_R->next;
        while(curr!=NULL){
            if(strcmpi(curr->plateNumber,head_R->plateNumber)==0&&curr->time_start<head_R->time_start){
                char clientID[11];
                strcpy(clientID,curr->clientID);
                int resID=curr->resID;
                char plateNumber[8];
                strcpy(plateNumber,curr->plateNumber);
                int days=curr->days;
                int date=curr->date;
                int month=curr->month;
                int year=curr->year;
                time_t time_start=curr->time_start;
                time_t time_end=curr->time_end;
                float price=curr->price;

                strcpy(curr->clientID,head_R->clientID);
                curr->resID=head_R->resID;
                strcpy(curr->plateNumber,head_R->plateNumber);
                curr->days=head_R->days;
                curr->date=head_R->date;
                curr->month=head_R->month;
                curr->year=head_R->year;
                curr->time_start=head_R->time_start;
                curr->time_end=head_R->time_end;
                curr->price=head_R->price;

                strcpy(head_R->clientID,clientID);
                head_R->resID=resID;
                strcpy(head_R->plateNumber,plateNumber);
                head_R->days=days;
                head_R->date=date;
                head_R->month=month;
                head_R->year=year;
                head_R->time_start=time_start;
                head_R->time_end=time_end;
                head_R->price=price;
            }
            curr=curr->next;
        }
        head_R=head_R->next;
    }
}

void newReservation (struct Client **head_C,struct Vehicle *head_V,struct Reservation **head_R,int *cnt, int *cntC,int today_time){
    struct Reservation *curr, *newRes;
    struct Vehicle *search_V;
    struct Client *search_C;
    int a=0;
    search_V=head_V;
    search_C=*head_C;
    curr=*head_R;

//check if vehicles list is empty
    if(search_V==NULL){
        printf("\nThere are no vehicles saved on the system! Add a vehicle first!");
        return;
    }
//create the new node for res
    (*cnt)++;
    newRes = (struct Reservation*) malloc(sizeof(struct Reservation));
    newRes->next=NULL;
    newRes->resID=0;
    for(int i=0;i<6;i++){
        newRes->resID+=(1+rand()%9)*pow(10,i);}
	printf("\nNew reservation ID:%d\n",newRes->resID);

//vehicle data check
    printf ("\nEnter car plate number: ");
    scanf("%s",newRes->plateNumber);
    a=strcmp(newRes->plateNumber,search_V->plateNumber);
    if (a==0){
        search_V->reserved++;
    }
    else{
        while(a!=0){
            while(search_V!=NULL){
                a=strcmp(newRes->plateNumber,search_V->plateNumber);
                if (a==0)
                    break;
                search_V=search_V->next;
            }
            if(a!=0){
                printf("\nNo vehicle with such plate number was found! Insert another plate number!");
                printf ("\nEnter car plate number: ");
                scanf("%s",newRes->plateNumber);
                search_V=head_V;
            }

        }
        search_V->reserved++;
    }

//client data check
    struct Client ***check=&head_C;
    printf("\nEnter clientID: ");
    scanf("%s",newRes->clientID);
    if (search_C==NULL){
        printf("\nThis is your first customer! Please insert information!\n");
        ADDclient(check,newRes->clientID);
        search_C=*head_C;
        search_C->rents++;
        (*cntC)++;
    }
    else {
        a=strcmp(newRes->clientID,search_C->clientID);
        if (a==0){
            search_C->rents++;
        }
        else{
            int found=0;
            while(found==0){
                struct Client *left, *right=NULL;
                left=*head_C;
                search_C=NULL; //kind of binary search for linked list
                while(search_C==NULL){
                    while (left != right) {
                        struct Client* middle = left;
                        struct Client* last = left;

                        while (last != right && last->next != right) {
                            middle = middle->next;
                            last = last->next->next;
                        }
                        search_C=middle;
                        if (strcmp(search_C->clientID,newRes->clientID)==0) {
                            search_C = middle;
                            search_C->rents++;
                            found=1;
                            break;
                        } else if (strcmp(search_C->clientID,newRes->clientID)<0) {
                            left = middle->next;
                        } else {
                            right = middle;
                        }
                    }
                    if(found==0){
                        printf("\nWe don't have your data saved in system! Please insert information!\n");
                        ADDclient(check,newRes->clientID);
                        (*cntC)++;
                    }
                }
            }
        }
    }
//reservation details (date&days) & calendar implementation
    do{
    printf("\nThe month: ");
    scanf("%d",&newRes->month);
    while(newRes->month<0||newRes->month>12){
        printf("\nIncorrect month! Insert month again: ");
        scanf("%d",&newRes->month);
    }
    printf("\nThe date: ");
    scanf("%d", &newRes->date);
    while(newRes->date <= 0 || newRes->date > 31 || ((newRes->month == 4 || newRes->month == 6 || newRes->month == 9 || newRes->month == 11) && newRes->date == 31) || (newRes->month == 2 && newRes->date > 28)) {
        printf("\nIncorrect date! Insert date again: ");
        scanf("%d", &newRes->date);
    }
    printf("\nThe year: ");
    scanf("%d",&newRes->year);

    printf("\nNumber of days: ");
    scanf("%d",&newRes->days);
    //calendar system implementation
    struct tm day={0, 0, 0, newRes->date, (newRes->month)-1, (newRes->year)-1900 };
    time_t one_day=86400;
    time_t days=one_day*((newRes->days)-1);

    newRes->time_start =mktime(&day)+3600;
    newRes->time_end=(newRes->time_start)+82800+days;
    if(newRes->time_start<today_time)
        printf("Can't make past date reservation! Insert data again!");}while(newRes->time_start<today_time);

//price 2 options
    if(newRes->days==7)
        newRes->price=search_V->dailyPrice*newRes->days*0.9;
    else if(newRes->days==14)
        newRes->price=search_V->dailyPrice*newRes->days*0.85;
    else if(newRes->days==30||newRes->days==31)
        newRes->price=search_V->dailyPrice*newRes->days*0.80;
    else
        newRes->price=(float)search_V->dailyPrice*newRes->days;
    printf("\nReservation price: %.2lf EUR",newRes->price);

    struct tm *ptm1 = gmtime(&newRes->time_start);
    printf("\n\n%s",asctime(ptm1));
    printf("\n%s",asctime(gmtime(&newRes->time_end)));

//add node with insertion to have sorted list (based on 2 conditions - res time and vehicle plate)
    if(*head_R==NULL){
        *head_R=newRes;
        return;
    }
    curr=*head_R;
    while(curr->next!=NULL){
        curr=curr->next;
    }
    curr->next=newRes;
}

void displayReservation(struct Reservation *head){
    if(head==NULL){
        printf("\nNo reservations made at the moment!\n");
    }
    while(head!=NULL){
        printf("\n\tResID:%d\
\tClient ID:%s\
\tBooked Car:%s\
\tDate (MM/DD/YYYY):%d/%d/%d\
\tTotal Days:%d\
\tReservation Price (EUR):%.2f",head->resID,head->clientID,head->plateNumber,head->month,head->date,head->year,head->days,head->price);
        head=head->next;
    }
}

void vehiclesAvailFuture(struct Reservation *head_R,struct Vehicle *head_V,time_t today_time){

    if (head_V==NULL){
        printf("No data for vehicles saved! Please save data first!");
        return;
    }
    if (head_R==NULL){
        printf("There are no reservations made. All cars are available.");
        return;
    }
    printf("\nInsert the information:");
    int month,date,year,nr_days;
    time_t start,end;
    do{
    printf("\nThe month: ");
    scanf("%d",&month);
    while(month<0||month>12){
        printf("\nIncorrect month! Insert month again: ");
        scanf("%d",&month);
    }
    printf("\nThe date: ");
    scanf("%d", &date);
    while(date <= 0 || date > 31 || ((month == 4 || month == 6 || month == 9 || month == 11) && date == 31) || (month == 2 && date > 28)) {
        printf("\nIncorrect date! Insert date again: ");
        scanf("%d", &date);
    }
    printf("\nThe year: ");
    scanf("%d",&year);
    printf("\nNumber of days: ");
    scanf("%d",&nr_days);

    struct tm day={0, 0, 0, date, (month)-1, (year)-1900 };
    time_t one_day=86400;
    time_t days=one_day*(nr_days);

    start=mktime(&day)+3600;
    end=(start)+days;
    if (start<today_time)
        printf("\nCan't check for a past date! please insert data again.");
    }while(start<today_time);

    struct Vehicle *search_V;
    struct Reservation *search_R;
    search_V=head_V;
    search_R=head_R;


    int i=0,cnt=0;
    while(search_V!=NULL){
        while(search_R!=NULL){
            if (strcmp(search_V->plateNumber,search_R->plateNumber)==0&&((start<search_R->time_start&&end<=search_R->time_start)||(start>=search_R->time_end&&end>search_R->time_end)))
                search_R=search_R->next;
            else if (strcmp(search_V->plateNumber,search_R->plateNumber)!=0)
                search_R=search_R->next;
            else {
                i++;
                break;
            }
        }
        search_R=head_R;
        if (i==0||search_V->reserved==0){
            printf("\nVehicle plate number: %s",search_V->plateNumber);
            cnt++;
        }
        i=0;
        search_V=search_V->next;
    }
    if (cnt==0)
        printf("\nNo vehicles available for this time period!");
}

void deleteVehicle(struct Vehicle **head,struct Reservation **head_R,struct Client *head_C, int *cnt_V, int *cnt_R){
    char find[8];
    int x=0,a=1;
    struct Vehicle *curr,*prev,*searching;
    curr=prev=searching=*head;
    struct Reservation *searching_R,*prev_R, *curr_R;
    curr_R=prev_R=searching_R=*head_R;

    if((*head)==NULL){
        printf("\nNo vehicle saved in system! There is nothing to delete.");
        return;
    }

    printf("\nInsert vehicle plate number:");
    scanf("%s",find);

    while(searching!=NULL){
        x++;
        a=strcmp(find,searching->plateNumber);
        searching=searching->next;
        if(a==0)
            break;
    }
    if(a!=0){
        printf("\nNo vehicle with such plate number was found!");
        return;
    }
    if (x==1){
        curr=(*head);
        (*head)=(*head)->next;
    }
    else {
        for(int i=1; i<x; i++){
            prev=curr;
            curr=curr->next;
        }
        prev->next=curr->next;
        curr->next=NULL;
    }


    x=0;
    while(searching_R!=NULL){
        while(searching_R!=NULL){
            x++;
            if(strcmp(searching_R->plateNumber,curr->plateNumber)==0){
                    while(head_C!=NULL){
                        if(strcmp(searching_R->clientID,head_C->clientID)==0){
                            (head_C->rents)=(head_C->rents)-1;
                            break;
                        }
                        head_C=head_C->next;
                    }
                break;
            }
            searching_R=searching_R->next;
        }
        if(searching_R==NULL)
            break;
        else if(x==1){
            prev_R=(*head_R);
            (*head_R)=(*head_R)->next;
            prev_R->next=NULL;
            free(prev_R);
            (*cnt_R)--;
            x=0;
            searching_R=*head_R;
        }
        else {
            for(int i=1; i<x; i++){
                prev_R=curr_R;
                curr_R=curr_R->next;
            }
            prev_R->next=curr_R->next;
            curr_R->next=NULL;
            free(curr_R);
            (*cnt_R)--;
            x=0;
            searching_R=*head_R;
        }
    }
    free(curr);
    (*cnt_V)--;
    printf("\nThe Vehicle was deleted!");
}

void saveREStoFile(struct Reservation *head, int cnt){
    FILE *fp=NULL;
    fp=fopen("reservations.txt", "w");
    if(fp==NULL)
    {
        printf("\nCannot open file!");
        return;
    }
    fprintf(fp,"%d\n",cnt);
    if(cnt!=0)
    {
        while(head!=NULL)
        {
            fprintf(fp,"%d %s %s %d %d %d %d %lld %lld %.3f\n",head->resID,head->clientID,head->plateNumber,head->days,head->date,head->month,head->year,head->time_start,head->time_end,head->price);
            head=head->next;
        }
    }
    fclose(fp);
}

void readReservationsFromFile(struct Reservation** head, int *cnt) {
    FILE *fp = fopen("reservations.txt", "r");
    if (fp == NULL) {
        printf("\nUnable to open the file.");
        return;
    }
    fscanf(fp,"%d\n",cnt);
    if (*cnt==0){
        printf("\nNo reservations saved in file! File is empty!");
        return;
    }

    struct Reservation* current = *head;
    struct Reservation* newRES;

    while (!feof(fp)) {
        newRES = (struct Reservation*)malloc(sizeof(struct Reservation));
    	newRES->next = NULL;
        fscanf(fp, "%d %s %s %d %d %d %d %lld %lld %f\n",
               &newRES->resID,
               newRES->clientID,
               newRES->plateNumber,
               &newRES->days,
               &newRES->date,
               &newRES->month,
               &newRES->year,
               &newRES->time_start,
               &newRES->time_end,
               &newRES->price);

        if (*head == NULL) {
        	*head = newRES;
    	} else {
		current->next = newRES;
        }
        current = newRES;
    }
    printf("\nAll reservations were saved from file!");
    fclose(fp);
}

void displayResCalendarForVehicle(struct Vehicle *head_V, struct Reservation *head_R, time_t today_time) {
    if (head_V == NULL) {
        printf("\nThere are currently no vehicles saved in the system. Save vehicle information first.\n");
        return;
    }

    printf("\nEnter the vehicle plate number you want to check: ");
    char ID[8];
    scanf("%s", ID);

    struct Vehicle *currentVehicle = head_V;
    while (currentVehicle != NULL) {
        if (strcmp(currentVehicle->plateNumber, ID) == 0)
            break;
        currentVehicle = currentVehicle->next;
    }

    if (currentVehicle == NULL) {
        printf("\nNo vehicle with the provided plate number was found! Please double-check the plate number.\n");
        return;
    }

    int month_days, month, year;
    time_t end_month, start_month;
    do {
        printf("\nEnter the month you want to check: ");
        scanf("%d", &month);
        printf("Enter the year you want to check: ");
        scanf("%d", &year);

        if (month == 4 || month == 6 || month == 9 || month == 11)
            month_days = 30;
        else if (month == 2 && (year % 4) == 0)
            month_days = 29;
        else if (month == 2 && (year % 4) != 0)
            month_days = 28;
        else
            month_days = 31;

        struct tm day = {0, 0, 0, 1, month - 1, year - 1900};
        time_t days = 86400 * month_days;
        start_month = mktime(&day)+3600;
        end_month = start_month + days;
        if (end_month < today_time)
            printf("\nYou can't search for a past month! Please insert the month and year again.\n");
    } while (end_month < today_time);

    ///Formula used to find out the day of the week for a given date
    ///the months are considered starting from 1-MAR 2-APR ... 11-JAN 12-FEB
    int m;
    if (month == 1)
        m = 11;
    else if (month == 2)
        m = 12;
    else
        m = month - 2;
    int F = abs((1 + ((13 * m - 1) / 5) + (year % 100) + ((year % 100) / 4) + ((year / 100) / 4) - 2 * (year / 100)) % 7);
    ///the result will be a number from 0 to 6 where 0-SUN 1-MON ... 5-FRI 6-SAT
    if(F==0){
        F=7; ///We need sunday to be 7 for the "empty days" loop at the beginning of month
    }

    if (currentVehicle->reserved == 0) {
        printf("\n  M    T    W    T    F    S    S\n");
        for (int i = 1; i < F; i++)
            printf("     ");
        for (int i = 1; i <= month_days; i++) {
            printf("%3d -", i);
            if ((F + i - 1) % 7 == 0)
                printf("\n");
        }
        return;
    }

    int res_start[currentVehicle->reserved];
    int res_end[currentVehicle->reserved];
    int i = 0;

    struct Reservation *currentReservation = head_R;
    while (currentReservation != NULL) {
        if (strcmp(ID, currentReservation->plateNumber) == 0) {
            res_start[i] = currentReservation->time_start;
            res_end[i] = currentReservation->time_end;
            i++;
        }
        currentReservation = currentReservation->next;
    }

    int j = 0;
    printf("\n  M    T    W    T    F    S    S\n");
    for (int i = 1; i < F; i++)
        printf("     ");///prints empty days at start of month
    for (int i = 1; i <= month_days; i++) {
        if (start_month > res_start[j] && start_month > res_end[j]&&j<(currentVehicle->reserved)) {
            j++;///If the current checking data range is from a previous month we need to skip and check next
            ///this will be done for as long as needed or until reaching last index. if all reservations in prev months
            ///we keep the last reservation date and print the empty calendar based on the last else if
            i--;///decrement i since no date was printed
        } else if (start_month < res_start[j]) {
            printf("%3d -", i);
            start_month += 86400;///increment the time by 1 day to check following day avail
            if ((F + i - 1) % 7 == 0)
                printf("\n");
        } else if (start_month >= res_start[j] && start_month <= res_end[j]) {
            printf("%3d +", i);
            start_month += 86400;
            if ((F + i - 1) % 7 == 0)
                printf("\n");///after the 7th days prints a new line
        } else if (start_month > (res_end[j])&&j<(currentVehicle->reserved)) {
                j++; ///after starting day has been incremented and passes the first reservation time range
                ///we need to update and check for the next reservations range to see if we have other reserved days for that month
                i--;///decrement i since no date was printed in this iteration
        } else if (start_month>res_start[j]&&start_month>res_end[j]){
            printf("%3d -", i);///if there are no more reservations and the lates date is less than the current month
            start_month += 86400;///itll print an empty calendar
            if ((F + i - 1) % 7 == 0)
                printf("\n");
        }
    }
}

void loadDataFromFile(struct Damage damages[], int *damageCount) {
    FILE *file = fopen("damages.txt", "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return;
    }
    while ((*damageCount < MAX_DAMAGES) && (fscanf(file, "%d %s %[^;]%*c %s %d\n",
                                                 &damages[*damageCount].damageID,
                                                 damages[*damageCount].plateNumber,
                                                 damages[*damageCount].description,
                                                 damages[*damageCount].dateReported,
                                                 &damages[*damageCount].resolved) == 5)) {
        (*damageCount)++;
    }
    fclose(file);
}

#endif // STRUCTURES_H_INCLUDED