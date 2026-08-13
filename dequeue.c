#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *prev, *next;
};

// Global pointers initialized to NULL
struct node *head = NULL, *tail = NULL;

// Helper function to allocate and initialize a new node
struct node* createNode(int data) {
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    if (newnode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newnode->data = data;
    newnode->next = NULL;
    newnode->prev = NULL;
    return newnode;
}

// Insert an element at the front of the deque
void enqueueAtFront(int data) {
    struct node *newnode = createNode(data);

    if (head == NULL) {
        // Queue is empty: new node becomes both head and tail
        head = tail = newnode;
    } else {
        // Queue is not empty: attach before current head
        newnode->next = head;
        head->prev = newnode;
        head = newnode;
    }
}

// Insert an element at the rear of the deque
void enqueueAtRear(int data) {
    struct node *newnode = createNode(data);

    if (tail == NULL) {
        // Queue is empty: new node becomes both head and tail
        head = tail = newnode;
    } else {
        // Queue is not empty: attach after current tail
        tail->next = newnode;
        newnode->prev = tail;
        tail = newnode;
    }
}

// Delete an element from the front of the deque
void dequeueAtFront() {
    if (head == NULL) {
        printf("Queue is empty\n");
        return;
    }

    struct node *temp = head;

    if (head == tail) {
        // Only one node in the queue
        head = tail = NULL;
    } else {
        // Move head pointer to the next node
        head = head->next;
        head->prev = NULL;
    }

    free(temp);
}

// Delete an element from the rear of the deque
void dequeueAtRear() {
    if (tail == NULL) {
        printf("Queue is empty\n");
        return;
    }

    struct node *temp = tail;

    if (head == tail) {
        // Only one node in the queue
        head = tail = NULL;
    } else {
        // Move tail pointer to the previous node
        tail = tail->prev;
        tail->next = NULL;
    }

    free(temp);
}

// Display all elements from front to rear
void display() {
    if (head == NULL) {
        printf("Queue is empty\n");
        return;
    }

    struct node *temp = head;
    while (temp != NULL) {
        printf("%-3d", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    int data, ch;

    while (1) {
        printf("\n1. Enqueue at front\n2. Enqueue at rear\n");
        printf("3. Dequeue at front\n4. Dequeue at rear\n");
        printf("5. Display\n6. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &ch) != 1) {
            break;
        }

        switch (ch) {
            case 1:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                enqueueAtFront(data);
                break;

            case 2:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                enqueueAtRear(data);
                break;

            case 3:
                dequeueAtFront();
                break;

            case 4:
                dequeueAtRear();
                break;

            case 5:
                display();
                break;

            case 6:
                // Clean up remaining elements if any
                while (head != NULL) {
                    dequeueAtFront();
                }
                exit(0);

            default:
                printf("Enter a valid option\n");
                break;
        }
    }

    return 0;
}
