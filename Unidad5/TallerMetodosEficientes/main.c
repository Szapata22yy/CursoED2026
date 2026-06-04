/*
Unidad 5 - Taller Metodos Eficientes
Autores: Sebastian Zapata cuartas, Diego alberti lopez , miguel castrillon
 */

// libreria para entrada/salida (printf, scanf)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// constante que define el numero maximo de contenedores que se pueden registrar
#define MAX_CONTENEDORES 30

// array que almacena los pesos de los contenedores
int pesos[MAX_CONTENEDORES];
// bandera que indica si el arreglo esta ordenado (1) o no (0)
int ordenado = 0;
// variable que almacena la cantidad actual de contenedores registrados
int cantidadContenedores = 0;

void mostrarMenu(void);
int leerEntero(const char *mensaje, int minimo, int maximo);
void registrarPesosManual(void);
void generarPesosAleatorios(void);
void mostrarContenedores(void);
void swap(int *a, int *b);
int partition(int arr[], int low, int high);
void quickSort(int arr[], int low, int high);
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
    // inicializa la semilla aleatoria usando el tiempo actual del sistema
    srand((unsigned int)time(NULL));

    // bucle principal del programa que se ejecuta hasta que el usuario seleccione salir
    do
    {
        // muestra el menu de opciones
        mostrarMenu();
        // lee la opcion seleccionada por el usuario
        opcion = leerEntero("", 1, 8);

        // switch que ejecuta la accion correspondiente segun la opcion seleccionada
        switch (opcion)
        {
            // opcion 1: registrar pesos manualmente
            case 1:
                registrarPesosManual();
                break;
            // opcion 2: generar pesos aleatorios y mostrar contenedores
            case 2:
                generarPesosAleatorios();
                break;
            // opcion 3: mostrar los contenedores registrados
            case 3:
                mostrarContenedores();
                break;
            // opcion 4: ordenar usando bubble sort
            case 4:
                ordenarMetodo1();
                mostrarContenedores();
                break;
            // opcion 5: ordenar usando merge sort
            case 5:
                ordenarMetodo2();
                mostrarContenedores();
                break;
            // opcion 6: ordenar usando heap sort
            case 6:
                ordenarMetodo3();
                mostrarContenedores();
                break;
            // opcion 7: buscar un contenedor usando busqueda binaria
            case 7:
                buscarContenedor();
                break;
            // opcion 8: salir del programa
            case 8:
                printf("Saliendo del programa...\n");
                break;
            // opcion invalida: mostrar mensaje de error
            default:
                printf("Opcion invalida. Intente de nuevo.\n");
        }

        // si no es salir, pausa el programa para que el usuario vea los resultados
        if (opcion != 8)
        {
            pausar();
        }
    } while (opcion != 8);  // continua hasta que el usuario seleccione salir

    return 0;  // fin del programa
}

// funcion que muestra el menu principal del programa
void mostrarMenu(void)
{
    // imprime el titulo y opciones del menu
    printf("\n========================================\n");
    printf("\nsistema de organizacion de contenedores\n");
    printf("\nmuelle de carga\n");
    printf("\n========================================\n");
    printf("1. registrar peso de contenedores manualmente\n");
    printf("2. generar pesos aleatorios de contenedores\n");
    printf("3. mostrar contenedores registrados\n");
    printf("4. ordenar contenedores metodo 1\n");
    printf("5. ordenar contenedores metodo 2\n");
    printf("6. ordenar contenedores metodo 3\n");
    printf("7. buscar contenedor\n");
    printf("8. salir\n");
    printf("========================================\n");
    printf("seleccione una opcion\n");
}

