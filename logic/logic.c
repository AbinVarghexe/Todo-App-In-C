#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for each task in the to-do list
struct node {
    char task[100];          // Task desc
    int status;              // 0 for pending, 1 for completed
    int date;                // Date in YYYYMMDD format
    struct node* link;       // Link to the next node
};

// Global pointer to head
struct node* head = NULL;

// Function to convert date string (in DD/MM/YYYY format) to an integer (YYYYMMDD)
int convertDate(char* dateStr) {
    int day, month, year;
    sscanf(dateStr, "%d/%d/%d", &day, &month, &year);
    return year * 10000 + month * 100 + day;
}

// Display all tasks
void display() {
    if (head == NULL) {
        printf("The To-Do List is Empty.\n");
        return;
    }
    struct node* ptr = head;
    do {
        printf("Task: %s | Date: %08d | Status: %s\n", ptr->task, ptr->date, (ptr->status == 0) ? "Pending" : "Completed");
        ptr = ptr->link;
    } while (ptr != head);
}

// Add a task based on date
void InsertByDate(char* task, char* dateStr) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    strcpy(newNode->task, task);
    newNode->status = 0; // Task is pending when added
    newNode->date = convertDate(dateStr);

    // If the list is empty, make the new task the head
    if (head == NULL) {
        head = newNode;
        head->link = head;
    } else {
        struct node* ptr = head;
        struct node* prev = NULL;

        // Find the correct position based on date
        do {
            if (newNode->date < ptr->date) {
                break;
            }
            prev = ptr;
            ptr = ptr->link;
        } while (ptr != head);

        // Insert the new node at the correct position
        if (prev == NULL) {
            // Insert at head
            while (ptr->link != head) {
                ptr = ptr->link;
            }
            newNode->link = head;
            head = newNode;
            ptr->link = head;
        } else {
            // Insert somewhere in the middle or at the end
            prev->link = newNode;
            newNode->link = ptr;
            if (ptr == head && newNode->date > prev->date) {
                // If inserted at the end, adjust the link back to head
                while (ptr->link != head) {
                    ptr = ptr->link;
                }
                ptr->link = newNode;
            }
        }
    }
}

// Mark a task as completed by task name
void markCompleted(char* task) {
    if (head == NULL) {
        printf("The To-Do List is empty.\n");
        return;
    }
    struct node* ptr = head;
    do {
        if (strcmp(ptr->task, task) == 0) {
            ptr->status = 1; // Mark as completed
            printf("Task '%s' marked as completed.\n", task);
            return;
        }
        ptr = ptr->link;
    } while (ptr != head);
    printf("Task '%s' not found.\n", task);
}

// Delete a task by name
void deleteTask(char* task) {
    if (head == NULL) {
        printf("The To-Do List is empty.\n");
        return;
    }
    if (strcmp(head->task, task) == 0 && head->link == head) {
        free(head);
        head = NULL;
        printf("Task '%s' deleted.\n", task);
        return;
    }
    if (strcmp(head->task, task) == 0) {
        struct node* temp = head;
        struct node* ptr = head;
        while (ptr->link != head) {
            ptr = ptr->link;
        }
        head = head->link;
        ptr->link = head;
        free(temp);
        printf("Task '%s' deleted.\n", task);
        return;
    }
    struct node* prev = head;
    struct node* curr = head->link;
    do {
        if (strcmp(curr->task, task) == 0) {
            prev->link = curr->link;
            free(curr);
            printf("Task '%s' deleted.\n", task);
            return;
        }
        prev = curr;
        curr = curr->link;
    } while (curr != head);
    printf("Task '%s' not found.\n", task);
}

// Search for a task by name
void searchTask(char* task) {
    if (head == NULL) {
        printf("The To-Do List is empty.\n");
        return;
    }
    struct node* ptr = head;
    do {
        if (strcmp(ptr->task, task) == 0) {
            printf("Task: %s | Date: %08d | Status: %s\n", ptr->task, ptr->date, (ptr->status == 0) ? "Pending" : "Completed");
            return;
        }
        ptr = ptr->link;
    } while (ptr != head);
    printf("Task '%s' not found.\n", task);
}

// Main function to handle menu
int main() {
    int choice;
    char task[100];
    char date[11]; // To store date in DD/MM/YYYY format

    while (1) {
        printf("\n--- To-Do List Menu ---\n");
        printf("1. Add Task\n");
        printf("2. Display Tasks\n");
        printf("3. Mark Task as Completed\n");
        printf("4. Delete a Task\n");
        printf("5. Search for a Task\n");
        printf("6. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        getchar();  // Consume newline character left by scanf

        switch (choice) {
            case 1:
                printf("Enter the task: ");
                fgets(task, 100, stdin);
                task[strcspn(task, "\n")] = 0; // Remove newline
                printf("Enter the date (DD/MM/YYYY): ");
                fgets(date, 11, stdin);
                date[strcspn(date, "\n")] = 0; // Remove newline
                InsertByDate(task, date);
                break;
            case 2:
                display();
                break;
            case 3:
                printf("Enter the task to mark as completed: ");
                fgets(task, 100, stdin);
                task[strcspn(task, "\n")] = 0; // Remove newline
                markCompleted(task);
                break;
            case 4:
                printf("Enter the task to delete: ");
                fgets(task, 100, stdin);
                task[strcspn(task, "\n")] = 0; // Remove newline
                deleteTask(task);
                break;
            case 5:
                printf("Enter the task to search: ");
                fgets(task, 100, stdin);
                task[strcspn(task, "\n")] = 0; // Remove newline
                searchTask(task);
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}