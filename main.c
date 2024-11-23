//Waad Ala' Ziadeh
// 1220423
//sec 5: Dr.Ahmad abo sninah

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

int load=0; // global variable to check if the user enter 1 to load info or not
struct Town {
    int population;
    char T_name[50];
    struct Town* link;
};
struct District {
    int total_pop;
    char name [50]; //define a string with maximum 50 characters
    struct Town* towns; // Pointer to the first town in the district
    struct District* next;
    struct District* Previous;
};
struct District* findDistrictByName(char* name);
void printDistrictsToFile2(struct District* District_head, const char* stored_district);
void insertDistrict(char x[],struct District*L);

struct District * District_head;
struct Town * town_head ;

void printMenu();

/*1*/  void readFileAndStore(const char* );
struct District* insertandCreateDistrict(char* );
struct Town* insertTownToDistrict(struct Town* , char* , int );
void printDistrictsAndTowns();

/*2*/  void displayAll(struct District * );

/*3*/void RadixSort(struct District* );
void Addstars(struct District*);
void Removestars(struct District* );
struct District * findDistrict(char x[],struct District *L);
void deleteTown(struct District* , char* , char* );
int isEmpty(struct District* D);
void DeleteList(struct District* L);
struct District* makeEmpty(struct District* L);
int getMaxLengthDistrict(struct District* L);
struct District* findLastDistrict(struct District*L);

/*4*/ void sortedPopulation ();
void swapLinkedList(struct Town*  , struct Town* );
void BubbleSortForPopulation (struct District* district);

/*5*/ void printSortedInfo();

/*6*/ void addDistrict();
struct District* insertandCreateDistrict(char* );

/*7*/ void addTowntoCertainDistrict();
bool searchTown(struct District* district, char* townName);
void addTownToDistrict2(struct District* district, struct Town* town);
struct Town* InsertTown();
struct District* findDistrictByName(char* name);

/*8*/ void deleteTownFromCertainDistrict(struct District* );
     void deleteTown(struct District* , char* , char* );

/*9*/ void deleteCertainDistrict();
      void deleteDistrictwithTowns(char*);

/*10*/ void CalculatePopulation();

/*11*/ void printPopandDistrict();

/*12*/void NewPopulation();

/*13*/void printDistrictsToFile(struct District* , const char* );

/*14*/ //exit

