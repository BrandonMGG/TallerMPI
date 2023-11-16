#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

#define MATRIX_SIZE 300

void printMatrix(FILE *file, int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            fprintf(file, "%d ", matrix[i][j]);
        }
        fprintf(file, "\n");
    }
}

void fillMatrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            matrix[i][j] = j; 
        }
    }
}

void writeMatrixToFile(const char *filename, const char *matrixName, int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error: Unable to open file for writing");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    fprintf(file, "%s:\n", matrixName);
    printMatrix(file, matrix);

    fclose(file);
}

void performLocalMatrixAddition(int matrixA[MATRIX_SIZE][MATRIX_SIZE], int matrixB[MATRIX_SIZE][MATRIX_SIZE],
                                int result[MATRIX_SIZE][MATRIX_SIZE], int startRow, int endRow) {
    for (int i = startRow; i < endRow; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            result[i][j] = matrixA[i][j] + matrixB[i][j];
        }
    }
}

void broadcastMatrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    MPI_Bcast(matrix, MATRIX_SIZE * MATRIX_SIZE, MPI_INT, 0, MPI_COMM_WORLD);
}

void gatherResults(int result[MATRIX_SIZE][MATRIX_SIZE], int chunkSize, int cols) {
    MPI_Gather(result, chunkSize * cols, MPI_INT, result, chunkSize * cols, MPI_INT, 0, MPI_COMM_WORLD);
}

void synchronizeProcesses() {
    MPI_Barrier(MPI_COMM_WORLD);
}

int main(int argc, char **argv) {
    int priority, numProcesses;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &priority);
    MPI_Comm_size(MPI_COMM_WORLD, &numProcesses);

    const int rows = MATRIX_SIZE;
    const int cols = MATRIX_SIZE;
    int matrixA[rows][cols], matrixB[rows][cols], result[rows][cols];
    int dataLen = rows / numProcesses;
    int startRow = priority * dataLen;
    int endRow = (priority + 1) * dataLen;

    FILE *file = fopen("output.txt", "w");
    if (file == NULL) {
        fprintf(stderr, "Error opening file.\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    for (int messageSize = 1; messageSize <= MATRIX_SIZE * MATRIX_SIZE; messageSize += 9) {
        double startTime = MPI_Wtime();
        performLocalMatrixAddition(matrixA, matrixB, result, startRow, endRow);
        double endTime = MPI_Wtime();
        if (priority == 0) {
            fillMatrix(matrixA);

            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    matrixB[i][j] = matrixA[i][j];
                }
            }

            double executionTime = endTime - startTime;
            fprintf(file, "Message Size: %d \t Execution Time: %f seconds\n", messageSize, executionTime);
        }

        MPI_Barrier(MPI_COMM_WORLD); 

        MPI_Bcast(matrixA, messageSize, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast(matrixB, messageSize, MPI_INT, 0, MPI_COMM_WORLD);

       
        gatherResults(result, dataLen, cols);

        synchronizeProcesses();

        if (priority == 0) {
           
            double executionTime = endTime - startTime;
            printf("Message Size: %d \t Execution Time: %f seconds\n", messageSize, executionTime);
        }
    }

    MPI_Finalize();

    return 0;
}