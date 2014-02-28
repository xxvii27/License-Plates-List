/* Main creates the menu and calls the functions from other files. 
   Consolidates all the other files. This also writes to file
 
   Written By: Henry Wang
   Debugged by: Mark Darmadi, Jon Wu, Louis Lesman & Alfred Koshan
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cType.h>
#include "Header.h"

#define FLUSH while( getchar() != '\n' )

#ifdef _MSC_VER
#include <crtdbg.h>
#endif


int main(){
	HASH *hash;
	D_LIST *list;
	int size = 30;
	int i = 0;
	BST_TREE *tree = BST_Create(cmpID);
	list = createDoublyList();
	hash = createHashTable(size);
	readFile(hash, list, tree);
	process(hash, list, tree);
	
	
	hash = freeData(hash);
	freeLinkedList(list);
	tree = BST_Destroy(tree);
    
	printf("\n\t\tEnd of the program!\n" );
#ifdef _MSC_VER
    printf( _CrtDumpMemoryLeaks() ? "No Memory Leak\n" : "Memory Leak\n");
#endif
	getch();
    
}

/* ===== process =====
    This function presents the user with the menu.
    Pre     hash, list, tree
    Post    nothing
 */
void process (HASH *hash, D_LIST *list, BST_TREE *tree)
{
    //	Local Definitions
	char choice;
	CAR car;
    
    //	Statements
	do
    {
	    choice = getChoice ();
        
	    switch (choice)
        {
	        case 'P': printHash(hash);
                printLinkedList(list);
                printManager(tree);
                break;
			case 'R': printIndentedBST(tree);
                break;
			case 'E': printData(hash);
                break;
	        case 'S': searchByHash(hash, list);
                break;
			case 'T': searchByDList(list);
                break;
			case 'I': car = addNewNode();
                insert(hash,car);
                insertDNode(list, car);
                insertTree(tree,car);
                break;
			case 'D': deleteCar(list, hash, tree);
                break;
			case 'W': writeToFile(list);
                break;
	        case 'Q': break;
        } // switch
    } while (choice != 'Q');
	return;
}	// process

/* ===== getChoice =====
    This function prints the menu and gets the users option
    Pre  nothing
    Post choice is returned
 */
char getChoice (void)
{
    //	Local Definitions
	char choice;
	int  valid;
	
    //	Statements
	printf("\n======== MENU ======= \n"
	       "Here are your choices:\n"
	       "  S: Search by Hash Key\n"
		   "  T: Search by Self-Adjusting LL\n"
		   "  I: Insert a new Car\n"
	       "  P: Print all \n"
		   "  R: Print Indented Tree \n"
		   "  E: Print Efficiency \n"
		   "  D: Delete \n"
		   "  W: Write to file \n"
	       "  Q: Quit             \n\n"
	       "Enter your choice: ");
	do
    {
	    scanf(" %c", &choice);
		FLUSH;
	    choice = toupper(choice);
	    switch (choice)
        {
	        case 'S':
			case 'T':
	        case 'P':
			case 'R':
			case 'E':
			case 'I':
			case 'D':
			case 'W':
	        case 'Q': valid = 1;
                break;
	        default:  valid = 0;
                printf("\aInvalid choice\n"
                       "Please try again: ");
                break;
        } // switch
    } while (!valid);
	return choice;
}// getChoice

/* ===== readFile =====
    This function inputs the data from the file
    Pre     hash, list, cars
    Post    nothing
 */
void readFile(HASH *hash, D_LIST *list, BST_TREE *cars){
	
	CAR car;
	FILE *fp;
	CAR *fill;
	D_NODE *pPre = list->tail;
	
    char input[250];
    fp = fopen("Cars.txt","r");
    if(!fp){
        printf("Error. Cannot Read File");
        exit(100);
    }
    
	while((fgets(input,sizeof(input), fp))){
		car = stringToCar(input);
		insert(hash,car);
		insertDNode(list, car);
		pPre = pPre->back;
		if(!BST_Retrieve(cars, &car))
		{
			fill = (CAR*)malloc(sizeof(CAR));
			if(!fill)
			{
	            printf("Memory FULL\n"),
	            exit(101);
	        }
			fill->name = allocateString(car.name);
			fill->brand = allocateString(car.brand);
			fill->cost = car.cost;
			strcpy(fill->plate, car.plate);
			BST_Insert(cars, fill);
			cars->count++;
		}
	}
}// readFile