struct Town* InsertTown();
int main() {

    int option;
    while(1) { // to make the menu keeps appearing
        printMenu(); // Display application menu
        printf("Enter your option: \n");
        scanf("%d", &option); // Scan the option selected by the user

        switch(option){
            case 1: readFileAndStore("disricts.txt");
                break;
            case 2: displayAll(District_head);
                break;
            case 3:  RadixSort(District_head);
                break;
            case 4:  sortedPopulation ();
                break;
            case 5: printSortedInfo();
                break;
            case 6: addDistrict();
                break;
            case 7:  addTowntoCertainDistrict();
                break;
            case 8: deleteTownFromCertainDistrict( District_head);
                break;
            case 9:deleteCertainDistrict();
                break;
            case 10:CalculatePopulation();
                break;
            case 11:printPopandDistrict();
                break;
            case 12:NewPopulation();
                break;
            case 13:  printDistrictsToFile( District_head, "stored_districts");
                break;
            case 14: printf("Good Bye");
                exit(0); // exit when choose 14
            case 15:  printDistrictsToFile(District_head,  "stored_district.txt");
                break;
            default:printf("This option not valid try again \n"); break;

        }}
    return 0;

}
/////////////////////////////
// Function to display menu
void printMenu()
{
    printf(" \n  Menu of my application\n");
    printf("1-load the input file(Palestinian districts and their town with population)\n");
    printf("2-Print the loaded information before sorting(as in the input file format)\n");
    printf("3-Sort the districts alphabetically using Radix sort\n");
    printf("4-Sort the towns for each district based on population in ascending order.\n");
    printf("5-Print the sorted information\n");
    printf("6-Add a new district to the list of sorted districts (and sort the list)\n");
    printf("7-Add a new town to a certain district\n");
    printf("8-Delete a town from a specific district\n");
    printf("9-Delete a complete district\n");
    printf("10-Calculate the population of Palestine, the max and min town population\n");
    printf("11-Print the districts and their total population\n");
    printf("12-Change the population of a town\n");
    printf("13-Save to output file\n");
    printf("14-Exit\n");
}
////////////////////////////////////////////////////////
//Function to load the information by to read from file then store the data in doubly linked list (District) and linked list (town)
void readFileAndStore(const char* districts) {
            //1. Load the input file (Palestinian districts and their town with population).
    char line[256];
    char Dname[50];
    char Tname[50];
    int pop ;
    int count=0;

    FILE *file = fopen("districts.txt", "r"); // open the file to read
    if (!file) {
        printf("Error opening file\n");
        return;
    } else {
        printf("File loaded\n");
    }
// read thw whole line and calculate the letters in the lines and yhe number of lines
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
      /*  printf(" %s\n", line); //print lines*/
        count++; // number of lines increment
// split the lines depending on the "|" and store each word in specific string
        char *token = strtok(line, "|");
        strcpy(Dname, token);
        token = strtok(NULL, "|");
        strcpy(Tname, token);
        token = strtok(NULL, "|");
        pop = atoi(token);
       /* printf("\t %s \n ",Dname);
        printf("\t %s \n ",Tname);
        printf("\t %d \n ",pop);*/
// insert the name of district and there townes and there population to linked list
        struct District* district = insertandCreateDistrict(Dname); // call the function to create and insert the district
       district->towns = insertTownToDistrict(district->towns, Tname, pop); // call the function to create and insert the Town
        district->total_pop += pop; // increment the total population

    }
++load ; // variable if increment means the user load the file in the beginning if didn't change the program will tell the user to load information
   //printDistrictsAndTowns(); // this function to see the data after we store it
    fclose(file);
}
////////////////////////////////////
//this function to insert the districts to the linked list
struct District* insertandCreateDistrict(char* D_name) {
    struct District* dis  = District_head;
    struct District* tempdis = NULL;
    while (dis != NULL) {
        if (strcmp(dis->name, D_name) == 0) { // search the district in the first (if found don't add it if not found add it ) by the string compare
            return dis; // if found the district return it
        }
        tempdis = dis;//make pointer temp dis in the same pos of dis
        dis = dis->next;// go to next district
    }

    struct District* newDistrict = (struct District*)malloc(sizeof(struct District)); // creation a district
    strcpy(newDistrict->name, D_name); // copy the new name to the district name in linked list (save the name)
    newDistrict->towns = NULL; // make towns null
    newDistrict->total_pop = 0;// make the population zero
    newDistrict->next = NULL; // make next equal null
    newDistrict->Previous = tempdis; // make previous equal temp dis

    if (tempdis) {
        tempdis->next = newDistrict;
    } else { // if null add in the beginning
        District_head = newDistrict;
    }
    return newDistrict;//return the new district
}

