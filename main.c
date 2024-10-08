/* You are not allowed to use <stdio.h> */
#include "io.h"
#include <stdlib.h> // For malloc
#include <unistd.h> // For read and write

// Doubly linked list node structure
typedef struct Node {
    int value;
    struct Node* next;
    struct Node* prev;
} Node;

// Function to create a new node with a value
Node* create_node(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode != NULL) {
        newNode->value = value;
        newNode->next = NULL;
        newNode->prev = NULL;
    }
    return newNode;
}

// Function to append a node to the end of the list
void append(Node** head, Node** tail, int value) {
    Node* newNode = create_node(value);
    if (*head == NULL) {
        *head = newNode;
        *tail = newNode;
    } else {
        (*tail)->next = newNode;
        newNode->prev = *tail;
        *tail = newNode;
    }
}

// Function to remove the last node from the list
void remove_last(Node** head, Node** tail) {
    if (*tail == NULL) {
        return;  // List is empty, nothing to remove
    }

    Node* toRemove = *tail;
    if (*head == *tail) {
        // Only one node in the list
        *head = NULL;
        *tail = NULL;
    } else {
        *tail = (*tail)->prev;
        (*tail)->next = NULL;
    }
    free(toRemove);
}

// Function to print the list in the desired format
void print_list(Node* head) {
    Node* current = head;
    int first = 1;  // To handle the comma separation

    while (current != NULL) {
        if (!first) {
            write_char(',');  // Print comma after the first element
        }
        write_int(current->value);
        first = 0;
        current = current->next;
    }
    write_char('\n');  // Print a newline after the collection
}

/**
 * @name  main
 * @brief This function is the entry point to your program
 * @return 0 for success, anything else for failure
 */
int main()
{
    int counter = 0; // Initialize counter
    Node* head = NULL;  // Points to the start of the list
    Node* tail = NULL;  // Points to the end of the list

    char command;

    while (1) {
        command = read_char();

        // Handle EOF or other invalid commands to break the loop
        if (command != 'a' && command != 'b' && command != 'c') {
            break;
        }

        switch (command) {
            case 'a':
                // Add the counter to the collection, then increment the counter
                append(&head, &tail, counter);
                counter++;
                break;

            case 'b':
                // Do nothing but increment the counter
                counter++;
                break;

            case 'c':
                // Remove the most recently added element from the collection
                remove_last(&head, &tail);
                counter++;
                break;
        }
    }

    // Print the final counter value
    write_string("Count: ");
    write_int(counter);
    write_char('\n');

    // Print the final collection in the required format
    write_string("Collection: ");
    print_list(head);

    // Free the remaining elements in the collection (linked list)
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