// funcion que lee un entero del usuario dentro de un rango especificado
// parametros: mensaje (texto a mostrar), minimo y maximo (rango valido)
int leerEntero(const char *mensaje, int minimo, int maximo)
{
    int valor;  // variable para almacenar el valor ingresado
    int resultado;  // variable para verificar si scanf tuvo exito

    // bucle que se repite hasta obtener un valor valido
    do
    {
        // muestra el mensaje solicitando entrada
        printf("%s", mensaje);
        // intenta leer un entero del usuario
        resultado = scanf("%d", &valor);
        // limpia el buffer de entrada para evitar problemas con lecturas posteriores
        while (getchar() != '\n');

        // valida que la lectura fue exitosa y que el valor esta dentro del rango
        if (resultado != 1 || valor < minimo || valor > maximo)
        {
            // muestra un error si la entrada es invalida
            printf("entrada invalida. ingrese un numero entre %d y %d.\n", minimo, maximo);
        }
        else
        {
            // sale del bucle si la entrada es valida
            break;
        }
    } while (1);  // continua hasta obtener una entrada valida

    return valor;  // retorna el valor valido ingresado
}

// funcion que permite al usuario registrar manualmente los pesos de los contenedores
void registrarPesosManual(void)
{
    // lee la cantidad de contenedores a registrar
    int cantidad = leerEntero("ingrese la cantidad de contenedores a registrar (1-30): ", 1, MAX_CONTENEDORES);

    // bucle que itera sobre cada contenedor para leer su peso
    for (int i = 0; i < cantidad; i++)
    {
        char mensaje[80];  // buffer para construir el mensaje
        // construye un mensaje personalizado para cada contenedor
        sprintf(mensaje, "peso del contenedor %d: ", i + 1);
        // lee y almacena el peso del contenedor
        pesos[i] = leerEntero(mensaje, 0, 1000000);
    }

    // actualiza las variables globales
    cantidadContenedores = cantidad;  // registra la cantidad de contenedores
    ordenado = 0;  // marca que el arreglo no esta ordenado
    printf("contenedores registrados correctamente.\n");
    printf("\ncontenedores registrados:\n");
    // muestra los contenedores registrados
    for (int i = 0; i < cantidad; i++)
    {
        printf("#%d = %dkg\n", i + 1, pesos[i]);
    }
}

// funcion que genera pesos aleatorios para los contenedores
void generarPesosAleatorios(void)
{
    // lee la cantidad de contenedores a generar
    int cantidad = leerEntero("ingrese la cantidad de contenedores a generar (1-30): ", 1, MAX_CONTENEDORES);

    // bucle que genera pesos aleatorios para cada contenedor
    for (int i = 0; i < cantidad; i++)
    {
        // genera un numero aleatorio entre 0 y 1000 kg
        pesos[i] = rand() % 1001;
    }

    // actualiza las variables globales
    cantidadContenedores = cantidad;  // registra la cantidad de contenedores
    ordenado = 0;  // marca que el arreglo no esta ordenado
    printf("pesos aleatorios generados correctamente.\n");
    printf("\ncontenedores generados:\n");
    // muestra los contenedores generados
    for (int i = 0; i < cantidad; i++)
    {
        printf("#%d = %dkg\n", i + 1, pesos[i]);
    }
}

// funcion que muestra todos los contenedores registrados actualmente
void mostrarContenedores(void)
{
    // verifica si hay contenedores registrados
    if (cantidadContenedores == 0)
    {
        printf("no hay contenedores registrados.\n");
        return;  // sale de la funcion si no hay contenedores
    }

    // muestra el titulo con la cantidad de contenedores
    printf("\ncontenedores (cantidad = %d):\n", cantidadContenedores);
    // itera sobre todos los contenedores y los muestra
    for (int i = 0; i < cantidadContenedores; i++)
    {
        printf("#%d = %dkg\n", i + 1, pesos[i]);
    }
}

// funcion para intercambiar dos elementos
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// funcion particion: coloca el pivote en su posicion correcta
int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    // elegimos el ultimo elemento como pivote
    int i = low;
    for (int j = low; j < high; j++)
    {
        if (arr[j] < pivot)
        {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[high]);
    return i;
}

