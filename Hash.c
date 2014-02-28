/* This file stores the car information by a hash key. This inserts and deletes and searches for a car by a key.
    Written By: Aflred Koshan & Mark Darmadi
    Debugged by: Henry Wang, Jon Wu & Louis Lesman
*/

#include "Header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cType.h>
#define FLUSH while( getchar() != '\n' )

/* ================================================== */
/* This function creates the header of a hash table
   PRE: size
   POST: pointer to the header of the hash table
*/
HASH *createHashTable(int size){
	HASH *hash;
	int i;

	hash = (HASH *) malloc(sizeof(HASH));
	if( !hash )
		printf( "Not enough memory\n"), exit(101);
	hash->size = size;
	hash->table = (HASH_ELMNT *) calloc(size, sizeof(HASH_ELMNT));
	if( !(hash->table ) )
		printf( "Not enough memory\n"), exit(102);

	// write a loop to initialize the hash table: numbers to 0, pointers to NULL, etc.
	hash->noStu = 0;

	for(i = 0; i < hash->size; i++){
		hash->table[i].car.plate[0] ='\0';
		hash->table[i].list = buildList();
		hash->table[i].size = 0;
	}
	return hash;
}
/* ================================================== */
/* This function creates the list of data in a hash table
   PRE: -
   POST: pointer to the list
*/
LIST *buildList (void)
{
	LIST *list;
	list = createList(cmpID);
	if (!list)
	    printf("\aCannot create list\n"), exit (100);
	return list;
}
/* ================================================== */
/* This function locates the index of the data
   PRE: hash table, plate number
   POST: index number of the data
*/
int locate(HASH *hash, char *plate){
	int i;
	int sum = 0;
	int size = hash->size;

	for(i = 0; i < strlen(plate); i++){
		sum += (int)plate[i];
	}
	return sum % size;
}
/* ================================================== */
/* This function inserts the data to the hash table
   PRE: hash table, data of the car
   POST: data inserted
*/
int insert(HASH *hash, CAR car){
	int key;
	CAR *pCar;
	int addResult;

	key = locate(hash, car.plate);
	if(hash->table[key].car.plate[0] == '\0'){
		hash->table[key].car = car;
		hash->noStu++;
		return 1;

	}else if(strcmp(hash->table[key].car.plate, car.plate)  == 0){
		//do nothing. ID already exists.
		printf("ERROR");
		return 0;

	}else if(hash->table[key].car.plate[0] != '\0'){

		pCar = (CAR*)malloc(sizeof(CAR));
		strcpy(pCar->plate, car.plate);
		pCar->name = car.name;
		pCar->brand = car.brand;
		pCar->cost = car.cost;
		addResult = addNode(hash->table[key].list, pCar);
		if(!addResult){
			hash->table[key].size++;
		}
		return 1;
	}
}
/* ================================================== */
/* This function prints the data in the hash table
   PRE: hash table
   POST: data printed
*/
void printHash(HASH *hash){
	int i;
	CAR car;
	int count = 1;

	printf(" Cnt Index Plate     Name      Brand    Cost\n");
	printf("==== ===== ======= ======== ========== =====\n");

	for(i = 0; i <hash->size; i++){
		car = hash->table[i].car;
		if(car.plate[0]){
			printf("%4d. %2d %8s %9s %10s %5d\n",count, i,car.plate, car.name, car.brand, car.cost);
			if(!emptyList(hash->table[i].list)){
				printList(hash->table[i].list, i, &count);
			}
		}else{
			printf("%4d. %2d %7s\n",count, i,"Empty");
		}
		count++;
	}
}
/* ================================================== */
/* This function prints the linked list
   PRE: linked list, index, number of linked lists
   POST: linked list printed
*/
void printList (LIST* list, int i, int *count)
{
//	Local Definitions
	CAR* pCar;

//	Statements

	// Get first node

	traverse (list, 0, (void**)&pCar);
	do
	{
		(*count)++;
		printf("%4d. %2d %8s %9s %10s %5d\n",*count, i,pCar->plate, pCar->name, pCar->brand, pCar->cost);
	} while (traverse (list, 1, (void**)&pCar));
	return;
}
/* ================================================== */
/* This function frees the string name
   PRE: name
   POST: memory released
*/
void freeNames(void *value){
	CAR car = *((CAR*)value);
	free(car.brand);
	free(car.name);
	return;
}
/* ================================================== */
/* This function free all the data
   PRE: hash table
   POST: data released
*/
HASH *freeData(HASH *hash){
	CAR car;
	int i;

	for(i = 0; i <hash->size; i++){
		car = hash->table[i].car;
		hash->table[i].list = destroyList(hash->table[i].list, freeNames);
		if(car.plate[0]){
			free(car.name);
			free(car.brand);
		}
	}
	free(hash->table);
	free(hash);
	return NULL;
}
/* ================================================== */
/* This function searchs item in the hash
   PRE: hash table, list
   POST: data found
*/
void searchByHash(HASH *hash, D_LIST *list){
	char ID[50];
	int key;
	CAR car;
	CAR LLCar;
	CAR *pCar;
	int found;
	int check = 0;

	do{
		printf("Enter a six digit ID: ");
		gets(ID);
		if(strlen(ID) != 6){
			printf("Invalid input. Try Again\n");
		}
	}while(strlen(ID) != 6);

	strcpy(LLCar.plate, ID);
	key = locate(hash, ID);
	car = hash->table[key].car;

	if(strcmp(car.plate, ID)==0){

		printf("\nPlate: %s\nBrand: %s\nName: %s\n",car.plate, car.brand, car.name);
		check = 1;
	}else if(!emptyList(hash->table[key].list)){
		found = searchList(hash->table[key].list, &LLCar,(void**)&pCar);
		if(found){
			printf("\nPlate: %s\nBrand: %s\nName: %s\n",pCar->plate, pCar->brand, pCar->name);
			check = 1;
		}
	}
	if(!check){
		printf("Plate number not Found\n");
	}
	searchDNode(list, ID);

	return;
}
/* ================================================== */
/* This function delete one hash
   PRE: hash table, target to be deleted
   POST: target deleted
*/
void deleteHash(HASH *hash, char *target){
	int i;
	int key;
	CAR car;
	CAR newCar;
	CAR *pCar;
	CAR *pTempCar;

	int check = 0;
	key = locate(hash, target);
	car = hash->table[key].car;
	if(strcmp(car.plate, target)==0){
		free(car.brand);
		free(car.name);
		if(!emptyList(hash->table[key].list)){
			traverse (hash->table[key].list, 0, (void**)&pTempCar);
			removeNode(hash->table[key].list, pTempCar, (void**)&pCar);
			newCar.brand = pCar->brand;
			newCar.name  = pCar->name;
			strcpy(newCar.plate,pCar->plate);
			newCar.cost = pCar->cost;
		    hash->table[key].car = newCar;
			hash->table[key].size--;
		}else{
			newCar.plate[0] = '\0';
			hash->table[key].car = newCar;
		}
		check = 1;
	}else if(!emptyList(hash->table[key].list)){
		strcpy(newCar.plate,target);
		if(removeNode(hash->table[key].list, &newCar,(void**)&pCar)){
			free(pCar->brand);
			free(pCar->name);
			check = 1;
			hash->table[key].size--;
		};


	}
	if(!check){
		printf("Plate number not found\n");
	}
	return;
}
/* ================================================== */
/* This function prints the efficiency of the hash
   PRE: hash table
   POST: efficiency printed
*/
void printData(HASH *hash){
	double efficiency;
	int i;
	double total = 0;
	int count = 0;
	double averageNode;
	int largest = 0;


	efficiency = (double) hash->noStu/hash->size * 100;

	for(i = 0; i < hash->size; i++){
		if(hash->table[i].size != 0){
			if(hash->table[i].size>largest){
				largest = hash->table[i].size;
			}
			total += hash->table[i].size;
			count++;
		}
	}
	hash->maxLinkedList = largest;
	averageNode = total/count;
	printf("\n");
	printf("Load Factor: %.2f%%\n",efficiency);
	printf("Average nodes in linked-list: %.2f\n", averageNode);
	printf("Largest linked list: %d\n", hash->maxLinkedList);
}