/* ===== stringToCar =====
    This function converts the string and inputs the data
    Pre  input
    Post CAR list
*/
CAR stringToCar(char *input){
    
	CAR car;
	char tempBrand[50];
	char tempName[50];
    
	sscanf(input,"%s %s %s %d", car.plate, tempBrand,tempName, &(car.cost));
	car.brand = (char *)calloc(strlen(tempBrand)+1,sizeof(char));
	car.name = (char *)calloc(strlen(tempName)+1,sizeof(char));
	strcpy(car.name,tempName);
	strcpy(car.brand,tempBrand);
    
	return car;
}// stringToCar

/*Linked List */
/* ===== addNewNode =====
    This function adds a new node to the list
    Pre nothing
    Post CAR list
 */
CAR addNewNode(void){
	
	CAR car;
	char plate[50];
	char tempString[50];
    
	do{
		printf("Enter your plate number: ");
		gets(plate);
		if(strlen(plate)!=6){
			printf("Invalid input. Try Again\n");
		}
	}while(strlen(plate)!= 6);
	strcpy(car.plate, plate);
    
	printf("Enter brand: ");
	gets(tempString);
	car.brand = (char *)calloc(strlen(tempString)+1, sizeof(char));
	strcpy(car.brand, tempString);
    
	printf("Enter name: ");
	gets(tempString);
	car.name = (char *)calloc(strlen(tempString)+1, sizeof(char));
	strcpy(car.name, tempString);
    
	printf("Enter estimated cost: ");
	scanf("%d", &(car.cost));
    
	return car;
}// addNewNode

/* ===== cmpID =====
    This function compares the plate numbers
    Pre     pID1, pID2
    Post    returns result
 */
int cmpID (void* pID1, void* pID2)
{
    //	Local Definitions
	int   result;
	char id1[7];
	char id2[7];
    
    //	Statements
	strcpy(id1,((CAR *)pID1)->plate);
	strcpy(id2,((CAR *)pID2)->plate);
    
	if (strcmp(id1, id2) < 0)
	    result = -1;
	else if (strcmp(id1, id2) > 0)
	    result = +1;
	else{
	    result = 0;
	}
	return result;
}// cmpID

/* ===== deleteCar =====
    This function deletes the car entry
    Pre list, hash, tree
    Post nothing
 */
void deleteCar(D_LIST *list, HASH *hash, BST_TREE *tree){
	CAR car;
	char plate[50];
	char tempString[50];
    
	do{
		printf("Enter your plate number: ");
		gets(plate);
		if(strlen(plate)!=6){
			printf("Invalid input. Try Again\n");
		}
	}while(strlen(plate)!= 6);
	strcpy(car.plate, plate);
	deleteNode(list, plate);
	deleteHash(hash, plate);
	deleteTree(tree, plate);
}// deleteCar

/* ===== wroteToFile =====
    This function writes to file
    Pre list,
    Post nothing
 */
void writeToFile(D_LIST *list){
	FILE *fp;
	int i = 0;
	D_NODE *pCur;
    
	fp = fopen("serial.txt","w");
    if(!fp){
        printf("Error. Cannot Read File");
        exit(100);
    }
    
	pCur = list->head->forward;
	for(i = 0; i< list->counter; i++){
		fprintf(fp,"%s; %s; %s; %d\n", pCur->car.plate, pCur->car.name, pCur->car.brand, pCur->car.cost);
		pCur = pCur->forward;
	}
	
	printf("Succesfully output to serial.txt\n");
	fclose(fp);
}// writeToFile

/* ===== printIndentedBST =====
    Pre     cars
    Post    nothing
 */
void printIndentedBST(BST_TREE *cars)
{
	printf("=======================\n"
		   "LIST	OF	  CARS\n"
		   "=======================\n");
    
	BST_Print(cars, printCars);
    
	return;
}// printIndentedBST