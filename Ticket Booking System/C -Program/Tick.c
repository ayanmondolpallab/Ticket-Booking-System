
#include <stdio.h>
#include <stdlib.h>

// Node structure for linked list
typedef struct Node {
    int seatNumber;
    char passengerName[50];
    struct Node* next;
} Node;

// Function prototypes
Node* createNode(int seatNumber, char* passengerName);
void insertAtEnd(Node** head, int seatNumber, char* passengerName);
void displaySeats(Node* head);
Node* searchSeat(Node* head, int seatNumber);
void bookSeat(Node** head);
void editBooking(Node* head);
void deleteReservation(Node** head);

// Global variables
Node* seatList = NULL;

int main() {
    int choice;

    do {
        printf("\n----- Automated Bus Ticket Booking System -----\n");
        printf("1. Display available seats\n");
        printf("2. Book a seat\n");
        printf("3. Edit booking\n");
        printf("4. Delete reservation\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displaySeats(seatList);
                break;
            case 2:
                bookSeat(&seatList);
                break;
            case 3:
                editBooking(seatList);
                break;
            case 4:
                deleteReservation(&seatList);
                break;
            case 0:
                printf("Thank you for using the ticket booking system!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}

// Create a new node
Node* createNode(int seatNumber, char* passengerName) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->seatNumber = seatNumber;
    strcpy(newNode->passengerName, passengerName);
    newNode->next = NULL;
    return newNode;
}

// Insert a node at the end of the linked list
void insertAtEnd(Node** head, int seatNumber, char* passengerName) {
    Node* newNode = createNode(seatNumber, passengerName);

    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }

    printf("Seat %d booked successfully for %s.\n", seatNumber, passengerName);
}

// Display all seats and their status
void displaySeats(Node* head) {
    if (head == NULL) {
        printf("No seats booked yet.\n");
        return;
    }

    printf("Seat\tPassenger Name\n");
    printf("----\t--------------\n");

    Node* current = head;
    while (current != NULL) {
        printf("%d\t%s\n", current->seatNumber, current->passengerName);
        current = current->next;
    }
}

// Search for a seat in the linked list
Node* searchSeat(Node* head, int seatNumber) {
    Node* current = head;
    while (current != NULL) {
        if (current->seatNumber == seatNumber) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Book a seat
void bookSeat(Node** head) {
    int seatNumber;
    char passengerName[50];

    printf("Enter seat number: ");
    scanf("%d", &seatNumber);

    if (searchSeat(*head, seatNumber) != NULL) {
        printf("Seat %d is already booked. Please choose another seat.\n", seatNumber);
    } else {
        printf("Enter passenger name: ");
        scanf(" %[^\n]s", passengerName);
        insertAtEnd(head, seatNumber, passengerName);
    }
}

// Edit booking
void editBooking(Node* head) {
    int seatNumber;
    char passengerName[50];

    printf("Enter seat number to edit booking: ");
    scanf("%d", &seatNumber);

    Node* seatNode = searchSeat(head, seatNumber);
    if (seatNode == NULL) {
        printf("Seat %d is not booked.\n", seatNumber);
    } else {
        printf("Enter new passenger name: ");
        scanf(" %[^\n]s", passengerName);
        strcpy(seatNode->passengerName, passengerName);
        printf("Booking for seat %d updated successfully.\n", seatNumber);
    }
}

// Delete reservation
void deleteReservation(Node** head) {
    int seatNumber;

    printf("Enter seat number to delete reservation: ");
    scanf("%d", &seatNumber);

    Node* current = *head;
    Node* prev = NULL;

    while (current != NULL) {
        if (current->seatNumber == seatNumber) {
            if (prev == NULL) {
                *head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("Reservation for seat %d deleted successfully.\n", seatNumber);
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("Seat %d is not booked.\n", seatNumber);
}