// funcion recursiva de quicksort
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int p = partition(arr, low, high);
        quickSort(arr, low, p - 1);
        quickSort(arr, p + 1, high);
    }
}

// funcion auxiliar que fusiona dos subarreglos ordenados para el merge sort
// parametros: arr (arreglo), left (inicio), mid (punto medio), right (fin)
void merge(int arr[], int left, int mid, int right)
{
    // calcula el tamaño de los dos subarreglos
    int n1 = mid - left + 1;  // tamaño del subarreglo izquierdo
    int n2 = right - mid;  // tamaño del subarreglo derecho
    // arrays temporales para almacenar los subarreglos
    int L[MAX_CONTENEDORES];
    int R[MAX_CONTENEDORES];

    // copia datos al subarreglo izquierdo
    for (int i = 0; i < n1; i++)
    {
        L[i] = arr[left + i];
    }
    // copia datos al subarreglo derecho
    for (int j = 0; j < n2; j++)
    {
        R[j] = arr[mid + 1 + j];
    }

    // inicializa indices para los subarreglos y el arreglo principal
    int i = 0;  // indice para l
    int j = 0;  // indice para r
    int k = left;  // indice para arr

    // fusiona los dos subarreglos comparando elementos
    while (i < n1 && j < n2)
    {
        // inserta el elemento menor en el arreglo principal
        if (L[i] <= R[j])
        {
            arr[k++] = L[i++];
        }
        else
        {
            arr[k++] = R[j++];
        }
    }

    // copia los elementos restantes de l, si los hay
    while (i < n1)
    {
        arr[k++] = L[i++];
    }

    // copia los elementos restantes de r, si los hay
    while (j < n2)
    {
        arr[k++] = R[j++];
    }
}

// funcion que implementa el algoritmo mergesort
// parametros: arr (arreglo), left (indice izquierdo), right (indice derecho)
void mergeSort(int arr[], int left, int right)
{
    // condicion base: si hay mas de un elemento
    if (left < right)
    {
        // calcula el punto medio del arreglo
        int mid = (left + right) / 2;
        // ordena recursivamente la mitad izquierda
        mergeSort(arr, left, mid);
        // ordena recursivamente la mitad derecha
        mergeSort(arr, mid + 1, right);
        // fusiona las dos mitades ordenadas
        merge(arr, left, mid, right);
    }
}

// funcion auxiliar que mantiene la propiedad de monticulo (heap) para el heap sort
// parametros: arr (arreglo), n (tamaño), i (indice del nodo actual)
void heapify(int arr[], int n, int i)
{
    // asume que el nodo actual es el mas grande
    int largest = i;
    // calcula los indices de los hijos izquierdo y derecho
    int left = 2 * i + 1;  // hijo izquierdo
    int right = 2 * i + 2;  // hijo derecho

    // si el hijo izquierdo es mayor que el nodo actual, actualiza largest
    if (left < n && arr[left] > arr[largest])
    {
        largest = left;
    }
    // si el hijo derecho es mayor que el nodo actual, actualiza largest
    if (right < n && arr[right] > arr[largest])
    {
        largest = right;
    }
    // si largest cambio, intercambia y hace heapify recursivamente
    if (largest != i)
    {
        // intercambia los elementos
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        // llama heapify recursivamente en el subarbol afectado
        heapify(arr, n, largest);
    }
}

// funcion que implementa el algoritmo heap sort (ordenamiento por monticulo)
// parametro: arr (arreglo a ordenar), n (tamaño del arreglo)
void heapSort(int arr[], int n)
{
    // primer paso: construir el monticulo (heap) maximo
    // itera desde el ultimo nodo no-hoja hasta la raiz
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(arr, n, i);
    }

    // segundo paso: extraer elementos uno por uno del monticulo
    for (int i = n - 1; i > 0; i--)
    {
        // intercambia la raiz (elemento maximo) con el ultimo elemento
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        // hace heapify en el arbol reducido
        heapify(arr, i, 0);
    }
}

