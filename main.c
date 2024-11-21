#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define processes 5 // (P0, P1, P2, P3, P4)
#define resources 3 // (A, B, C)

// function to calculate the Need matrix
void calculateNeed(int need[processes][resources], int max[processes][resources], int allocation[processes][resources]) {
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            // need = max - allocation
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}


// function to check if the system is in a safe state
bool isSafe(int available[resources], int allocation[processes][resources], int need[processes][resources], int safeSequence[processes]) {
    bool finish[processes] = {false}; // marks processes that have finished
    int work[resources]; // work array to track available resources

    // Copy available resources into work
    for (int i = 0; i < resources; i++) {
        work[i] = available[i];
    }

    int count = 0; // count of finished processes
    int sequenceIndex = 0; // tracks where we are in the safe sequence

    // Attempt to find a safe sequence
    while (count < processes) {
        bool foundProcess = false;
        
        // Try to find a process that can execute
        for (int i = 0; i < processes; i++) {
            if (!finish[i]) {
                bool canExecute = true;

                // Check if we can satisfy all the resource needs of process i
                for (int j = 0; j < resources; j++) {
                    if (need[i][j] > work[j]) {
                        canExecute = false;
                        break;
                    }
                }

                // If process i can execute, update available resources
                if (canExecute) {
                    finish[i] = true;
                    safeSequence[sequenceIndex++] = i;

                    // Add the allocated resources of process i to work (available resources)
                    for (int j = 0; j < resources; j++) {
                        work[j] += allocation[i][j];
                    }
                    count++;
                    foundProcess = true;
                    break;
                }
            }
        }

        // If no process can be executed in this cycle, we have a deadlock
        if (!foundProcess) {
            printf("Deadlock detected: No process can be executed\n");
            return false; // System is in an unsafe state
        }
    }

    return true; // All processes can be executed, so the system is in a safe state
}





int main() {
    int allocation[processes][resources];
    int max[processes][resources];
    int available[resources];
    int need[processes][resources];
    int safeSequence[processes];

    FILE *inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("Error opening file.\n");
        return -1;
    }

    // read available resources
    for (int i = 0; i < resources; i++) {
        fscanf(inputFile, "%d", &available[i]);
    }

    // read the allocation matrix
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            fscanf(inputFile, "%d", &allocation[i][j]);
        }
    }

    // read the max matrix
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            fscanf(inputFile, "%d", &max[i][j]);
        }
    }

    fclose(inputFile);

    // calculate the Need matrix
    calculateNeed(need, max, allocation);

    // check if the system is in a safe state and print the safe sequence
    if (isSafe(available, allocation, need, safeSequence)) {
        printf("The system is in a safe state.\nSafe sequence: ");
        for (int i = 0; i < processes; i++) {
            printf("P%d ", safeSequence[i]);
        }
        printf("\n");
    } else {
        printf("The system is not in a safe state.\n");
    }

    return 0;
}
