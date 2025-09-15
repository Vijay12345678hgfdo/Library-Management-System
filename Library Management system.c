

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {
    int id;
    char title[50];
    char author[50];
};

void addBook() {
    struct Book b;
    FILE *fp = fopen("library.dat", "ab");
    if (fp == NULL) {
        printf("Unable to open file!\n");
        return;
    }
    printf("Enter Book ID: ");
    scanf("%d", &b.id);
    getchar(); // consume newline
    printf("Enter Book Title: ");
    fgets(b.title, 50, stdin);
    b.title[strcspn(b.title, "\n")] = 0; // remove newline
    printf("Enter Author Name: ");
    fgets(b.author, 50, stdin);
    b.author[strcspn(b.author, "\n")] = 0; // remove newline

    fwrite(&b, sizeof(struct Book), 1, fp);
    fclose(fp);
    printf("Book added successfully!\n");
}

void displayBooks() {
    struct Book b;
    FILE *fp = fopen("library.dat", "rb");
    if (fp == NULL) {
        printf("No books found.\n");
        return;
    }
    printf("\n--- All Books ---\n");
    while (fread(&b, sizeof(struct Book), 1, fp)) {
        printf("ID: %d | Title: %s | Author: %s\n", b.id, b.title, b.author);
    }
    fclose(fp);
}

void searchBook() {
    int searchId;
    struct Book b;
    FILE *fp = fopen("library.dat", "rb");
    if (fp == NULL) {
        printf("No books found.\n");
        return;
    }
    printf("Enter Book ID to search: ");
    scanf("%d", &searchId);

    int found = 0;
    while (fread(&b, sizeof(struct Book), 1, fp)) {
        if (b.id == searchId) {
            printf("Book Found: ID: %d | Title: %s | Author: %s\n", b.id, b.title, b.author);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Book not found.\n");
    }
    fclose(fp);
}

void deleteBook() {
    int delId;
    struct Book b;
    FILE *fp = fopen("library.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");
    if (fp == NULL) {
        printf("No books found.\n");
        return;
    }
    printf("Enter Book ID to delete: ");
    scanf("%d", &delId);

    int found = 0;
    while (fread(&b, sizeof(struct Book), 1, fp)) {
        if (b.id != delId) {
            fwrite(&b, sizeof(struct Book), 1, temp);
        } else {
            found = 1;
        }
    }
    fclose(fp);
    fclose(temp);

    remove("library.dat");
    rename("temp.dat", "library.dat");

    if (found) {
        printf("Book deleted successfully.\n");
    } else {
        printf("Book not found.\n");
    }
}

int main() {
    int choice;
    while (1) {
        printf("\nLibrary Management System\n");
        printf("1. Add Book\n");
        printf("2. Display Books\n");
        printf("3. Search Book\n");
        printf("4. Delete Book\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: searchBook(); break;
            case 4: deleteBook(); break;
            case 5: exit(0);
            default: printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}
