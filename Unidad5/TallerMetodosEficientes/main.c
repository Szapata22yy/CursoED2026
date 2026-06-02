/*
 * Unidad 5 - Taller Metodos Eficientes
 * Autores: [Nombre Completo 1], [Nombre Completo 2]
 * Fecha: 2026
 *
 * Programa para gestionar el peso de hasta 30 contenedores
 * en un patio de carga usando ordenamiento y busqueda binaria.
 */

// Librería para entrada/salida (printf, scanf)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Constante que define el número máximo de contenedores que se pueden registrar
#define MAX_CONTENEDORES 30

// Array que almacena los pesos de los contenedores
int pesos[MAX_CONTENEDORES];
// Bandera que indica si el arreglo está ordenado (1) o no (0)
int ordenado = 0;
// Variable que almacena la cantidad actual de contenedores registrados
int cantidadContenedores = 0;

void mostrarMenu(void);
int leerEntero(const char *mensaje, int minimo, int maximo);
void registrarPesosManual(void);
void generarPesosAleatorios(void);
void mostrarContenedores(void);
void bubbleSort(int arr[], int n);
void merge(int arr[], int left, int mid, int right);
void mergeSort(int arr[], int left, int right);
void heapify(int arr[], int n, int i);
void heapSort(int arr[], int n);
void ordenarMetodo1(void);
void ordenarMetodo2(void);
void ordenarMetodo3(void);
int busquedaBinaria(int arr[], int n, int valor);
void buscarContenedor(void);
void pausar(void);

// Función principal del programa
int main(void)
{
    int opcion;
    // Inicializa la semilla aleatoria usando el tiempo actual del sistema
    srand((unsigned int)time(NULL));

    // Bucle principal del programa que se ejecuta hasta que el usuario seleccione salir
    do
    {
        // Muestra el menú de opciones
        mostrarMenu();
        // Lee la opción seleccionada por el usuario
        opcion = leerEntero("", 1, 8);

        // Switch que ejecuta la acción correspondiente según la opción seleccionada
        switch (opcion)
        {
            // Opción 1: Registrar pesos manualmente
            case 1:
                registrarPesosManual();
                break;
            // Opción 2: Generar pesos aleatorios y mostrar contenedores
            case 2:
                generarPesosAleatorios();
                mostrarContenedores();
                break;
            // Opción 3: Mostrar los contenedores registrados
            case 3:
                mostrarContenedores();
                break;
            // Opción 4: Ordenar usando Bubble Sort
            case 4:
                ordenarMetodo1();
                mostrarContenedores();
                break;
            // Opción 5: Ordenar usando Merge Sort
            case 5:
                ordenarMetodo2();
                mostrarContenedores();
                break;
            // Opción 6: Ordenar usando Heap Sort
            case 6:
                ordenarMetodo3();
                mostrarContenedores();
                break;
            // Opción 7: Buscar un contenedor usando búsqueda binaria
            case 7:
                buscarContenedor();
                break;
            // Opción 8: Salir del programa
            case 8:
                printf("Saliendo del programa...\n");
                break;
            // Opción inválida: mostrar mensaje de error
            default:
                printf("Opcion invalida. Intente de nuevo.\n");
        }

        // Si no es salir, pausa el programa para que el usuario vea los resultados
        if (opcion != 8)
        {
            pausar();
        }
    } while (opcion != 8);  // Continúa hasta que el usuario seleccione salir

    return 0;  // Fin del programa
}

// Función que muestra el menú principal del programa
void mostrarMenu(void)
{
    // Imprime el título y opciones del menú
    printf("\n========================================\n");
    printf("\nSistema de organizacion de Contenedores\n");
    printf("\nMUELLE DE CARGA\n");
    printf("\n========================================\n");
    printf("1. Registrar peso de contenedores manualmente\n");
    printf("2. Generar pesos aleatorios de contenedores\n");
    printf("3. Mostrar contenedores registrados\n");
    printf("4. Ordenar contenedores Metodo 1\n");
    printf("5. Ordenar contenedores Metodo 2\n");
    printf("6. Ordenar contenedores Metodo 3\n");
    printf("7. Buscar contenedor\n");
    printf("8. Salir\n");
    printf("========================================\n");
    printf("Seleccione una opcion\n");
}

