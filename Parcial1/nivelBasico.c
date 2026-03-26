#include <stdio.h>

#define N 50

// Variables globales
int arreglo[N];
int n = 0;
int datosRegistrados = 0; // 1 si hay datos, 0 si no

// Declaracion de funciones
void mostrarMenu();
void registrarDatos();
void mostrar();
void bubbleSort(int arr[], int n);
void selectionSort(int arr[], int n);
void insertionSort(int arr[], int n);

// Funcion para mostrar el arreglo
void mostrar() {
    printf(" ");
    for (int i = 0; i < n; i++) {
        printf("%d - ", arreglo[i]);
    }
    printf("\n");
}

// Funcion para registrar datos
void registrarDatos() {
    printf("\n     REGISTRAR DATOS    \n");
    printf("Cuantos datos desea ingresar? (maximo %d): ", N);
    scanf("%d", &n);

    if (n <= 0 || n > N) {
        printf("Cantidad invalida. Intente de nuevo.\n");
        n = 0;
        datosRegistrados = 0;
        return;
    }

    printf("Ingrese los %d valores:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Elemento [%d]: ", i + 1);
        scanf("%d", &arreglo[i]);
    }

    datosRegistrados = 1; // Habilitar las demas opciones
    printf("\nDatos registrados correctamente.\n");
    mostrar();
}

// Metodo Burbuja
void bubbleSort(int arr[], int n) {
    printf("\n===== ORDENAMIENTO BURBUJA =====\n");
    printf("Arreglo inicial: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    for (int i = 0; i < n - 1; i++) {
        printf("PASADA %d:\n", i + 1);
        int paso = 1;
        
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int Temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = Temp;
                printf("  Paso %d: ", paso);
                for (int k = 0; k < n; k++) {
                    printf("%d ", arr[k]);
                }
                printf("\n");
            }
            paso++;
        }
        printf("  Fin de pasada %d\n\n", i + 1);
    }

    printf("\n*** Arreglo ordenado: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("***\n");
}

// Metodo Seleccion
void selectionSort(int arr[], int n) {
    printf("\n===== ORDENAMIENTO SELECCION =====\n");
    printf("Arreglo inicial: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    for (int i = 0; i < n - 1; i++) {
        printf("PASADA %d:\n", i + 1);
        
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            int Temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = Temp;
            printf("  Paso 1: ");
            for (int k = 0; k < n; k++) {
                printf("%d ", arr[k]);
            }
            printf("\n");
        }
        printf("  Fin de pasada %d\n\n", i + 1);
    }

    printf("\n*** Arreglo ordenado: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("***\n");
}

// Metodo Insercion
void insertionSort(int arr[], int n) {
    printf("\n===== ORDENAMIENTO INSERCION =====\n");
    printf("Arreglo inicial: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    for (int i = 1; i < n; i++) {
        printf("PASADA %d:\n", i);
        
        int clave = arr[i];
        int j = i - 1;
        int paso = 1;

        while (j >= 0 && arr[j] > clave) {
            arr[j + 1] = arr[j];
            j--;
            printf("  Paso %d: ", paso);
            for (int k = 0; k < n; k++) {
                printf("%d ", arr[k]);
            }
            printf("\n");
            paso++;
        }

        arr[j + 1] = clave;
        
        if (paso > 1) {
            printf("  Paso %d: ", paso);
            for (int k = 0; k < n; k++) {
                printf("%d ", arr[k]);
            }
            printf("\n");
        }
        
        printf("  Fin de pasada %d\n\n", i);
    }

    printf("\n*** Arreglo ordenado: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("***\n");
}


//  mostrar el menu
void mostrarMenu() {
    printf("\n\n");
    printf("        MENU DE OPERACIONES     \n");
    printf("\n");
    printf("1. Registrar datos en el vector\n");

    if (datosRegistrados) {
        printf("2. Mostrar el arreglo original\n");
        printf("3. Ordenar mediante metodo Burbuja\n");
        printf("4. Ordenar mediante metodo Seleccion\n");
        printf("5. Ordenar mediante metodo Insercion\n");
        printf("6. Salir\n");
    } else {
        printf("2. Mostrar el arreglo original (deshabilitado)\n");
        printf("3. Ordenar mediante metodo Burbuja (deshabilitado)\n");
        printf("4. Ordenar mediante metodo Seleccion (deshabilitado)\n");
        printf("5. Ordenar mediante metodo Insercion (deshabilitado)\n");
        printf("6. Salir\n");
    }

    printf("  \n");
}


int main() {
    int opcion;

    while (1) {
        mostrarMenu();
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                registrarDatos();
                break;

            case 2:
                if (!datosRegistrados) {
                    printf("\nOpcion deshabilitada. Primero debe registrar datos.\n");
                } else {
                    mostrar();
                }
                break;

            case 3:
                if (!datosRegistrados) {
                    printf("\nOpcion deshabilitada. Primero debe registrar datos.\n");
                } else {
                    int copia[N];
                    for (int i = 0; i < n; i++) {
                        copia[i] = arreglo[i];
                    }
                    bubbleSort(copia, n);
                }
                break;

            case 4:
                if (!datosRegistrados) {
                    printf("\nOpcion deshabilitada. Primero debe registrar datos.\n");
                } else {
                    int copia[N];
                    for (int i = 0; i < n; i++) {
                        copia[i] = arreglo[i];
                    }
                    selectionSort(copia, n);
                }
                break;

            case 5:
                if (!datosRegistrados) {
                    printf("\nOpcion deshabilitada. Primero debe registrar datos (Opcion 1).\n");
                } else {
                    int copia[N];
                    for (int i = 0; i < n; i++) {
                        copia[i] = arreglo[i];
                    }
                    insertionSort(copia, n);
                }
                break;

            case 6:
                printf("\nPrograma cerrado\n");
                return 0;

            default:
                printf("\nOpcion invalida. Intente de nuevo.\n");
        }
    }

    return 0;
}

