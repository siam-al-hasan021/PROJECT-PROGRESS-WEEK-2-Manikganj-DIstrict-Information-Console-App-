#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100

char **customEntries = NULL;
int entryCount = 0;

void showIntroduction() {
    printf("\n--- Introduction ---\n");
    printf("Manikganj is a district in central Bangladesh, located on the banks of the Jamuna River. \n");
    printf("It is known for its historical significance, natural beauty, and cultural heritage.\n");
}

void showHistory() {
    printf("\n--- History ---\n");
    printf("Manikganj has a rich history, dating back to the Mughal period. \n");
    printf("It played a significant role during the Liberation War of Bangladesh in 1971.\n");
}

void showTouristSpots() {
    printf("\n--- Tourist Spots ---\n");
    printf("1. Baliati Zamindar Bari - A grand palace showcasing the legacy of zamindars.\n");
    printf("2. Teota Zamindar Bari - Another historic palace with architectural beauty.\n");
    printf("3. Padma River - A popular spot for enjoying the natural beauty of the river.\n");
}

void showCulture() {
    printf("\n--- Culture ---\n");
    printf("Manikganj is known for its vibrant culture, including traditional music, dance, and festivals.\n");
    printf("The district is famous for its handloom weaving and pottery crafts.\n");
}

void provideName() {
    char name[50];
    printf("\nEnter your name: ");
    scanf(" %[^\n]", name);
    printf("Hello, %s! Welcome to the Manikganj Information App.\n", name);
}

void addEntry() {
    char temp[MAX_LENGTH];

    printf("\nEnter the new entry: ");
    scanf(" %[^\n]", temp);

    // Allocate memory for new entry
    customEntries = realloc(customEntries, (entryCount + 1) * sizeof(char *));
    if (!customEntries) {
        printf("Memory allocation failed.\n");
        return;
    }

    customEntries[entryCount] = malloc(strlen(temp) + 1);
    if (!customEntries[entryCount]) {
        printf("Memory allocation failed.\n");
        return;
    }

    strcpy(customEntries[entryCount], temp);
    entryCount++;

    printf("Entry added successfully.\n");
}

void removeEntry() {
    if (entryCount == 0) {
        printf("No entries to remove.\n");
        return;
    }

    int index;
    printf("\nEnter the index of the entry to remove (1-%d): ", entryCount);
    scanf("%d", &index);

    if (index < 1 || index > entryCount) {
        printf("Invalid index.\n");
        return;
    }

    free(customEntries[index - 1]);

    for (int i = index - 1; i < entryCount - 1; i++) {
        customEntries[i] = customEntries[i + 1];
    }

    entryCount--;
    customEntries = realloc(customEntries, entryCount * sizeof(char *));

    printf("Entry removed successfully.\n");
}

void showEntries() {
    if (entryCount == 0) {
        printf("\nNo entries to display.\n");
        return;
    }

    printf("\n--- Custom Entries ---\n");
    for (int i = 0; i < entryCount; i++) {
        printf("%d. %s\n", i + 1, customEntries[i]);
    }
}

void saveEntriesToFile() {
    FILE *file = fopen("entries.txt", "w");
    if (!file) {
        printf("Failed to save entries.\n");
        return;
    }

    for (int i = 0; i < entryCount; i++) {
        fprintf(file, "%s\n", customEntries[i]);
    }

    fclose(file);
    printf("Entries saved to 'entries.txt' successfully.\n");
}

void deleteAllEntries() {
    for (int i = 0; i < entryCount; i++) {
        free(customEntries[i]);
    }

    free(customEntries);
    customEntries = NULL;
    entryCount = 0;

    printf("All entries have been deleted.\n");
}

int main() {
    int choice;

    provideName();

    do {
        printf("\n=== Manikganj Information App ===\n");
        printf("1. Introduction\n");
        printf("2. History\n");
        printf("3. Tourist Spots\n");
        printf("4. Culture\n");
        printf("5. Add Entry\n");
        printf("6. Remove Entry\n");
        printf("7. Show Entries\n");
        printf("8. Save Entries to File\n");
        printf("9. Delete All Entries\n");
        printf("10. Exit\n");
        printf("Enter your choice (1-10): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                showIntroduction();
                break;
            case 2:
                showHistory();
                break;
            case 3:
                showTouristSpots();
                break;
            case 4:
                showCulture();
                break;
            case 5:
                addEntry();
                break;
            case 6:
                removeEntry();
                break;
            case 7:
                showEntries();
                break;
            case 8:
                saveEntriesToFile();
                break;
            case 9:
                deleteAllEntries();
                break;
            case 10:
                printf("\nExiting the app. Thank you!\n");
                break;
            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    } while (choice != 10);

    deleteAllEntries();  // Free allocated memory before exiting

    return 0;
}