// Función que lee un entero del usuario dentro de un rango especificado
// Parámetros: mensaje (texto a mostrar), minimo y maximo (rango válido)
int leerEntero(const char *mensaje, int minimo, int maximo)
{
    int valor;  // Variable para almacenar el valor ingresado
    int resultado;  // Variable para verificar si scanf tuvo éxito

    // Bucle que se repite hasta obtener un valor válido
    do
    {
        // Muestra el mensaje solicitando entrada
        printf("%s", mensaje);
        // Intenta leer un entero del usuario
        resultado = scanf("%d", &valor);
        // Limpia el buffer de entrada para evitar problemas con lecturas posteriores
        while (getchar() != '\n');

        // Valida que la lectura fue exitosa y que el valor está dentro del rango
        if (resultado != 1 || valor < minimo || valor > maximo)
        {
            // Muestra un error si la entrada es inválida
            printf("Entrada invalida. Ingrese un numero entre %d y %d.\n", minimo, maximo);
        }
        else
        {
            // Sale del bucle si la entrada es válida
            break;
        }
    } while (1);  // Continúa hasta obtener una entrada válida

    return valor;  // Retorna el valor válido ingresado
}

// Función que permite al usuario registrar manualmente los pesos de los contenedores
void registrarPesosManual(void)
{
    // Lee la cantidad de contenedores a registrar
    int cantidad = leerEntero("Ingrese la cantidad de contenedores a registrar (1-30): ", 1, MAX_CONTENEDORES);

    // Bucle que itera sobre cada contenedor para leer su peso
    for (int i = 0; i < cantidad; i++)
    {
        char mensaje[80];  // Buffer para construir el mensaje
        // Construye un mensaje personalizado para cada contenedor
        sprintf(mensaje, "Peso del contenedor %d: ", i + 1);
        // Lee y almacena el peso del contenedor
        pesos[i] = leerEntero(mensaje, 0, 1000000);
    }

    // Actualiza las variables globales
    cantidadContenedores = cantidad;  // Registra la cantidad de contenedores
    ordenado = 0;  // Marca que el arreglo no está ordenado
    printf("Contenedores registrados correctamente.\n");
    printf("\nContenedores registrados:\n");
    // Muestra los contenedores registrados
    for (int i = 0; i < cantidad; i++)
    {
        printf("#%d = %dkg\n", i + 1, pesos[i]);
    }
}

// Función que genera pesos aleatorios para los contenedores
void generarPesosAleatorios(void)
{
    // Lee la cantidad de contenedores a generar
    int cantidad = leerEntero("Ingrese la cantidad de contenedores a generar (1-30): ", 1, MAX_CONTENEDORES);

    // Bucle que genera pesos aleatorios para cada contenedor
    for (int i = 0; i < cantidad; i++)
    {
        // Genera un número aleatorio entre 0 y 1000 kg
        pesos[i] = rand() % 1001;
    }

    // Actualiza las variables globales
    cantidadContenedores = cantidad;  // Registra la cantidad de contenedores
    ordenado = 0;  // Marca que el arreglo no está ordenado
    printf("Pesos aleatorios generados correctamente.\n");
    printf("\nContenedores generados:\n");
    // Muestra los contenedores generados
    for (int i = 0; i < cantidad; i++)
    {
        printf("#%d = %dkg\n", i + 1, pesos[i]);
    }
}

// Función que muestra todos los contenedores registrados actualmente
void mostrarContenedores(void)
{
    // Verifica si hay contenedores registrados
    if (cantidadContenedores == 0)
    {
        printf("No hay contenedores registrados.\n");
        return;  // Sale de la función si no hay contenedores
    }

    // Muestra el título con la cantidad de contenedores
    printf("\nContenedores (cantidad = %d):\n", cantidadContenedores);
    // Itera sobre todos los contenedores y los muestra
    for (int i = 0; i < cantidadContenedores; i++)
    {
        printf("#%d = %dkg\n", i + 1, pesos[i]);
    }
}

// Función que implementa el algoritmo de ordenamiento Bubble Sort (Ordenamiento de Burbuja)
// Parámetro: arr (arreglo a ordenar), n (tamaño del arreglo)
void bubbleSort(int arr[], int n)
{
    // Bucle externo que itera sobre el arreglo
    for (int i = 0; i < n - 1; i++)
    {
        int intercambiado = 0;  // Bandera para optimización (si no hay cambios, sale)
        // Bucle interno que compara elementos adyacentes
        for (int j = 0; j < n - 1 - i; j++)
        {
            // Si el elemento actual es mayor que el siguiente, intercambia
            if (arr[j] > arr[j + 1])
            {
                // Intercambio de elementos: usa una variable temporal
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                intercambiado = 1;  // Marca que hubo un intercambio
            }
        }
        // Optimización: si no hubo intercambios, el arreglo ya está ordenado
        if (!intercambiado)
        {
            break;  // Sale del bucle externo
        }
    }
}

