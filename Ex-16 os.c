#include <stdio.h>
#include <stdlib.h>

// Define the structure for employee details
struct Employee {
    int empID;
    char name[50];
    float salary;
};

// Function declarations
void addRecord(FILE *file);
void displayRecords(FILE *file);
void updateRecord(FILE *file);
void deleteRecord(FILE *file);

int main() {
    FILE *file;
    file = fopen("employee.dat", "rb+");

    if (file == NULL) {
        // If the file doesn't exist, create it
        file = fopen("employee.dat", "wb+");
        if (file == NULL) {
            printf("Error creating file!\n");
            return 1;
        }
    }

    int choice;
    do {
        printf("\nEmployee Database Menu\n");
        printf("1. Add Record\n");
        printf("2. Display Records\n");
        printf("3. Update Record\n");
        printf("4. Delete Record\n");
        printf("0. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addRecord(file);
                break;
            case 2:
                displayRecords(file);
                break;
            case 3:
                updateRecord(file);
                break;
            case 4:
                deleteRecord(file);
                break;
            case 0:
                break;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    } while (choice != 0);

    fclose(file);

    return 0;
}

void addRecord(FILE *file) {
    struct Employee emp;

    printf("Enter employee details:\n");
    printf("Employee ID: ");
    scanf("%d", &emp.empID);
    printf("Name: ");
    scanf("%s", emp.name);
    printf("Salary: ");
    scanf("%f", &emp.salary);

    fseek(file, 0, SEEK_END); // Move the file pointer to the end of the file
    fwrite(&emp, sizeof(struct Employee), 1, file);

    printf("Record added successfully!\n");
}

void displayRecords(FILE *file) {
    struct Employee emp;

    rewind(file); // Move the file pointer to the beginning of the file

    printf("\nEmployee Records:\n");
    printf("%-10s %-30s %-10s\n", "Emp ID", "Name", "Salary");
    printf("=======================================\n");

    while (fread(&emp, sizeof(struct Employee), 1, file) == 1) {
        printf("%-10d %-30s %-10.2f\n", emp.empID, emp.name, emp.salary);
    }
}

void updateRecord(FILE *file) {
    struct Employee emp;
    int empID;

    printf("Enter the employee ID to update: ");
    scanf("%d", &empID);

    int found = 0;
    while (fread(&emp, sizeof(struct Employee), 1, file) == 1) {
        if (emp.empID == empID) {
            found = 1;

            printf("Enter new details:\n");
            printf("Name: ");
            scanf("%s", emp.name);
            printf("Salary: ");
            scanf("%f", &emp.salary);

            fseek(file, -sizeof(struct Employee), SEEK_CUR); // Move the file pointer back to the beginning of the record
            fwrite(&emp, sizeof(struct Employee), 1, file);

            printf("Record updated successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("Employee with ID %d not found!\n", empID);
    }
}

void deleteRecord(FILE *file) {
    struct Employee emp;
    int empID;

    printf("Enter the employee ID to delete: ");
    scanf("%d", &empID);

    FILE *tempFile = fopen("temp.dat", "wb");
    if (tempFile == NULL) {
        printf("Error creating temporary file!\n");
        return;
    }

    int found = 0;
    while (fread(&emp, sizeof(struct Employee), 1, file) == 1) {
        if (emp.empID == empID) {
            found = 1;
            printf("Record deleted successfully!\n");
        } else {
            fwrite(&emp, sizeof(struct Employee), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("employee.dat");
    rename("temp.dat", "employee.dat");

    if (!found) {
        printf("Employee with ID %d not found!\n", empID);
    }

    file = fopen("employee.dat", "rb+");
}

