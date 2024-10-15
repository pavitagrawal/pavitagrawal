#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct UserNode {
    char name[50];
    int duration;
    struct UserNode* next;
    struct UserNode* prev;
};

struct WashingMachine {
    struct UserNode* head;
};

struct UserNode* createUserNode(const char* name, int duration) {
    struct UserNode* newUser = (struct UserNode*)malloc(sizeof(struct UserNode));
    strcpy(newUser->name, name);
    newUser->duration = duration;
    newUser->next = newUser;
    newUser->prev = newUser;
    return newUser;
}

struct WashingMachine* createWashingMachine() {
    struct WashingMachine* machine = (struct WashingMachine*)malloc(sizeof(struct WashingMachine));
    machine->head = NULL;
    return machine;
}

void bookWashingMachine(struct WashingMachine* machine, const char* name, int duration) {
    struct UserNode* newUser = createUserNode(name, duration);
    if (machine->head == NULL) {
        machine->head = newUser;
    } else {
        struct UserNode* last = machine->head->prev;
        last->next = newUser;
        newUser->prev = last;
        newUser->next = machine->head;
        machine->head->prev = newUser;
    }
}

void handOverWashingMachine(struct WashingMachine* machine) {
    if (machine->head == NULL) {
        printf("No one is currently using the washing machine.\n");
        return;
    }

    struct UserNode* currentUser = machine->head;
    printf("Handing over the washing machine from %s after %d minutes.\n",
           currentUser->name, currentUser->duration);


    if (currentUser->next == currentUser) {

        free(currentUser);
        machine->head = NULL;
    } else {
        struct UserNode* nextUser = currentUser->next;
        machine->head = nextUser;
        nextUser->prev = currentUser->prev;
        currentUser->prev->next = nextUser;
        free(currentUser);
    }
}

void printQueue(struct WashingMachine* machine) {
    if (machine->head == NULL) {
        printf("No bookings in the queue.\n");
        return;
    }

    struct UserNode* current = machine->head;
    do {
        printf("User: %s, Duration: %d minutes\n", current->name, current->duration);
        current = current->next;
    } while (current != machine->head);
}

void freeMachine(struct WashingMachine* machine) {
    if (machine->head == NULL) {
        free(machine);
        return;
    }

    struct UserNode* current = machine->head;
    do {
        struct UserNode* temp = current;
        current = current->next;
        free(temp);
    } while (current != machine->head);

    free(machine);
}

int main() {
    struct WashingMachine* machine = createWashingMachine();
    int choice;
    char name[50];
    int duration;

    while (1) {
        printf("\nWashing Machine Renting System\n");
        printf("1. Book Washing Machine\n");
        printf("2. Hand Over Washing Machine\n");
        printf("3. Print Queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter your name: ");
                scanf("%s", name);
                printf("Enter duration in minutes: ");
                scanf("%d", &duration);
                bookWashingMachine(machine, name, duration);
                break;
            case 2:
                handOverWashingMachine(machine);
                break;
            case 3:
                printQueue(machine);
                break;
            case 4:
                freeMachine(machine);
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}