// Función auxiliar que fusiona dos subarreglos ordenados para el Merge Sort
// Parámetros: arr (arreglo), left (inicio), mid (punto medio), right (fin)
void merge(int arr[], int left, int mid, int right)
{
    // Calcula el tamaño de los dos subarreglos
    int n1 = mid - left + 1;  // Tamaño del subarreglo izquierdo
    int n2 = right - mid;  // Tamaño del subarreglo derecho
    // Arrays temporales para almacenar los subarreglos
    int L[MAX_CONTENEDORES];
    int R[MAX_CONTENEDORES];

    // Copia datos al subarreglo izquierdo
    for (int i = 0; i < n1; i++)
    {
        L[i] = arr[left + i];
    }
    // Copia datos al subarreglo derecho
    for (int j = 0; j < n2; j++)
    {
        R[j] = arr[mid + 1 + j];
    }

    // Inicializa índices para los subarreglos y el arreglo principal
    int i = 0;  // Índice para L
    int j = 0;  // Índice para R
    int k = left;  // Índice para arr

    // Fusiona los dos subarreglos comparando elementos
    while (i < n1 && j < n2)
    {
        // Inserta el elemento menor en el arreglo principal
        if (L[i] <= R[j])
        {
            arr[k++] = L[i++];
        }
        else
        {
            arr[k++] = R[j++];
        }
    }

    // Copia los elementos restantes de L, si los hay
    while (i < n1)
    {
        arr[k++] = L[i++];
    }

    // Copia los elementos restantes de R, si los hay
    while (j < n2)
    {
        arr[k++] = R[j++];
    }
}

// Función que implementa el algoritmo Merge Sort (Ordenamiento por Mezcla)
// Parámetros: arr (arreglo), left (índice izquierdo), right (índice derecho)
void mergeSort(int arr[], int left, int right)
{
    // Condición base: si hay más de un elemento
    if (left < right)
    {
        // Calcula el punto medio del arreglo
        int mid = (left + right) / 2;
        // Ordena recursivamente la mitad izquierda
        mergeSort(arr, left, mid);
        // Ordena recursivamente la mitad derecha
        mergeSort(arr, mid + 1, right);
        // Fusiona las dos mitades ordenadas
        merge(arr, left, mid, right);
    }
}

// Función auxiliar que mantiene la propiedad de montículo (Heap) para el Heap Sort
// Parámetros: arr (arreglo), n (tamaño), i (índice del nodo actual)
void heapify(int arr[], int n, int i)
{
    // Asume que el nodo actual es el más grande
    int largest = i;
    // Calcula los índices de los hijos izquierdo y derecho
    int left = 2 * i + 1;  // Hijo izquierdo
    int right = 2 * i + 2;  // Hijo derecho

    // Si el hijo izquierdo es mayor que el nodo actual, actualiza largest
    if (left < n && arr[left] > arr[largest])
    {
        largest = left;
    }
    // Si el hijo derecho es mayor que el nodo actual, actualiza largest
    if (right < n && arr[right] > arr[largest])
    {
        largest = right;
    }
    // Si largest cambió, intercambia y hace heapify recursivamente
    if (largest != i)
    {
        // Intercambia los elementos
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        // Llama heapify recursivamente en el subárbol afectado
        heapify(arr, n, largest);
    }
}

// Función que implementa el algoritmo Heap Sort (Ordenamiento por Montículo)
// Parámetro: arr (arreglo a ordenar), n (tamaño del arreglo)
void heapSort(int arr[], int n)
{
    // Primer paso: Construir el montículo (heap) máximo
    // Itera desde el último nodo no-hoja hasta la raíz
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(arr, n, i);
    }

    // Segundo paso: Extraer elementos uno por uno del montículo
    for (int i = n - 1; i > 0; i--)
    {
        // Intercambia la raíz (elemento máximo) con el último elemento
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        // Hace heapify en el árbol reducido
        heapify(arr, i, 0);
    }
}

