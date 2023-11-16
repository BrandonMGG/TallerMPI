MATRIX_SIZE = 300  # Puedes ajustar esto según el tamaño real de tus matrices

def perform_local_matrix_addition(matrixA, matrixB, result, start_row, end_row):
    for i in range(start_row, end_row):
        for j in range(MATRIX_SIZE):
            result[i][j] = matrixA[i][j] + matrixB[i][j]

# Leer la matriz desde un archivo de texto
def read_matrix_from_file(filename):
    matrix = []
    with open(filename, 'r') as file:
        for line in file:
            row = [int(x) for x in line.split()]
            matrix.append(row)
    return matrix

# Escribir la matriz en un archivo de texto
def write_matrix_to_file(matrix, filename):
    with open(filename, 'w') as file:
        for row in matrix:
            file.write(' '.join(map(str, row)) + '\n')

# Rutas de los archivos
fileA = 'original_matrices.txt'
fileB = 'original_matrices.txt'
fileResult = 'distributed_results.txt'

# Leer las matrices desde los archivos
matrixA = read_matrix_from_file(fileA)
matrixB = read_matrix_from_file(fileB)

# Inicializar la matriz resultante con ceros
result = [[0 for _ in range(MATRIX_SIZE)] for _ in range(MATRIX_SIZE)]

# Realizar la suma de matrices
perform_local_matrix_addition(matrixA, matrixB, result, 0, MATRIX_SIZE)


# Leer la matriz resultado desde el archivo
result_from_file = read_matrix_from_file(fileResult)

# Comparar si la matriz resultante es igual a la leída desde el archivo
if result == result_from_file:
    print("Las matrices son iguales.")
else:
    print("Las matrices son diferentes.")