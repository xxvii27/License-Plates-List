/* This file contains the headers for the whole program. It creates the structures and prototypes.
    Written By: Henry Wang
    Debugged by: Louis Lesman, Jon Wu, Alfred Koshan & Mark Darmadi
 */

/*All headers */
#include "linkListADT.h"
#include "bstADT.h"

//main
typedef struct{
	char plate[7];
	char *name;
	char *brand;
	int cost;
} CAR;
typedef struct{
	CAR    car;
	LIST  *list;
	int size;
} HASH_ELMNT; // an element in the hash table

typedef struct{
	int size;          // size of the hash table
	int noStu;         // number of students
	int maxLinkedList; // longest linked list
	HASH_ELMNT *table; // a pointer to a dynamically allocated array of structures
} HASH;

typedef struct nodetag{
	CAR car;
    struct nodetag *forward;
	struct nodetag *back;

}D_NODE;

typedef struct{
	D_NODE *head;
	int counter;
	D_NODE *tail;

}D_LIST;

/*main*/
void readFile(HASH *hash, D_LIST *list, BST_TREE *tree);
CAR stringToCar(char *input);
void process (HASH *hash, D_LIST *list, BST_TREE *tree);
char getChoice (void);
CAR addNewNode();
void searchByDList(D_LIST *list);
void writeToFile(D_LIST *pList);


/*hash*/
HASH *createHashTable(int size);
LIST *buildList (void);
int cmpID (void* pID1, void* pID2);
int locate(HASH *hash, char *plate);
int insert(HASH *hash, CAR car);
void printHash(HASH *hash);
void printList (LIST* list, int i, int *count);
HASH *freeData(HASH *hash);
void freeNames(void *value);
void searchByHash(HASH *hash, D_LIST *list);
void deleteHash(HASH *hash, char *target);
void printData(HASH *hash);

/*Doubly*/
D_LIST *createDoublyList();
void insertDNode(D_LIST *pList, CAR car);
CAR searchDNode(D_LIST *pList, char *target);
void printLinkedList(D_LIST *list);
LIST *freeLinkedList(D_LIST *list);
void deleteNode(D_LIST *list, char *target);
void deleteCar(D_LIST *list);

/*BST */
char *allocateString( char *tempString );
void printManager(BST_TREE *cars);
void printCars(void *dataPtr);
void searchManCars(BST_TREE *cars);
void insertTree(BST_TREE *tree, CAR tempCar);
void deleteTree(BST_TREE *tree, char *target);
void printIndentedBST(BST_TREE *cars);