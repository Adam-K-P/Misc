/* Adam Pinarbasi
   akpinarb
   pa2           */
#ifndef __LIST
#define __LIST

struct List {
   struct node *front;
   struct node *back;
   struct node *cursor;
   int index;
   int length;
};
typedef struct List *List;

// Constructors-Destructors
List newList(void);
void freeList(List *pL);

// Access functions
int length(List L);
int index(List L);
void *front(List L);
void *back(List L);
void *get(List L);
int equals(List A, List B);

// Manipulation procedures
void clear(List L);
void moveFront(List L);
void moveBack(List L);
void movePrev(List L);
void moveNext(List L);
void prepend(List L, void *data, size_t size);
void append(List L, void *data, size_t size);
void insertBefore(List L, void *data, size_t size);
void insertAfter(List L, void *data, size_t size);
void deleteFront(List L);
void deleteBack(List L);
void delete(List L);

// Other operations
void printList(FILE *out, List L);
List copyList(List L);
List concatList(List A, List B);

#endif