// funcion que ordena los contenedores usando el metodo 1 (quick sort)
void ordenarMetodo1(void)
{
    // verifica si hay contenedores registrados
    if (cantidadContenedores == 0)
    {
        printf("no hay contenedores para ordenar.\n");
        return;  // sale si no hay contenedores
    }

    // llama a quicksort para ordenar los contenedores
    quickSort(pesos, 0, cantidadContenedores - 1);
    // marca que el arreglo esta ordenado
    ordenado = 1;
    printf("contenedores ordenados correctamente con el metodo 1 (quick sort).\n");
}

// funcion que ordena los contenedores usando el metodo 2 (merge sort)
void ordenarMetodo2(void)
{
    // verifica si hay contenedores registrados
    if (cantidadContenedores == 0)
    {
        printf("no hay contenedores para ordenar.\n");
        return;  // sale si no hay contenedores
    }

    // llama a mergesort para ordenar los contenedores
    mergeSort(pesos, 0, cantidadContenedores - 1);
    // marca que el arreglo esta ordenado
    ordenado = 1;
    printf("contenedores ordenados correctamente con el metodo 2 (merge sort).\n");
}

// funcion que ordena los contenedores usando el metodo 3 (heap sort)
void ordenarMetodo3(void)
{
    // verifica si hay contenedores registrados
    if (cantidadContenedores == 0)
    {
        printf("no hay contenedores para ordenar.\n");
        return;  // sale si no hay contenedores
    }

    // llama a heapsort para ordenar los contenedores
    heapSort(pesos, cantidadContenedores);
    // marca que el arreglo esta ordenado
    ordenado = 1;
    printf("contenedores ordenados correctamente con el metodo 3 (heap sort).\n");
}

// funcion que implementa la busqueda binaria en un arreglo ordenado
// parametros: arr (arreglo ordenado), n (tamaño), valor (elemento a buscar)
// retorna: indice del elemento si se encuentra, -1 si no se encuentra
int busquedaBinaria(int arr[], int n, int valor)
{
    int inicio = 0;
    int fin = n - 1;
    while (inicio <= fin)
    {
        int medio = (inicio + fin) / 2;
        if (arr[medio] == valor)
        {
            return medio; // elemento encontrado
        }
        else if (arr[medio] < valor)
        {
            inicio = medio + 1;
        }
        else
        {
            fin = medio - 1;
        }
    }
    return -1; // no encontrado
}

// funcion que busca un contenedor por su peso usando busqueda binaria
void buscarContenedor(void)
{
    // Verifica si hay contenedores registrados
    if (cantidadContenedores == 0)
    {
        printf("no hay contenedores registrados para buscar.\n");
        return;  // sale si no hay contenedores
    }

    // verifica que el arreglo este ordenado (requisito para busqueda binaria)
    if (!ordenado)
    {
        printf("el arreglo no esta ordenado. ordene los contenedores antes de buscar.\n");
        return;  // sale si el arreglo no esta ordenado
    }

    // lee el peso a buscar del usuario
    int valor = leerEntero("ingrese el peso a buscar: ", 0, 1000000);
    // ejecuta la busqueda binaria
    int posicion = busquedaBinaria(pesos, cantidadContenedores, valor);

    // verifica si el contenedor fue encontrado
    if (posicion >= 0)
    {
        printf("contenedor encontrado en la posicion %d (peso = %d).\n", posicion + 1, pesos[posicion]);
    }
    else
    {
        printf("no se encontro ningun contenedor con ese peso.\n");
    }
}

// funcion que pausa el programa para que el usuario vea los resultados antes de continuar
void pausar(void)
{
    // muestra un mensaje indicando que se presione enter
    printf("\npresione enter para continuar...");
    // espera a que el usuario presione enter, descartando otros caracteres
    while (getchar() != '\n')
        ;  // bucle vacio que consume caracteres hasta encontrar enter
}

