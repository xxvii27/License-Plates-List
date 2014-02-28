/* This file stores information into a self adjusting linked list. It inserts, searches, and deletes by key.
   It also prints the efficiency.
    Written By: Jon Wu
    Debugged by: Henry Wang, Louis Lesman, Alfred Koshan & Mark Darmadi
 */
#include "Header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cType.h>

D_LIST *createDoublyList(){
	D_LIST *list;
	list = (D_LIST *)malloc(sizeof(D_LIST));
	list->counter = 0;

	list->head = (D_NODE *)malloc(sizeof(D_NODE));
	list->tail = (D_NODE *)malloc(sizeof(D_NODE));
	list->head->forward = list->tail;
	list->tail->back = list->head;
	list->head->back= NULL;
	list->tail->forward = NULL;
	
	return list;
}
void insertDNode(D_LIST *pList, CAR car)
{
	D_NODE* pNew;
	D_NODE* pFront = pList->head->forward;
	D_NODE* pPre = pList->head;
	D_NODE *pCurrent = pList->head->forward;
	int i, check = 0;

	for(i=0;i<pList->counter;i++)
	{
		if(strcmp(pCurrent->car.plate, car.plate)==0){
			check = 1;
			break;
		}
			pCurrent = pCurrent->forward;
	}
	if(!check){
		if (!(pNew = (D_NODE*)malloc(sizeof(D_NODE))))
		{
			printf("\aMemory overflow in insert\n");
			exit(100);
		}
		pNew->car = car;
		pFront->back = pNew;
		pNew->forward = pFront;
		pPre->forward = pNew;
		pNew->back = pPre;

		pList->counter++;
	}
	return;
}//insertNode

CAR searchDNode(D_LIST *pList, char *target){

	int i; 
	D_NODE *pCur;
	D_NODE *pForw;
	D_NODE *pBack;
	D_NODE *pFront = pList->head->forward;
	D_NODE *pFirst = pList->head;

	CAR car;
	car.plate[0] = '\0';
	if(!strcmp(pList->head->forward->car.plate, target) == 0){
		pCur = pList->head->forward;
		for(i = 0; i < pList->counter; i++){
			if(strcmp(pCur->car.plate, target)==0){
			
				pForw = pCur->forward;
				pBack = pCur->back;
				pBack->forward = pForw;
				pForw->back = pBack;

				pFirst->forward = pCur;
				pCur->back = pFirst;
				pFront->back = pCur;
				pCur->forward = pFront;

				car = pCur->car;
				return car;
			}
			pCur = pCur->forward;
		}
	}else{
		car = pList->head->forward->car;
	}
	return car;
}

void printLinkedList(D_LIST *list){
	D_NODE *pCur;
	int i;
	pCur = list->head->forward;
	
	
	printf("\nPlate     Name       Brand     Cost\n");
	printf("======= ========= ========== ======\n");
	for(i = 0; i < list->counter; i++){
		printf("%6s %10s %10s %6d\n", pCur->car.plate, pCur->car.name, pCur->car.brand,pCur->car.cost);
		pCur = pCur->forward;
	}
}

LIST *freeLinkedList(D_LIST *list){
	D_NODE *pCur;
	D_NODE *pTemp;
	pCur = list->head->forward;
	
	while(pCur!=NULL){
		pTemp = pCur;
		pCur = pCur->forward;
		free(pTemp);
	}
	free(list->head);
	free(list);
	return NULL;
}
void searchByDList(D_LIST *list){
	char plate[50];
	CAR car;

	do{
		printf("Enter your plate number: ");
		gets(plate);
		if(strlen(plate) != 6){
			printf("Invalid input. Try Again\n");
		}
	}while(strlen(plate) != 6);
	car = searchDNode(list,plate);

	if(car.plate[0]){
		printf("\n");
		printf("Plate ID: %s\n", car.plate);
		printf("Brand: %s\n", car.brand);
		printf("Name: %s\n", car.name);
		printf("Cost: %d\n", car.cost);
	}else{
		printf("Car is not found\n");
	}
	return;
}
void deleteNode(D_LIST *list, char *target){
	D_NODE *pCur;
	D_NODE *pPre;
	D_NODE *pFront;
	int i;
	
	pCur = list->head->forward;
	
	for(i = 0; i < list->counter; i++){
		
		if(strcmp(pCur->car.plate, target)==0){
			pPre = pCur->back;
			pFront = pCur->forward;
			pFront->back = pPre;
			pPre->forward = pFront;
			(list->counter)--;
			
			free(pCur);

			return;
		}
		pCur = pCur->forward;
		
	}
	return;
}