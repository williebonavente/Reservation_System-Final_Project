#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the beginning of the circular linked list
Node* insertAtBeginning(Node* head, int data) {
    Node* newNode = createNode(data);
    if (head == NULL) {
        newNode->next = newNode;  // Point to itself to form a circular link
        return newNode;
    }
    newNode->next = head->next;
    head->next = newNode;
    return head;
}

// Function to insert a node at the end of the circular linked list
Node* insertAtEnd(Node* head, int data) {
    Node* newNode = createNode(data);
    if (head == NULL) {
        newNode->next = newNode;  // Point to itself to form a circular link
        return newNode;
    }
    newNode->next = head->next;
    head->next = newNode;
    return newNode;
}

// Function to delete a node from the circular linked list
Node* deleteNode(Node* head, int data) {
    if (head == NULL) {
        printf("List is empty.\n");
        return NULL;
    }
    Node* current = head->next;
    Node* prev = head;
    Node* deletedNode = NULL;
    while (current != head) {
        if (current->data == data) {
            prev->next = current->next;
            deletedNode = current;
            free(deletedNode);
            break;
        }
        prev = current;
        current = current->next;
    }
    if (current == head && current->data == data) {
        prev->next = current->next;
        deletedNode = current;
        free(deletedNode);
        if (current == current->next) {
            head = NULL;
        } else {
            head = current->next;
        }
    }
    return head;
}

// Function to display the circular linked list
void displayList(Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    Node* current = head->next;
    printf("Circular Linked List: ");
    while (current != head) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("%d ", current->data);
    printf("\n");
}

// Main function - Driver program
int main() {
    Node* head = NULL;
    int choice, data;

    while (1) {
        printf("Circular Linked List Operations:\n");
        printf("1. Insert at the beginning\n");
        printf("2. Insert at the end\n");
        printf("3. Delete a node\n");
        printf("4. Display the list\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the data to insert: ");
                scanf("%d", &data);
                head = insertAtBeginning(head, data);
                printf("Node inserted at the beginning.\n");
                break;
            case 2:
                printf("Enter the data to insert: ");
                scanf("%d", &data);
                head = insertAtEnd(head, data);
                printf("Node inserted at the end.\n");
                break;
            case 3:
                printf("Enter the data to delete: ");
                scanf("%d", &data);
                head = deleteNode(head, data);
                printf("Node deleted.\n");
                break;
            case 4:
                displayList(head);
                break;
            case 5:
                printf("Exiting the program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }

    return 0;
}