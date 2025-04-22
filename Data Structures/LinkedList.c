#include <stdio.h>
typedef struct NODE {
    int data;
    struct NODE *next;
}NODE;


typedef struct list {
    NODE *start;
} list;

NODE insert(list *ls, int data) {
    NODE *new_node = malloc(sizeof(NODE));
    new_node->data = data;
    new_node->next = NULL;
    if (ls->start == NULL) { // list is empty
        ls->start = new_node;   
    } else {
        NODE *curr = ls->start;
        while (curr != NULL) {
            if (curr->next == NULL) {
                curr->next = new_node;
            }

            curr = curr->next;
        }
    }
}

NODE delete(list *ls, int data) {

    NODE *curr = ls->start;
    NODE *prev = NULL;
    if (ls == NULL) return *curr; // Handle empty list case

    while (curr != NULL) {
        if (curr->data == data) { //found node to delete

            // this code is meant to skip the list over the node thats abt to get deleted
            if (prev == NULL) {
                ls->start = curr->next;
            } else {
                prev->next = curr->next;
            }
            /////////////////////////////////////////////////////////////////////////////

            
            NODE *temp = curr;
            curr = curr->next;
            free(temp);
        }
        prev = curr;
        curr = curr->next;
    }
}