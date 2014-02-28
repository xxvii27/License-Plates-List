/*	
    This header file contains the functions to maintain
	and process a linked list.
*/

/*  Singly-Linked List ADT Type Definitions */

typedef struct l_node 
   {
	void*        dataPtr;
	struct l_node* link;
   } L_NODE; 

typedef struct
   {
	int   count; 
	L_NODE* pos;
	L_NODE* head; 
	L_NODE* rear;
	int    (*compare) (void* argu1, void* argu2); 
   } LIST;

/* List ADT Prototype Declarations: public functions */
	LIST* createList   (int (*compare)
	                   (void* argu1, void* argu2));

	LIST* destroyList (LIST* pList, void (*process) (void* dataPtr)); 

	int   addNode   (LIST* pList, void* dataInPtr);

	int   removeNode   (LIST*  pList,
	                    void*  keyPtr,
	                    void** dataOutPtr);

	int   searchList   (LIST*  pList,
	                    void*  pArgu,
	                    void** pDataOut);

	int   retrieveNode (LIST*  pList,
	                    void*  pArgu,
	                    void** dataOutPtr);

	int   traverse     (LIST*  pList,
	                    int    fromWhere,
	                    void** dataOutPtr);

	int   listCount    (LIST*  pList);
	int   emptyList    (LIST*  pList);
	int   fullList     (LIST*  pList); 

