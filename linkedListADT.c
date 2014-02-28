/*	
    This file contains the definitons of the functions to maintain
	and process a linked list:

    Public Functions:
        createList
        addNode
        removeNode
        searchList
        retrieveNode
        emptyList
        fullList
        listCount
        traverse
        destroyList

    Private Functions:
        _insert
        _delete
        _search
*/

#include <stdlib.h>

#include "linkListADT.h"   /* <== public functions */


/* private functions */
static int  _insert  (LIST*  pList, L_NODE* pPre,  void* dataInPtr);
static void _delete  (LIST*  pList, L_NODE*  pPre, L_NODE*  pLoc, void** dataOutPtr);
static int  _search  (LIST*  pList, L_NODE** pPre, L_NODE** pLoc, void*  pArgu);


/* 
    =================================================
    ============== Public Functions =================
    =================================================
*/


/*	=============== createList ==============
	Allocates dynamic memory for a list head
	l_node and returns its address to caller
	   Pre    compare is address of compare function 
	          used to compare two nodes.
	   Post   head has allocated or error returned
	   Return head l_node pointer or null if overflow 
*/
LIST* createList (int (*compare) (void* argu1, void* argu2))
{
//	Local Definitions 
	LIST* list;

//	Statements 
	list = (LIST*) malloc (sizeof (LIST));
	if (list)
	   {
	    list->head    = NULL;
	    list->pos     = NULL;
	    list->rear    = NULL;
	    list->count   = 0;
	    list->compare = compare;
	   } // if 

	return list;
}	// createList 

/*	================== addNode =================
	Inserts data into list.
	   Pre    pList is pointer to valid list
	          dataInPtr pointer to insertion data
	   Post   data inserted or error
	   Return -1 if overflow
	           0 if successful
	           1 if dupe key
*/
int addNode (LIST* pList, void* dataInPtr)
{
//	Local Definitions 
	int  found;
	int  success;
	
	L_NODE* pPre;
	L_NODE* pLoc;
	
//	Statements 
	found = _search (pList, &pPre, &pLoc, dataInPtr);
	if (found)
	   // Duplicate keys not allowed 
	   return (+1);

	success = _insert (pList, pPre, dataInPtr);
	if (!success)
	   // Overflow 
	   return (-1);
	return (0);
}	// addNode 


/*	================= removeNode ================ 
	Removes data from list. 
	   Pre    pList pointer to a valid list
	          keyPtr pointer to key to be deleted
	          dataOutPtr pointer to data pointer
	   Post   Node deleted or error returned.
	   Return false not found; true deleted
*/
int removeNode  (LIST*  pList, void*  keyPtr, void** dataOutPtr)
{
//	Local Definitions 
	int  found;
	
	L_NODE* pPre;
	L_NODE* pLoc;
	
//	Statements 
	found = _search (pList, &pPre, &pLoc, keyPtr);
	if (found)
	   _delete (pList, pPre, pLoc, dataOutPtr);
	
	return found;
}	// removeNode 


/*	================== searchList ================= 
	Interface to search function. 
	   Pre    pList pointer to initialized list.
	          pArgu pointer to key being sought
	   Post   pDataOut contains pointer to found data
	     -or- NULL if not found
	   Return boolean true successful; false not found 
*/
int searchList (LIST*  pList, void* pArgu, void** pDataOut)
{
//	Local Definitions 
	int  found;
	
	L_NODE* pPre;
	L_NODE* pLoc;

//	Statements 
	found = _search (pList, &pPre, &pLoc, pArgu);
	if (found)
	    *pDataOut = pLoc->dataPtr;
	else
	    *pDataOut = NULL;
	return found;
}	// searchList 


/*	================== retrieveNode ================ 
	This algorithm retrieves data in the list without
	changing the list contents. 
	   Pre    pList pointer to initialized list.
	          pArgu pointer to key to be retrieved
	   Post   Data (pointer) passed back to caller
	   Return boolean true success; false underflow
*/
int  retrieveNode (LIST*  pList, void*  pArgu, void** dataOutPtr)
{
//	Local Definitions 
	int  found;
	
	L_NODE* pPre;
	L_NODE* pLoc;
	
//	Statements 
	found = _search (pList, &pPre, &pLoc, pArgu);
	if (found)
	   {
	    *dataOutPtr = pLoc->dataPtr;
	    return 1;
	   } // if 

	*dataOutPtr = NULL;
	return 0;
}	// retrieveNode 

/*	================= emptyList ================
	Returns boolean indicating whether or not the
	list is empty
	   Pre    pList is a pointer to a valid list 
	   Return boolean true empty; false list has data 
*/
int emptyList (LIST* pList) 
{
//	Statements 
	return (pList->count == 0);
}	// emptyList 

/*	================== fullList =================
	Returns boolean indicating no room for more data.
	This list is full if memory cannot be allocated for
	another l_node. 
	   Pre    pList pointer to valid list 
	   Return boolean true if full
	                  false if room for l_node 
*/
int fullList (LIST* pList) 
{
//	Local Definitions 
L_NODE* temp;

//	Statements 
	if ((temp = (L_NODE*)malloc(sizeof(*(pList->head)))))
	   {
	    free (temp);
	    return 0;
	   } // if 

	// Dynamic memory full 
	return 1;

}	// fullList 

/*	================== listCount ==================
	Returns number of nodes in list.
	   Pre    pList is a pointer to a valid list
	   Return count for number of nodes in list
*/
int listCount(LIST* pList) 
{
//	Statements 

	return pList->count; 
	
}	// listCount 