///////////////////////////////////////////////
//funtion to add the towns to their districts
struct Town* insertTownToDistrict(struct Town* head, char* T_name, int population) {
    struct Town* newTown = (struct Town*)malloc(sizeof(struct Town)); // creat the town
    strcpy(newTown->T_name, T_name); // copy the new name to the district name in linked list (save the name)
    newTown->population = population; // save the population
    newTown->link = head; // make the head pointer to the link
    return newTown; // return the new town
}
//////////////////////////////////
// this function i use it in the read and store function to can see the data after enter the linked list
void printDistrictsAndTowns() {
    struct District *district  = District_head;
    while (district != NULL) {
        printf(" %s, Population: %d\n", district->name, district->total_pop);
        struct Town *currentTown = district->towns;
        while (currentTown != NULL) {
            printf("\t %s,%d\n", currentTown->T_name, currentTown->population);
            currentTown = currentTown->link;//go to next town
        }
        district = district->next;//go to next district
    }
}
///////////////////////////////////////
//function to print the data after store it
    void displayAll(struct District* districts) {
    //2. Print the loaded information before sorting (as in the input file format).
    if(load ==0 ){ // u can't choose  this function before load the information
        printf("  U didn't load the info , please load the it \n ");
    }
        struct District* head = districts;
        while (head != NULL) {
            printf("-District: %s \n", head->name);
            struct Town* currentTown = head->towns;

            while (currentTown != NULL) {
                printf("%s, %d\n", currentTown->T_name, currentTown->population);
                currentTown = currentTown->link;
            }
            printf("\n");
            head = head->next; // Assuming districts are in a linked list
        }
    }
    ////////////////////////////////////
    //Function to sort the districts name by radix sort
    void RadixSort(struct District* L) {
      // 3. Sort the districts alphabetically using Radix sort.
        if (load == 0)
        {
            printf(" U didn't load the info , please load the it \n");

        }
        else {
            struct District* temp;
            struct District *PinL;
            struct District *NewList;
            char currentCharacter;

            int i, j, z, x = getMaxLengthDistrict(L), index;
            Addstars(L); // make all strings same length
            struct District* RadixSortArray[53]; // make array of linked list
            temp = L->next;
            for (i = x - 1; i >= 0; i--) {
                for (j = 0; j < 53; j++) {
                    RadixSortArray[j] = makeEmpty(NULL);// make the array empty to can store data in it
                }
                while (temp != NULL) {
                    currentCharacter = temp->name[i];
                    if (currentCharacter == '*') { // make index=0 is a star
                        index = 0;
                    }

                    else if (isupper(currentCharacter)) {// from index 1 to 26 store the capital letters
                        index = currentCharacter - 'A' + 1;
                    }
                    else if (islower(currentCharacter)) {// from index 27 to 53 store the smaller letters
                        index = currentCharacter - 'a' + 27;
                    }
                    insertDistrict(temp->name, RadixSortArray[index]); // insert the data in the temp name
                    temp = temp->next; // first time the word hebron will on n and gaza , jenin in star , jerusalem in m
                }

                NewList = makeEmpty(NULL);//make the new list empty to can fill it with data
                for (z = 0; z < 63; z++) {
                    temp = RadixSortArray[z]->next;
                    while (temp != NULL) {
                        insertDistrict(temp->name, NewList);
                        // to can connect sort districts with its towns
                        struct District* LastAdded = findDistrict(temp->name, NewList);
                        PinL = findDistrict(temp->name, L);
                        LastAdded->total_pop = PinL->total_pop; // Copy total population
                        temp = temp->next;
                    }
                }
                temp = NewList->next;
            }

            L->next = NewList->next;
            Removestars (L); // remove the stars
            for (i = 0; i < 63; i++) {
                RadixSortArray[i]->next = NULL;
            }

        }
        printf(" Done ");
        displayAll(L);
}
//////////////////////////////////////////
//Function to make all strings same length
void Addstars(struct District* L) {
    struct District* temp = L->next;
    int MaxLength = getMaxLengthDistrict(L);
    int LengthOfDistrict, NumOfSpacesToAdd, i;
    while (temp != NULL) {
        LengthOfDistrict = strlen(temp->name);
        NumOfSpacesToAdd = MaxLength - LengthOfDistrict;
        for (i = 0; i < NumOfSpacesToAdd; i++) {
            strcat(temp->name, "*");
        }
        temp = temp->next;
    }
}
///////////////////////////////////////
struct District* findLastDistrict(struct District* L) {
    struct District* p =L->next ;
}
////////////////////////////////////////
//function to remove stars
void Removestars(struct District* L) {
    struct District* temp = L->next;
    int NumOfSpaces = 0, sizeOfDistrict = sizeof(temp->name), MaxLength = getMaxLengthDistrict(L), LengthOfDistrict, i;
    while (temp != NULL) {
        LengthOfDistrict = strlen(temp->name);
        for (i = 0; i < LengthOfDistrict; i++) {
            if (temp->name[i] == '*') {
                NumOfSpaces++;
            }
        }
        temp->name[sizeOfDistrict - (sizeOfDistrict - (LengthOfDistrict - NumOfSpaces))] = '\0';
        temp = temp->next;
        NumOfSpaces = 0;
    }
}
///////////////////
int isEmpty(struct District* D) {
    return D->next == NULL && D->Previous == NULL;
}
///////////////////////////
void insertDistrict(char x[], struct District* L) {
    struct District* temp, *p;
    temp = (struct District*)malloc(sizeof(struct District));
    if (temp != NULL) {
        strcpy(temp->name, x);
        if (L->next != NULL) {
            p = findLastDistrict(L);
        }
        else
            p = L;
    }
    temp->next = p->next;
    temp->Previous = p;
    p->next = temp;
}
/////////////////////////////////////
//Function to make the lists empty
struct District* makeEmpty(struct District* L) {
    if (L != NULL)
        DeleteList(L);