// Función que ordena los contenedores usando el Método 1 (Bubble Sort)
void ordenarMetodo1(void)
{
    // Verifica si hay contenedores registrados
    if (cantidadContenedores == 0)
    {
        printf("No hay contenedores para ordenar.\n");
        return;  // Sale si no hay contenedores
    }

    // Llama a bubbleSort para ordenar los contenedores
    bubbleSort(pesos, cantidadContenedores);
    // Marca que el arreglo está ordenado
    ordenado = 1;
    printf("Contenedores ordenados correctamente con el Metodo 1 (Bubble Sort optimizado).\n");
}

// Función que ordena los contenedores usando el Método 2 (Merge Sort)
void ordenarMetodo2(void)
{
    // Verifica si hay contenedores registrados
    if (cantidadContenedores == 0)
    {
        printf("No hay contenedores para ordenar.\n");
        return;  // Sale si no hay contenedores
    }

    // Llama a mergeSort para ordenar los contenedores
    mergeSort(pesos, 0, cantidadContenedores - 1);
    // Marca que el arreglo está ordenado
    ordenado = 1;
    printf("Contenedores ordenados correctamente con el Metodo 2 (Merge Sort).\n");
}

// Función que ordena los contenedores usando el Método 3 (Heap Sort)
void ordenarMetodo3(void)
{
    // Verifica si hay contenedores registrados
    if (cantidadContenedores == 0)
    {
        printf("No hay contenedores para ordenar.\n");
        return;  // Sale si no hay contenedores
    }

    // Llama a heapSort para ordenar los contenedores
    heapSort(pesos, cantidadContenedores);
    // Marca que el arreglo está ordenado
    ordenado = 1;
    printf("Contenedores ordenados correctamente con el Metodo 3 (Heap Sort).\n");
}

// Función que implementa la búsqueda binaria en un arreglo ordenado
// Parámetros: arr (arreglo ordenado), n (tamaño), valor (elemento a buscar)
// Retorna: índice del elemento si se encuentra, -1 si no se encuentra
int busquedaBinaria(int arr[], int n, int valor)
{
    // Inicializa los límites de búsqueda
    int izquierda = 0;  // Índice del inicio
    int derecha = n - 1;  // Índice del final

    // Bucle que continúa mientras hay elementos por revisar
    while (izquierda <= derecha)
    {
        // Calcula el índice del elemento medio
        int medio = izquierda + (derecha - izquierda) / 2;

        // Si encuentra el valor, retorna su índice
        if (arr[medio] == valor)
        {
            return medio;
        }
        // Si el valor es mayor que el elemento medio, busca en la mitad derecha
        else if (arr[medio] < valor)
        {
            izquierda = medio + 1;
        }
        // Si el valor es menor que el elemento medio, busca en la mitad izquierda
        else
        {
            derecha = medio - 1;
        }
    }

    return -1;  // Retorna -1 si el valor no se encuentra
}

// Función que busca un contenedor por su peso usando búsqueda binaria
void buscarContenedor(void)
{
    // Verifica si hay contenedores registrados
    if (cantidadContenedores == 0)
    {
        printf("No hay contenedores registrados para buscar.\n");
        return;  // Sale si no hay contenedores
    }

    // Verifica que el arreglo esté ordenado (requisito para búsqueda binaria)
    if (!ordenado)
    {
        printf("El arreglo no esta ordenado. Ordene los contenedores antes de buscar.\n");
        return;  // Sale si el arreglo no está ordenado
    }

    // Lee el peso a buscar del usuario
    int valor = leerEntero("Ingrese el peso a buscar: ", 0, 1000000);
    // Ejecuta la búsqueda binaria
    int posicion = busquedaBinaria(pesos, cantidadContenedores, valor);

    // Verifica si el contenedor fue encontrado
    if (posicion >= 0)
    {
        printf("Contenedor encontrado en la posicion %d (peso = %d).\n", posicion + 1, pesos[posicion]);
    }
    else
    {
        printf("No se encontro ningun contenedor con ese peso.\n");
    }
}

// Función que pausa el programa para que el usuario vea los resultados antes de continuar
void pausar(void)
{
    // Muestra un mensaje indicando que se presione Enter
    printf("\nPresione Enter para continuar...");
    // Espera a que el usuario presione Enter, descartando otros caracteres
    while (getchar() != '\n')
        ;  // Bucle vacío que consume caracteres hasta encontrar Enter
}