/*	================== traverse =================
	Traverses a list. Each call either starts at the
	beginning of list or returns the location of the 
	next element in the list.
	   Pre    pList       pointer to a valid list
	          fromWhere   0 to start at first element
	          dataPtrOut  address of pointer to data
	   Post   if more data, address of next l_node 
	   Return true l_node located; false if end of list
*/
int traverse (LIST*  pList,
              int    fromWhere,
              void** dataPtrOut)
{
//	Statements 
	if (pList->count == 0)
	    return 0;

	if (fromWhere == 0)
	   {
		 //Start from first l_node 
	    pList->pos  = pList->head;
	    *dataPtrOut = pList->pos->dataPtr;
	    return 1;
	   } // if fromwhere 
	else
	   {
	    // Start from current position 
	    if (pList->pos->link == NULL)
	        return 0;
	    else
	       {
	        pList->pos  = pList->pos->link;
	        *dataPtrOut = pList->pos->dataPtr;
	        return 1;
	       } // if else 
	   } // if fromwhere else 
}	// traverse 

/*	================== destroyList =================
	Deletes all data in list and recycles memory
	   Pre    List is a pointer to a valid list.
	   Post   All data and head structure deleted
	   Return null head pointer
*/
LIST* destroyList (LIST* pList, void (*process) (void* dataPtr)) 
{
//	Local Definitions 
	L_NODE* deletePtr;

//	Statements 
	if (pList)
	   {
	    while (pList->count > 0) 
	       {
	        // First delete data 
			if(!emptyList(pList)){
				process(pList->head->dataPtr);
			}
	        free (pList->head->dataPtr);
 
	        // Now delete l_node 
	        deletePtr    = pList->head;
	        pList->head  = pList->head->link; 
	        pList->count--;
	        free (deletePtr); 
	       } // while 
	    free (pList);
	   } // if 
	return NULL;
}	// destroyList 

/* 
    =================================================
    ============== Private Functions ================
    =================================================
*/
/*	================== _search =================
	Searches list and passes back address of l_node 
	containing target and its logical predecessor.
	   Pre    pList pointer to initialized list 
	          pPre  pointer variable to predecessor
	          pLoc  pointer variable to receive l_node
	          pArgu pointer to key being sought
	   Post   pLoc points to first equal/greater key 
	     -or- null if target > key of last l_node
	          pPre points to largest l_node < key
	     -or- null if target < key of first l_node
	   Return boolean true found; false not found 

*/
static int _search (LIST*  pList, L_NODE** pPre, L_NODE** pLoc,  void*  pArgu)
{
//	Macro Definition 
#define COMPARE      ( ((* pList->compare) (pArgu, (*pLoc)->dataPtr)) )

#define COMPARE_LAST ((* pList->compare) (pArgu, pList->rear->dataPtr))

//	Local Definitions 
	int result;
	
//	Statements 
	*pPre  = NULL;
	*pLoc  = pList->head;
	if (pList->count == 0)
	    return 0;
	
	// Test for argument > last l_node in list 
	if ( COMPARE_LAST > 0) 
	   {
	    *pPre = pList->rear;
	    *pLoc = NULL;
	    return 0;
	   } // if 

	while ( (result = COMPARE) > 0 )
	   {
	    // Have not found search argument location 
	    *pPre = *pLoc;
	    *pLoc = (*pLoc)->link;
	   } // while 
	
	if (result == 0)
	   // argument found--success 
	   return 1;
	else
	   return 0;
}	// _search 

/*	================= _delete ================ 
	Deletes data from a list and returns 
	pointer to data to calling module.
	   Pre    pList pointer to valid list.
	          pPre  pointer to predecessor l_node
	          pLoc  pointer to target l_node
	          dataOutPtr pointer to data pointer
	   Post   Data have been deleted and returned 
	          Data memory has been freed
*/
void _delete (LIST* pList, L_NODE*  pPre,
              L_NODE* pLoc,  void** dataOutPtr)
{
//	Statements 
	*dataOutPtr = pLoc->dataPtr;
	if (pPre == NULL)
	   // Deleting first l_node 
	   pList->head = pLoc->link;
	else
	   // Deleting any other l_node 
	   pPre->link = pLoc->link;
	 
	// Test for deleting last l_node 
	if (pLoc->link == NULL)
	    pList->rear = pPre;

	(pList->count)--;
	free (pLoc);

	return;
}	// _delete 

/*	=================== _insert ================== 
	Inserts data pointer into a new l_node.
	   Pre    pList pointer to a valid list 
	          pPre  pointer to data's predecessor 
	          dataInPtr data pointer to be inserted 
	   Post   data have been inserted in sequence 
	   Return boolean, true  if successful, 
	                   false if memory overflow 
*/
static int _insert (LIST* pList, L_NODE* pPre,
                     void* dataInPtr)
{
//	Local Definitions 
	L_NODE* pNew;

//	Statements 
	if (!(pNew = (L_NODE*) malloc(sizeof(L_NODE))))
	   return 0;

	pNew->dataPtr   = dataInPtr; 
	pNew->link      = NULL; 
 
	if (pPre == NULL)
	   {
	    // Adding before first l_node or to empty list. 
	    pNew->link       = pList->head;
	    pList->head      = pNew;
	    if (pList->count == 0)
	       // Adding to empty list. Set rear 
	       pList->rear = pNew;
	   } // if pPre 
	else
	   {
	    // Adding in middle or at end 
	    pNew->link  = pPre->link;
	    pPre->link  = pNew;
 
	    // Now check for add at end of list 
	    if (pNew->link     == NULL)
	         pList->rear   =  pNew;
	   } // if else 

	(pList->count)++;
	return 1;
}	// _insert 
