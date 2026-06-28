#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Definición de estructuras y constantes
#define MAX_SABORES 10
#define MAX_NOMBRE 30
// Estructura para representar un cliente
typedef struct
{
    char nombre[MAX_NOMBRE];
    char sabor[MAX_NOMBRE];
    float litros;
    float total;
} Cliente;
// Estructura para representar un recipiente
typedef struct
{
    char sabor[MAX_NOMBRE];
    float litros;
} Recipiente;

#define MAX_CLIENTES 50

Cliente cola[MAX_CLIENTES];

int cabeza = 0;   // Índice del primer cliente
int final = -1;   // Índice del último cliente

float totalLitrosSabor(const char sabor[]);
void buscarRecipiente(const char sabor[], float litrosSolicitados);

// Agrega un nuevo cliente a la cola
void encolar()
{
    if (final == MAX_CLIENTES - 1)
    {
        printf("La cola esta llena.\n");
        return;
    }

    final++;

    printf("Nombre del cliente: ");
    scanf(" %[^\n]", cola[final].nombre);

    printf("Sabor: ");
    scanf(" %[^\n]", cola[final].sabor);

    printf("Cantidad de litros: ");
    scanf("%f", &cola[final].litros);

     // Precio: 8000 por litro
    cola[final].total = cola[final].litros * 8000;

    printf("Cliente registrado correctamente.\n");
}

// Atiende al primer cliente de la cola
void desencolar()
{
    if (cabeza > final)
    {
        printf("No hay clientes en espera.\n");
        return;
    }

    printf("\n--- ATENDIENDO CLIENTE ---\n");

    float litrosDisponibles = totalLitrosSabor(cola[cabeza].sabor);

    if (litrosDisponibles == 0)
    {
        printf("No hay ese sabor disponible.\n");
        return;
    }

    if (litrosDisponibles < cola[cabeza].litros)
    {
        printf("No hay suficientes litros de ese sabor.\n");
        return;
    }

    // Retira los litros de los recipientes
    buscarRecipiente(cola[cabeza].sabor, cola[cabeza].litros);

    printf("Nombre: %s\n", cola[cabeza].nombre);
    printf("Sabor: %s\n", cola[cabeza].sabor);
    printf("Cantidad: %.2f litros\n", cola[cabeza].litros);
    printf("Total: $%.2f\n", cola[cabeza].total);

    cabeza++;

    printf("Cliente atendido correctamente.\n");
}

Recipiente pila[MAX_SABORES];



int tope = -1;  // Índice del último recipiente

// Agrega un recipiente a la pila
void push()
{
    if (tope == MAX_SABORES - 1)
    {
        printf("La pila esta llena.\n");
        return;
    }

    tope++;

    printf("Nombre del sabor: ");
    scanf(" %[^\n]", pila[tope].sabor);

    printf("Cantidad de litros: ");
    scanf("%f", &pila[tope].litros);

    printf("Recipiente agregado correctamente.\n");
}

// Calcula el total de litros disponibles de un sabor
float totalLitrosSabor(const char sabor[])
{
    float total = 0;
    int i;

    // Suma litros de todos los recipientes con ese sabor
    for (i = 0; i <= tope; i++)
    {
        if (strcmp(pila[i].sabor, sabor) == 0)
        {
            total += pila[i].litros;
        }
    }

    return total;
}

// Busca y retira litros de recipientes (LIFO desde el tope)
void buscarRecipiente(const char sabor[], float litrosSolicitados)
{
    int i = tope;

    // Busca desde el tope hacia abajo
    while (i >= 0 && litrosSolicitados > 0)
    {
        if (strcmp(pila[i].sabor, sabor) == 0)
        {    
            // Si el recipiente tiene más litros que los necesarios
            if (pila[i].litros > litrosSolicitados)
            {
                pila[i].litros -= litrosSolicitados;
                litrosSolicitados = 0;
            }
            else
            {    
                // Si tiene menos, quitar el recipiente completo
                litrosSolicitados -= pila[i].litros;
                // Desplazar elementos hacia arriba
                int j;
                for (j = i; j < tope; j++)
                {
                    pila[j] = pila[j + 1];
                }

                tope--;
                i++;
            }
        }

        i--;
    }
}
// Muestra todos los clientes en espera
void mostrarCola()
{
    int i;

    if (cabeza > final)
    {
        printf("No hay clientes en espera.\n");
        return;
    }

    printf("\n----- CLIENTES EN ESPERA -----\n");

    for (i = cabeza; i <= final; i++)
    {
        printf("Nombre: %s\n", cola[i].nombre);
        printf("Sabor: %s\n", cola[i].sabor);
        printf("Litros: %.2f\n", cola[i].litros);
        printf("Total: $%.2f\n\n", cola[i].total);
    }
}
// Muestra todos los recipientes disponibles
void mostrarPila()
{
    int i;

    if (tope == -1)
    {
        printf("La pila esta vacia.\n");
        return;
    }

    printf("\n------ PILA DE RECIPIENTES ------\n");
    
    // Muestra desde el tope hacia la base (LIFO)
    for (i = tope; i >= 0; i--)
    {
        printf("Sabor: %s\n", pila[i].sabor);
        printf("Litros: %.2f\n\n", pila[i].litros);
    }
}
// Menú principal del sistema
int main()
{
    int opcion;

    do
    {
        printf("\n===== HELADERIA DONA PEPE =====\n");
        printf("1. Registrar recipiente\n");
        printf("2. Mostrar pila\n");
        printf("3. Registrar cliente\n");
        printf("4. Mostrar cola\n");
        printf("5. Atender cliente\n");
        printf("6. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch(opcion)
        {
            case 1:
                push();
                break;

            case 2:
                mostrarPila();
                break;

            case 3:
                encolar();
                break;

            case 4:
                mostrarCola();
                break;

            case 5:
                desencolar();
                break;

            case 6:
                printf("Gracias por utilizar el sistema.\n");
                break;

            default:
                printf("Opcion invalida.\n");
        }

    } while(opcion != 6);
}
