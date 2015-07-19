//TODO node->data may not be freed

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

typedef struct node {
   struct node *next;
   struct node *prev;
   void *data;
} node;

static void error (char *function, char *message) {
   fprintf(stderr, "Error in function %s: %s\n", function, message);
   exit(EXIT_FAILURE);
}

// newList
/* List constructor */
List newList (void) {
   List thisList = malloc(sizeof(struct List));
   clear(thisList);
   return thisList;
}

node *newNode (void) {
   node *newNode = malloc(sizeof(node));
   newNode->next = NULL;
   newNode->prev = NULL;
   newNode->data = NULL;
   return newNode;
}

// freeNode
/* node destructor */
void freeNode (node **dNode) {
   if (dNode != NULL && *dNode != NULL) {
      free((*dNode)->data);
      (*dNode)->data = NULL;
      free(*dNode);
      *dNode = NULL;
   }
}

// freeList
/* List destructor */
void freeList (List *pL) {
   if (pL != NULL && *pL != NULL) {
      for (node *curr = (*pL)->front; curr != NULL;) {
         node *temp = curr;
         curr = curr->next;
         freeNode(&temp);
      }
      free(*pL); 
      *pL = NULL;
   }
}

// length
/* Get length */
inline int length (List L) { return L->length; }

// index
/* Get index */
inline int index (List L) { return (L->cursor == NULL ? -1 : L->index); }

// front
/* Get front element */
void *front (List L) { 
   if (L->length == 0) error("front", "length is 0");
   return L->front->data; 
}

// back
/* Get back element */
void *back (List L) { 
   if (L->back == NULL) error ("back", "back is NULL");
   return L->back->data; 
}

// get
/* Get element at cursor */
void *get (List L) { 
   if (L->cursor == NULL) error("get", "cursor is NULL");
   return L->cursor->data; 
}

// equals
/* Find if List A equals List B */
int equals (List A, List B) {  
   if (A->length != B->length) return false;
   for (node *Anode = A->front, *Bnode = B->front; 
        Anode != NULL && Bnode != NULL;
        Anode = Anode->next, Bnode = Bnode->next ) 
      if (memcmp((const void *)Anode->data, 
                 (const void *)Bnode->data, sizeof(void *)))
         return false;
   return true;
}
// clear
/* Clear out a List to defaults */
void clear (List L) { 
   L->front  = NULL;
   L->back   = NULL;
   L->cursor = NULL;
   L->index  = -1;
   L->length = 0;
}

// moveFront
/* Move cursor to front node */
void moveFront (List L) { 
   if (L->length == 0) error("moveFront", "length is 0");
   L->index = 0;
   L->cursor = L->front;
}

// moveBack
/* Move cursor to back node */
void moveBack (List L) {
   if (L->length == 0) error("moveBack", "length is 0"); 
  L->index = L->length - 1;
  L->cursor = L->back;
}

// movePrev
/* Move cursor to previous node */
void movePrev (List L) { 
   if (L->cursor == NULL) return;
   L->cursor = L->cursor->prev;
   --L->index;
}

// moveNext
/* Move cursor to next node */
void moveNext (List L) {
   if (L->cursor == NULL) return;
   L->cursor = L->cursor->next;
   ++L->index;
}

// prepend
/* Prepend node to list */
void prepend (List L, void *data, size_t size) { 
   node *prep    = newNode(); 
   prep->data    = malloc(size);
   prep->data    = memcpy(prep->data, (const void *)data, size);
   prep->next    = L->front;
   if (L->front == NULL) { L->front = prep; L->back = prep; }
   else { L->front->prev = prep; L->front = prep; }
   ++L->length;
}

// append
/* Append node to list */
void append (List L, void *data, size_t size) { 
   node *app     = newNode();
   app->data     = malloc(size);
   app->data     = memcpy(app->data, (const void *)data, size);
   app->prev     = L->back;
   if (L->front == NULL) { L->front = app; L->back = app; }
   else { L->back->next = app; L->back = app; }
   ++L->length;
}

// insertBefore
/* Insert node before cursor */
void insertBefore (List L, void *data, size_t size) {
   if (L->cursor == NULL) error("insertBefore", "cursor is NULL");
   node *insb = newNode();
   insb->data = malloc(size);
   insb->data = memcpy(insb->data, (const void *)data, size);
   insb->next = L->cursor;
   insb->prev = L->cursor->prev;
   if (L->cursor->prev != NULL) L->cursor->prev->next = insb;
   else L->front = insb;
   L->cursor->prev  = insb;
   ++L->index;
   ++L->length;
}

// insertAfter
/* Insert node after cursor */
void insertAfter (List L, void *data, size_t size) {
   if (L->cursor == NULL) error("insertBefore", "cursor is NULL");
   node *insa = newNode();
   insa->data = malloc(size);
   insa->data = memcpy(insa->data, (const void *)data, size);
   insa->prev = L->cursor;
   insa->next = L->cursor->next;
   if (L->cursor->next != NULL) L->cursor->next->prev = insa;
   else L->back = insa;
   L->cursor->next  = insa;
   ++L->length;
}

// deleteFront
/* Delete front element */
void deleteFront (List L) {
   if (L->front == NULL) error("deleteFront", "front is NULL");
   node *temp = L->front;
   L->front = L->front->next;
   free(temp);
   temp = NULL;
   --L->index;
}

// deleteBack
/* Delete back element */
void deleteBack (List L) {
   if (L->back == NULL) error("deleteBack", "back is NULL");
   node **temp = &L->back;
   L->back = L->back->prev;
   free(*temp);
   *temp = NULL;
   if (L->cursor == L->back) L->index = -1;
}

// delete
/* Delete element under cursor */
void delete (List L) {
   if (L->cursor == NULL) error("delete", "cursor is NULL");
   L->cursor->prev->next = L->cursor->next;
   L->cursor->next->prev = L->cursor->prev;
   free(L->cursor);
   L->cursor = NULL;
   L->index = -1;
   --L->length;
}

// printList
/* Print the contents of the list */
/*void printList (FILE *out, List L) {
   for (node *curr = L->front; curr != NULL; curr = curr->next) {
      if (curr == L->back) fprintf(out, "%d", (int)(*curr->data));
      else fprintf(out, "%d ", (int)(*curr->data));
   }
}*/

// copyList
/* Return a new copy of the list */
/*List copyList (List L) {
   List newL = newList();
   for (node *curr = L->front; curr != NULL; curr = curr->next)
      append(newL, curr->data);
   return newL;
}*/

// concatList
/* Concatenate List B onto List A */
/*List concatList (List A, List B) {
   List cat = copyList(A);
   for (node *curr = B->front; curr != NULL; curr = curr->next)
      append(cat, curr->data);
   return cat;
}*/
