//question 3 
/*Name:Catherine Nduta
Reg no.:PA106/G/28730/25
Description:a c program
*/
#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

void inputIntegersToFile();
void processIntegers();
void displayFiles();
int handleFileError(FILE *file, const char *filename);

int main() {
    int choice;
    
    do {
        printf("\n=== Integer Processing Program ===\n");
        printf("1. Input 10 integers to file\n");
        printf("2. Process integers and calculate sum/average\n");
        printf("3. Display file contents\n");
        printf("4. Exit\n");
        printf("Enter your choice (1-4): ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                inputIntegersToFile();
                break;
            case 2:
                processIntegers();
                break;
            case 3:
                displayFiles();
                break;
            case 4:
                printf("Program terminated.\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 4);
    
    return 0;
}

int handleFileError(FILE *file, const char *filename) {
    if (file == NULL) {
        printf("Error: Cannot open file '%s'\n", filename);
        return 1; 
    }
    return ;
}

void inputIntegersToFile() {
    FILE *inputFile;
    int numbers[SIZE];
    int i;
    
    printf("Enter 10 integers:\n");
    for(i = 0; i < SIZE; i++) {
        printf("Enter integer %d: ", i + 1);
        scanf("%d", &numbers[i]);
    }
    
    inputFile = fopen("input.txt", "w");
    if(handleFileError(inputFile, "input.txt")) {
        return;
    }
    
    for(i = 0; i < SIZE; i++) {
        fprintf(inputFile, "%d\n", numbers[i]);
    }
    
    fclose(inputFile);
    printf("Successfully wrote 10 integers to 'input.txt'\n");
}
 
void processIntegers() {
    FILE *inputFile, *outputFile;
    int numbers[SIZE];
    int i, sum = 0;
    float average;
    
    inputFile = fopen("input.txt", "r");
    if(handleFileError(inputFile, "input.txt")) {
        return;
    }
    
    for(i = 0; i < SIZE; i++) {
        if(fscanf(inputFile, "%d", &numbers[i]) != 1) {
            printf("Error reading integer from file.\n");
            fclose(inputFile);
            return;
        }
        sum += numbers[i];
    }
    fclose(inputFile);
    
    average = (float)sum / SIZE;
    
    outputFile = fopen("output.txt", "w");
    if(handleFileError(outputFile, "output.txt")) {
        return;
    }
    
    fprintf(outputFile, "Sum: %d\n", sum);
    fprintf(outputFile, "Average: %.2f\n", average);
    
    fclose(outputFile);
    printf("Successfully calculated and wrote results to 'output.txt'\n");
    printf("Sum: %d, Average: %.2f\n", sum, average);
}

void displayFiles() {
    FILE *inputFile, *outputFile;
    char line[100];
    int number, count = 0;
    
    printf("\n=== Contents of input.txt ===\n");
    inputFile = fopen("input.txt", "r");
    if(handleFileError(inputFile, "input.txt")) {
	
    } else {
        printf("Integers stored in input.txt:\n");
        while(fscanf(inputFile, "%d", &number) == 1) {
            printf("Number %d: %d\n", ++count, number);
        }
        fclose(inputFile);
    }
    
    printf("\n=== Contents of output.txt ===\n");
    outputFile = fopen("output.txt", "r");
    if(handleFileError(outputFile, "output.txt")) {
        return;
    }
    
    printf("Calculation results:\n");
    while(fgets(line, sizeof(line), outputFile) != NULL) {
        printf("%s", line);
    }
    fclose(outputFile);
}