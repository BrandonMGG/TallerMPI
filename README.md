# Matrix Addition with MPI

Este repositorio contiene un programa en C que realiza la suma de matrices en paralelo utilizando la biblioteca MPI. También incluye scripts en Python (`comprobarResultados.py` y `plot.py`) para verificar los resultados y visualizar el rendimiento.

## Requisitos Previos
  1. **Virtual Machine:**
   - Plataforma de virtualización (por ejemplo, VirtualBox, VMware).
   - Máquina virtual con sistema operativo compatible (por ejemplo, Ubuntu, CentOS).

2. **Herramientas de Desarrollo:**
   - Compilador de C que sea compatible con MPI (por ejemplo, OpenMPI).
   - Herramientas de desarrollo de MPI (pueden variar según el sistema operativo).
     
- Python 3.x
- Bibliotecas Python: NumPy, Matplotlib (instalables mediante `pip install numpy matplotlib`)

## Instrucciones de Ejecución

1. **Compilación del Código:**

   ```bash
   mpicc matrix_addition_mpi.c -o matrix_addition_mpi
Ejecución del Programa MPI:
Ejecutar: mpirun -n <num_procesos> ./mpi
  reemplazar <num_procesos> con el número deseado de procesos MPI.
Verificación de Resultados con Python:
  comprobar.py: Este script verifica la corrección de los resultados generados por el programa 
 Ejecutar: python3 comprobar.py
Visualización de Rendimiento con Python:
  plot.py: Este script genera un gráfico del tiempo de ejecución en función del tamaño del mensaje.
 Ejecutar: python plot.py