    L = (struct District*)malloc(sizeof(struct District));
    if (L == NULL) {
        printf("Out of memory!\n");
        return NULL;
    }

    L->next = NULL;
    L->Previous = NULL;

    return L;
}
/////////////////////////
//Function delete the list
void DeleteList(struct District* L) {
    struct District* current = L;
    struct District* nextN;

    while (current != NULL) {
        nextN = current->next;
        free(current);
        current = nextN;
    }

    L->next = NULL;
    L->Previous = NULL;
}
//////////////////////////////////////
// find max length of the string
int getMaxLengthDistrict(struct District* L) {
    if (isEmpty(L)) {
        return 0;
    }

    int maxL = 0;
    struct District* P = L->next;
    while (P != NULL) {
        int length = strlen(P->name);
        if (length > maxL) {
            maxL = length;
        }
        P = P->next;
    }
    return maxL;
}
//////////////////////////////////
struct District * findDistrict(char x[],struct District *L) {//return pointer to a district we are searching for
    struct District *p;
    p = L->next;
    while (p != NULL && strcasecmp(p->name, x) != 0) {//strcasecmp() function is used for comparing strings
        p = p->next;
    }
    return p;
}

    ////////////////////////////////////////
    //Function to make swap between 2 nodes in town
    void swapLinkedList(struct Town* node1 , struct Town* node2) {
    // node1 = pointer to first node in town  ,  node2 = pointer to second node in town
        int temp ;
        char tempName[50];
        // make a swap between the population
        temp = node1->population; // put first population in temp
        node1->population = node2->population; // put second population in the first
        node2->population = temp;// put first (temp) population in the second
         // edit the names to make every town with it's population
         // like make a swap of numbers but in strings using strcpy
        strcpy(tempName, node1->T_name);
        strcpy(node1->T_name, node2->T_name);
        strcpy(node2->T_name, tempName);
    }
    //////////////////////////////////////////////
    // Function to make bubble sort for towns node depending on population
    void BubbleSortForPopulation (struct District* district) {
        int swapped; // like a flag
        struct Town*  ptr1 ;
        struct Town* lastnode = NULL; // to mark the last swap node
        if (district->towns == NULL) // check if the district empty or not
            return; // go out the function
            // we use do-while to be sure that enter in first time
        do {
            swapped = 0;
            ptr1 = district->towns; // the first town in district
            while (ptr1->link != lastnode) {
                if (ptr1->population > ptr1->link->population) { // compare between the population of current node and the population of next node
                    swapLinkedList(ptr1, ptr1->link); // call the function swap to swap between node and the next node
                    swapped = 1;
                }
                ptr1 = ptr1->link; // go to next town
            }
            lastnode = ptr1; // make last node swap equal ptr1
        } while (swapped);
    }
    /////////////////////////////////////////////
    // function to print sorted population
    void sortedPopulation (){
       // 4. Sort the towns for each district based on population in ascending order.
    struct District* district = District_head;
        while (district != NULL) {
            BubbleSortForPopulation(district);
            district = district->next;
        }
        displayAll(District_head);
}
///////////////////////////////////////////////
//Function to print sorted information
void printSortedInfo(){
   // 5. Print the sorted information.
    if(load ==0 ){ // u can't choose  this function before load the information
        printf("  U didn't load the info , please load the it \n ");
    }
    else{
        RadixSort(District_head);
    BubbleSortForPopulation(District_head);
    displayAll(District_head);}


}
////////////////////////////////////////////////
//function to add district
void addDistrict(){
    //6. Add a new district to the list of sorted districts (and sort the list)
    if(load ==0 ){ // u can't choose  this function before load the information
        printf("  U didn't load the info , please load the it \n ");
    }
    else {
    char districtName[50];
    printf("Enter the district name to add : ");
    while (getchar()!='\n'); // to read the town with space
    scanf("%49[^\n]", districtName); // read the town with space
    struct District*dis= insertandCreateDistrict(districtName);
    printf("Done");

}}
 //////////////////////////////////////////////////////////
    //function used to add town to certain district
    void addTowntoCertainDistrict() {
        //7.Add a new town to a certain district.
        char *districtName = (char *)malloc(50 * sizeof(char)); // space from memory
        if (districtName == NULL) {
            printf("Memory allocation failed.\n");
            return;
        }
        printf("Enter the district name to add the town to: ");
        scanf("%s", districtName);

        struct District* temp = findDistrictByName(districtName);//search about district by name
        if (temp != NULL) {
            struct Town* newTown = InsertTown();
            addTownToDistrict2(temp, newTown);// call the function to add the town
        }
        free(districtName);//make the district name string free t can store in it another something
        printf("Done\n");
    }
 /////////////////////////////////////////////////////
    //function to search about district by name * to avoid some errors
