/* This file contains all the tree functions, uses them, and calls them. It 
   sorts all the car information by license plate number in alphabetical order. 
   It also prints the indented tree.

    Written By: Louis Lesman
    Debugged by: Henry Wang, Jon Wu, Alfred Koshan & Mark Darmadi
*/

#include "Header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cType.h>
#define FLUSH while( getchar() != '\n' )

/* ======================== allocateString ========================
    Uses a statically allocated string to create a
    dynamically allocated string with the same contents.
    Pre:  tempString - statically allocated
    Post: string - dynamically allocated
*/
char *allocateString( char *tempString )
{
    char *string;
    int   stringSize;

    stringSize = strlen( tempString ) + 1;
    string = (char *) calloc (stringSize, sizeof (char));
    if ( string == NULL)
	{
        printf ("ERROR, not enough memory!!!\a\n");
		exit (102);
	}
    strcpy (string, tempString);
    return string;
}// allocateString

/* ======================== printManager ========================
 This function prints the tree.
 Pre:  The tree containing the data
 Post: Printed the tree.
 */
void printManager(BST_TREE *cars)
{
	printf("\nPlate     Name       Brand     Cost\n");
	printf("======= ========= ========== ======\n");
	BST_Traverse(cars, printCars);

	return;
}
/* ======================== printCars ========================
 This function prints the car for the indented tree
 Pre:  A void type data
 Post: Printed the car and information.
 */
void printCars(void *dataPtr)
{
	CAR car = *((CAR*)dataPtr);

	printf("%6s %10s %10s %6d\n", car.plate, car.name, car.brand,car.cost);
	return;
}
/* ======================== searchManCars ========================
 This function searches the tree when the user searches for a specific car
 Pre:  The tree of cars
 Post: Either prints the information the user wants or prints an error message
       if he/she does not give a valid input
 */
void searchManCars(BST_TREE *cars)
{
	CAR search, *output;
	int k;
	char temp[7];

	printf("Enter plate to be searched, (END To Stop)\n");

	do
	{
		scanf("%s", temp);
		FLUSH;
		for(k=0;k<strlen(temp);k++)
			temp[k] = toupper(temp[k]);
		strcpy(search.plate, temp);
		if(strcmp(temp, "End")!=0){
			output = (CAR*)BST_Retrieve(cars, &search);
			if(output)
				printf("%6s %10s %10s $%6d\n", output->plate, output->name, output->brand, output->cost);
			else printf("Target Not Found\n");
		}
	}while(strcmp(temp, "END")!=0);
 return;
}//searchManHobb
/* ======================== insertTree ========================
 This function inserts the data into the tree
 Pre: The tree of cars and the structure that we are inserting
 Post: Data inserted into the tree
 */
void insertTree(BST_TREE *tree, CAR tempCar){
	 CAR *car = (CAR *)malloc(sizeof(CAR));
	 car->brand = tempCar.brand;
	 car->name = tempCar.name;
	 strcpy(car->plate, tempCar.plate);
	 car->cost = tempCar.cost;
	 if(!BST_Retrieve(tree, &tempCar))
		BST_Insert(tree,car);
	 return;
}
/* ======================== deleteTree ========================
 This function deletes the tree and frees the memory
 Pre:  The tree of cars and the no. plate of the car
 Post: tree deleted and memory freed
 */
void deleteTree(BST_TREE *tree, char *target){
	CAR car;
	strcpy(car.plate, target);
	BST_Delete(tree, &car);
}
