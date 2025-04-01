#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

extern char *pop();
extern void push(char *);
extern int isEmpty();

int is_valid_tag(const char* tag) {
    // Check if the tag is valid. Tags can include alphanumeric characters (letters and digits)
    for (int i = 0; tag[i] != '\0'; i++) {
        if (!(isalnum(tag[i]))) {
            return 0; // Invalid tag if the character is not alphanumeric
        }
    }
    return 1; // Valid tag
}

int main(int argc, char * argv[]) {
    char tag[100]; 
    int tag_index = 0;
    int ch;
    
    while ((ch = getchar()) != EOF) {
        // Ignore characters that are not relevant for tags (except '<', '>', '/', and alphabets)
        if (!(isalpha(ch) || ch == '>' || ch == '<' || ch == '/'))
            continue;

        if (ch == '<') {
            tag_index = 0;
            int is_end_tag = 0;

            ch = getchar();
            if (ch == '/') {
                is_end_tag = 1;  // End tag detected
                ch = getchar();  // Move past '/'
            }

            // Start building the tag, don't include '<' or '/' in the tag
            while (ch != '>' && ch != EOF) {
                if (tag_index < sizeof(tag) - 1) {
                    tag[tag_index++] = ch;
                }
                ch = getchar();  // Read next character
            }
            tag[tag_index] = '\0'; // Null-terminate the tag

            // If the tag is invalid (not alphanumeric), print error and exit
            if (!is_valid_tag(tag)) {
                printf("Invalid tag: %s\n", tag);
                return 1;
            }

            printf("Read tag: %s\n", tag);

            if (is_end_tag == 0) {  // Start tag
                // Push the start tag to the stack
                push(tag);
            } else {  // End tag
                if (isEmpty()) {
                    printf("Error: Stack Underflow (no matching start tag)\n");
                    return 1;
                }

                // Pop the last tag and check if it matches the current end tag
                char* popped_tag = pop();
                if (strcmp(popped_tag, tag) != 0) {
                    // Print the tag mismatch error
                    printf("Error: Tag mismatch, expected '%s' but found '%s'\n", popped_tag, tag);
                    return 1;
                }
            }
        }
    }

    // If the stack is not empty after reading all tags, there are unmatched start tags
    if (!isEmpty()) {
        printf("Error: Unmatched start tag(s) remaining\n");
        return 1;
    }

    printf("XML is valid!\n");
    return 0;  // Exit successfully
}

