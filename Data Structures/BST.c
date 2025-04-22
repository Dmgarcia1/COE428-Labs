#include <stdio.h>
//BST implementation in C
typedef struct {
    int data;
    TNODE *left;
    TNODE *right;
}TNODE;


typedef struct {
    int count;
    TNODE *root;
}TREE;

TNODE search(TNODE *root, int key) {
    if (root == NULL) {
        return *root;   // Return NULL if tree is empty
    }
    TNODE *curr = root;
    

    while (curr != NULL) {
        if (key == curr->data) {
            return *curr;
        }
        if (key < curr->data) {
            curr = curr->left;
        }
        if (key > curr->data) {
            curr = curr->right;
        }
    }
}




TNODE insert(TNODE *root, int key) {
    TNODE *new = malloc(sizeof(TNODE));
    if (new == NULL) return *root; // Handle memory allocation failure
    
    new->data = key;
    new->left = NULL;
    new->right = NULL;
    
    // Handle empty tree case
    if (root == NULL) {
        return *new; // Return the new node as root
    }
    
    TNODE *parent = NULL;
    TNODE *curr = root;
    
    // Find the insertion point
    while (curr != NULL) {
        parent = curr; // Update parent before moving curr
        
        if (key == curr->data) {
            free(new); // Duplicate key, free the new node
            return *root; // Return original root unchanged
        }
        else if (key < curr->data) {
            curr = curr->left;
        }
        else { // key > curr->data
            curr = curr->right;
        }
    }
    
    // Insert the new node at the correct position
    if (key < parent->data) {
        parent->left = new;
    }
    else { // key > parent->data
        parent->right = new;
    }
    
    return *root; // Return the original root
}

TNODE* delete(TNODE *root, int key) {
    if (root == NULL) return NULL;
    
    TNODE *parent = NULL;
    TNODE *curr = root;
    
    // First, find the node to delete and its parent
    while (curr != NULL && curr->data != key) {
        parent = curr;
        if (key < curr->data) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    
    // If key not found
    if (curr == NULL) return root;
    
    // Case 1: Node has two children
    if (curr->left != NULL && curr->right != NULL) {
        // Find inorder successor (smallest node in right subtree)
        TNODE *succ_parent = curr;
        TNODE *succ = curr->right;
        
        while (succ->left != NULL) {
            succ_parent = succ;
            succ = succ->left;
        }
        
        // Copy successor's data to current node
        curr->data = succ->data;
        
        // Now delete the successor (which has at most one child)
        if (succ_parent == curr) {
            succ_parent->right = succ->right;
        } else {
            succ_parent->left = succ->right;
        }
        
        free(succ);
        return root;
    }
    
    // Case 2 & 3: Node has 0 or 1 child
    TNODE *child = (curr->left != NULL) ? curr->left : curr->right;
    
    // If deleting root
    if (parent == NULL) {
        free(root);
        return child;
    }
    
    // Connect parent to child
    if (curr == parent->left) {
        parent->left = child;
    } else {
        parent->right = child;
    }
    
    free(curr);
    return root;
}