struct District* findDistrictByName(char* name) {
    struct District* current = District_head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL; // Not found
}
//////////////////////////////////////////////////////
// function to creation and insert the town
struct Town* InsertTown() {
    struct Town* newTown = (struct Town*)malloc(sizeof(struct Town));
    if (newTown == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    printf("Enter town name: ");
    while (getchar()!='\n'); // to read the town with space
    scanf("%49[^\n]", newTown->T_name); // read the town with space
    printf("Enter town population: ");
    scanf("%d", &newTown->population);
    newTown->link = NULL;
    return newTown;
}
////////////////////////////////////////////////
//function to add the town to district
void addTownToDistrict2(struct District* district, struct Town* town) {
    if (!searchTown(district, town->T_name)) {
        if (district->towns == NULL) {
            district->towns = town;
        } else {
            struct Town *temp = district->towns;
            while (temp->link != NULL) {
                temp = temp->link;
            }
            temp->link = town;
        }

        town->link = NULL;
        district->total_pop += town->population;
    } else {
        printf("Town already exists.\n");
        free(town); // delete
        printf("Done\n");
    }
}
//////////////////////////////////////
//  function to search about town by its name
bool searchTown(struct District* district, char* townName) {
    struct Town* ptr = district->towns;
    while (ptr != NULL) {
        if (strcmp(ptr->T_name, townName) == 0) {
            return true;
        }
        ptr = ptr->link;
    }
    return false;
}
//////////////////////////////////////////////
//this function used to take the name of district and the town were wat to delete then call delete function to delete the town
void deleteTownFromCertainDistrict(struct District* District_head) {
    //8. Delete a town from a specific district.
    char districtName[50];
    char townName[50];
    if(load ==0 ){
        printf("  U didn't load the info , please load the it \n");
    }else
    {
    printf("Enter the district name to delete the town from: ");
    scanf("%s", districtName);// read the nam of district
    printf("Enter the town name to delete: ");
    while (getchar()!='\n'); // to read the town with space
    scanf("%49[^\n]", townName); // read the town with space

    deleteTown(District_head, districtName, townName); // call delete function to delete specific town from certain district
}}
//////////////////////////////////////
//  delete the town
void deleteTown(struct District* District_head, char* districtName, char* townName) {
    struct District* district = District_head;
    while (district != NULL && strcmp(district->name, districtName) != 0) { // search about district
        district = district->next;// go to next to still search to find the district
    }
    if (district == NULL) {// if the district doesn't found the statement will print
        printf("District '%s' not found.\n", districtName);
        return;
    }

    struct Town* tempTown = district->towns; // pointer to the first town in the linked list
    struct Town* prev = NULL; // make pointer call prev

    while (tempTown != NULL) {
        if (strcmp(tempTown->T_name, townName) == 0) {
            break;
        }
        prev = tempTown;
        tempTown = tempTown->link;
    }
    if (tempTown == NULL) {
        printf("Town '%s' not found.\n", townName); // Print the input town and district names
        return;
    }

    if (prev == NULL) {
        district->towns = tempTown->link;
    } else {
        prev->link = tempTown->link;
    }
    district->total_pop -= tempTown->population; // update the total population
    free(tempTown); // delete the town (free build in function , delete from memory )
    printf("Done \n");
}
///////////////////////////////////////////////////////
// function take the name of district that i want to delete it with the towns
void deleteCertainDistrict() {
    //  9. Delete a complete district; here, you must delete all towns belonging to that district before deleting it.
    char districtName[50];
    if(load ==0 ){
        printf("  U didn't load the info , please load the it \n");
    }
else {
    printf("Enter the district name to delete : ");
    scanf("%s", districtName); // Read the district name
    deleteDistrictwithTowns(districtName);//call function that delete the district
}}
/////////////////////////////////////
// function when call it delete the district with the towns
void deleteDistrictwithTowns(char* districtName) {

    struct District *ptr = District_head , *temp = NULL; // *temp to traverse the linked list of districts
    while (ptr != NULL && strcmp(ptr->name, districtName) != 0) {
        temp = ptr;
        ptr = ptr ->next; // go to next district
    }

    if (ptr == NULL) { // district not found
        printf("District not found.\n");
        return;// go out of function
    }
    struct Town *town = ptr ->towns, *nextTown; //  *nextTown  to traverse the linked list of town
    while (town != NULL) {
        nextTown = town->link; // Save the next town
        free(town); // delete town
        town = nextTown; // go to the next town
    }
// have a problem if the district in the first , solution ->
    if (temp == NULL) {  //if the district in first
        District_head = ptr->next;
    } else {// if it in the middle
        temp->next = ptr->next;
    }

    if(ptr->next != NULL) { // if the district not last one
        ptr->next->Previous = ptr;
    }
    free(ptr); //delete district
    printf("Done");
}
//////////////////////////////////////
// Function to calculate the total population of palestine and the max and min population
void CalculatePopulation(){
    // 10.Calculate the population of Palestine, the max and min town population
    int Total_population=0;
    char *max;
    int maxpopulation =0;
    char *min ;
    int minpopulation = INT_MAX; // Initialize minpopulation with the highest possible int value

    struct District* D_head = District_head; //d head = district head
    if(load ==0 ){
        printf("  U didn't load the info , please load the it\n ");
    }
    else {
    if(! isEmpty(District_head)){ // chek if empty

        while ( D_head !=NULL) {
            struct Town *T_head = D_head->towns; // t_head pointer to the first town
            while (T_head !=NULL) {
                // find total population
                Total_population += T_head->population; // sum the pop with the population of each district
//find max population with the name
                if(T_head->population >maxpopulation ){
                    maxpopulation=T_head->population; // max pop
                    max=T_head->T_name; // name of max pop town
                }
                //find min population with the name
                if(T_head->population < minpopulation ){
                    minpopulation=T_head->population;// min pop
                    min=T_head->T_name;// name of min pop town
                }
                T_head = T_head->link; // go to next town
            }

            D_head = D_head->next; // go to next district
        }
        printf("Total Population of Palestine: %d \n", Total_population);
        printf("Maximum Town Population: %s, %d \n", max, maxpopulation);
        printf("Minimum Town Population: %s, %d \n", min, minpopulation);
    }
    else printf("The list is empty ");

} }
///////////////////////////////////////////////
// function when i call it check if the linked list empty or not
/*int isEmpty( struct District* D){
    if(D!=NULL)
        return D->next==NULL&&D->Previous==NULL;

}*/
//////////////////////////////////////////////
// function to print total population with the name of each district
void printPopandDistrict() {
    // 11.Print the districts and their total population (without towns details).
    struct District *D_head = District_head; // D_head = district head
    if(load ==0 ){
        printf("  U didn't load the info , please load the it \n");
    }
    if (!isEmpty(District_head)) { // Check if empty
        while (D_head != NULL) {
            int pop = 0;

            struct Town *T_head = D_head->towns; // T_head pointer to the first town
            while (T_head != NULL) {
                pop += T_head->population; // Sum the population with the population of each town
                T_head = T_head->link; // Move to next town
            }
            printf("%s ,Population = %d \n", D_head->name , pop); // Print the name of district and the population
            D_head = D_head->next; // go to next district
        }
    } else {
        printf(" The list is empty ");
    }
}
/////////////////////////////////////////////////
//function to update the population of certain town after enter district name
void NewPopulation() {
    //12.Change the population of a town, after prompting the user to enter the district name.
    char districtName[50];
    char townName[50];
    int newPopulation;
    if(load ==0 ){
        printf("  U didn't load the info , please load the it\n ");
    }
    else {

    printf("Enter the district name: ");
    scanf("%s", districtName);// read the district name

    struct District* district ;
        while (district != NULL && strcmp(district->name, districtName) != 0) { // search about district
            district = district->next;// go to next to still search to find the district
        }

    if (district == NULL) {
        printf("District not found.\n");
        return;
    }

    printf("Enter the town name: ");
    scanf("%s", townName);

    struct Town* town = district->towns;// pointer to first town

    while (town != NULL && strcmp(town->T_name, townName) != 0) {//search the town
        town = town->link;//go to next
    }

    if (town == NULL) {
        printf("Town not found within\n");
        return;
    }

    printf("Enter the new population for %s: ", townName); // if found the town , the program tell u to enter new population
    scanf("%d", &newPopulation); // read
    town->population = newPopulation;// update the population of the town

    printf("Done\n");
}}
//////////////////////////////////////////
// Function to print the output on file
void printDistrictsToFile(struct District* District_head, const char* stored_districts) {
if(load==0){
    printf(" U didn't load the info , to save it in file \n");
}
else {
    FILE* file = fopen("stored_districts.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    struct District* District = District_head;
    while (District != NULL) {
        fprintf(file ,  "%s District,Population= %d\n", District->name, District->total_pop);
       // printf("%s District,Population= %d\n", District->name, District->total_pop);
        struct Town* Town = District->towns;
        while (Town != NULL) {
            fprintf(file, "%s,%d\n", Town->T_name, Town->population);
            //printf("%s,%d\n", Town->T_name, Town->population);
            Town = Town->link;
        }

        fprintf(file, "\n");

        District = District->next;
    }

    fclose(file);
}
    printf("Done\n");
    }

//////////////////////////////////////////