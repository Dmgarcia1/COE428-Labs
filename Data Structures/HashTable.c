#include <stdio.h>
#define TABLE_SIZE 101  // Prime number works well

typedef struct HNODE {
    char* word;
    int frequency;
    struct HNODE* next;  // For collision handling
} HNODE;

typedef struct {
    HNODE* buckets[TABLE_SIZE];
} HashTable;


HashTable* createHashTable() {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    
    // Initialize all buckets to NULL
    for (int i = 0; i < TABLE_SIZE; i++) {
        table->buckets[i] = NULL;
    }
    
    return table;
}

int hash(char *word) {
    int sum = 0;

    for (int i=0; word[i] !='\0';i++) {
        sum +=i;
    }

    return sum % TABLE_SIZE;
}


void insert(HashTable *ht, char *word) {
    int index = hash(word);
    HNODE *curr = ht->buckets[index];


    // runs till theres no value found 
    while (curr != NULL) {
        if (strcmp(curr->word, word) == 0) {
            curr->frequency++;
        }

        curr = curr->next;
    }
    HNODE *new = malloc(sizeof(HNODE));
    strcpy(new->word = word);


    // set node's next to point to its index
    new->next = ht->buckets[index];

    //point index at new
    ht->buckets[index] = new;

    new->frequency = 1;

}