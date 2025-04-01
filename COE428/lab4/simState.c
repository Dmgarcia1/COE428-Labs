#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define structure for FSM state
typedef struct state_Machine {
    char name;
    int number;
    struct state_Machine* next_state_0;
    struct state_Machine* next_state_1;
} fsm;

fsm states[8];

// Function to initialize states
void initialize_states() {
    states[0] = (fsm){'A', 0, &states[6], &states[7]}; // A -> 0 -> G, 1 -> H
    states[1] = (fsm){'B', 1, &states[2], &states[5]}; // B -> 0 -> C, 1 -> F
    states[2] = (fsm){'C', 2, &states[4], &states[6]}; // C -> 0 -> E, 1 -> G
    states[3] = (fsm){'D', 3, &states[1], &states[4]}; // D -> 0 -> B, 1 -> E
    states[4] = (fsm){'E', 4, &states[0], &states[1]}; // E -> 0 -> A, 1 -> B
    states[5] = (fsm){'F', 5, &states[7], &states[2]}; // F -> 0 -> H, 1 -> C
    states[6] = (fsm){'G', 6, &states[5], &states[0]}; // G -> 0 -> F, 1 -> A
    states[7] = (fsm){'H', 7, &states[3], &states[7]}; // H -> 0 -> D, 1 -> H
}

// Function to print state transitions
void print_states() {
    printf("FSM State Configuration:\n");
    for (int i = 0; i < 8; i++) {
        printf("%c -> 0 -> %c, 1 -> %c\n",
               states[i].name,
               states[i].next_state_0->name,
               states[i].next_state_1->name);
    }
}

// Function to determine if a state is reachable via DFS
void dfs(fsm* current_state, int* visited) {
    // Mark the current state as visited
    visited[current_state->number] = 1;
    
    // Visit the next states
    if (current_state->next_state_0 != NULL && !visited[current_state->next_state_0->number]) {
        dfs(current_state->next_state_0, visited);
    }
    if (current_state->next_state_1 != NULL && !visited[current_state->next_state_1->number]) {
        dfs(current_state->next_state_1, visited);
    }
}

// Function to delete a state by name or delete all unreachable states if name is NULL
void delete(char* name) {
    int visited[8] = {0};  // Array to track visited states
	char temp;
    // Start DFS from state E (index 4)
    dfs(&states[4], visited);
    
    int deleted_any = 0;

    if (name == NULL) {
        // Delete unreachable states
        for (int i = 0; i < 8; i++) {
            // If state is unreachable and not already deleted (marked as 'X')
            if (!visited[i] && states[i].name != 'X') {
				temp = states[i].name;
                states[i].name = 'X';  // Mark state as deleted
                // Make sure no other state points to this deleted state
                for (int j = 0; j < 8; j++) {
                    if (states[j].next_state_0->name == states[i].name) {
                        states[j].next_state_0 = NULL;
                    }
                    if (states[j].next_state_1->name == states[i].name) {
                        states[j].next_state_1 = NULL;
                    }
                }
                printf("Deleted %c\n", temp);
                deleted_any = 1;
            }
        }

        if (!deleted_any) {
            printf("No states deleted\n");
        }
    } else {
        // Delete specific state
        int found = 0;
        for (int i = 0; i < 8; i++) {
            if (states[i].name == *name) {
				temp = states[i].name;
                states[i].name = 'X'; // Mark state as deleted
                // Also make sure no other state points to this deleted state
                for (int j = 0; j < 8; j++) {
                    if (states[j].next_state_0->name == *name) {
                        states[j].next_state_0 = NULL;  // Remove reference
                    }
                    if (states[j].next_state_1->name == *name) {
                        states[j].next_state_1 = NULL;  // Remove reference
                    }
                }
                printf("Deleted %c\n", *name);
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("State %c not found\n", *name);
        }
    }
}

// Function to change state transitions
void change(char *input, fsm* current_state) {
    if ((input[1] == '0' || input[1] == '1') && input[2] != '\0' && input[2] >= 'A' && input[2] <= 'H') {
        char state_name = input[2];
        fsm* new_state = NULL;

        // Find the new state by name (A-H)
        for (int i = 0; i < 8; i++) {
            if (states[i].name == state_name) {
                new_state = &states[i];
                break;
            }
        }

        // If state is found, update transition
        if (new_state != NULL) {
            if (input[1] == '0') {
                current_state->next_state_0 = new_state;
            } else if (input[1] == '1') {
                current_state->next_state_1 = new_state;
            }
        }
    }
}

void garbage() {
    int visited[8] = {0};  // Array to track visited states

    // Start DFS from state E (index 4)
    dfs(&states[4], visited);

    int found_garbage = 0;
    printf("Garbage:\n");

    // Check and print unreachable states
    for (int i = 0; i < 8; i++) {
        if (!visited[i] && states[i].name != 'X') {  // State is unreachable and not deleted
            printf("%c\n", states[i].name);
            found_garbage = 1;
        }
    }

    if (!found_garbage) {
        printf("No Garbage\n");
    }
}

int main() {
    char input[100];   // Input buffer to handle multiple commands
    fsm* current_state; 

    initialize_states(); 
    current_state = &states[4]; // Start from state 'E'

    printf("Enter commands: 0, 1, p, c [state], g, d [state], q to quit\n");
    printf("Starting State: %c\n", current_state->name);

    while (1) {
        printf("Current State: %c\n", current_state->name);
        printf("Enter commands (space-separated): ");
        
        // Read the command from user
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0; // Remove newline
        
        // Split the input into individual commands
        char* token = strtok(input, " ");  // Split by spaces
        while (token != NULL) {
            if (token[0] == '0') {
                // Transition to next state on input '0'
                printf("Next state: %c\n", current_state->next_state_0->name);
                current_state = current_state->next_state_0;
            }
            else if (token[0] == '1') {
                // Transition to next state on input '1'
                printf("Next state: %c\n", current_state->next_state_1->name);
                current_state = current_state->next_state_1;
            }
            else if (token[0] == 'p') {
                print_states();
            }
            else if (token[0] == 'g') {
                garbage();
            }
            else if (token[0] == 'd') {
                if (token[1] != '\0') {
                    delete(&token[1]); // Handle delete of state by name
                } else {
                    delete(NULL); // Delete unreachable states if no specific state is provided
                }
            }
            else if (token[0] == 'c') {
                change(token, current_state);
            }
            else if (token[0] == 'q') {
                printf("Exiting FSM program.\n");
                return 0;  // Exit the loop
            }
            else {
                printf("Unknown command! Please enter a valid command.\n");
            }
            token = strtok(NULL, " ");  // Get the next token
        }
    }

    return 0;
}


