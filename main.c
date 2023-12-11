#include <stdio.h>
#include <stdlib.h>
#define MAX_CONTACTOS 100

///Estructura
typedef struct
{
    char nombre[50];
    int numeroTelefono;
    char ciudad[50];
} contacto;


int main()
{
    contacto contact[MAX_CONTACTOS];
    int opcion;
    int cantidadContactos = 0;

    // Cargar los contactos existentes desde el archivo al inicio
    FILE *archivo = fopen("contactos.bin", "rb");
    if (archivo != NULL)
    {
        while (fread(&contact[cantidadContactos], sizeof(contacto), 1, archivo) == 1)
        {
            cantidadContactos++;
        }
        fclose(archivo);
    }

    do
    {
        limpiarConsola();
        printf("--- GESTION DE CONTACTOS ---\n");
        printf("1. Agregar contacto\n");
        printf("2. Eliminar contacto\n");
        printf("3. Buscar contacto en archivo\n");
        printf("4. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            agregarContacto(contact, &cantidadContactos);
            break;
        case 2:
            eliminarContacto(contact, &cantidadContactos);
            break;
        case 3:
            buscarContacto(contact, cantidadContactos);
            break;
        case 4:
            printf("Saliendo del programa...\n");
            break;
        default:
            printf("Opcion invalida.\n");
        }

        printf("Presione Enter para continuar...\n");
        getchar();
    }
    while (opcion != 4);

    return 0;
}


void limpiarConsola()
{
    system("cls");
}

void agregarContacto(contacto contac[], int* cantidadContactos)
{
    limpiarConsola();
    contacto contactoNuevo;
    if(*cantidadContactos < MAX_CONTACTOS)
    {


        printf("--- AGREGAR CONTACTO ---\n");

        printf("Ingrese el nombre del contacto: ");
        scanf("%s", contactoNuevo.nombre);
        printf("Ingrese el numero de telefono del contacto: ");
        scanf("%i", contactoNuevo.numeroTelefono);
        printf("Ingrese la ciudad del contacto: ");
        scanf("%s", contactoNuevo.ciudad);

        contac[*cantidadContactos]=contactoNuevo;
        (*cantidadContactos)++;
        printf("Contacto agregado correctamente.");
    }
    else
    {
        printf("No se pueden agregar mas contactos.");
    }

    FILE* archivo = fopen("contactos.bin", "ab");

    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    for (int i = 0; i < *cantidadContactos; i++)
    {
        fwrite(&contac[i], sizeof(contacto), 1, archivo);
    }


    fclose(archivo);

}

void eliminarContacto(contacto contac[], int* cantidadContactos)
{
    limpiarConsola();
    char nombreBuscado[50];
    printf("--- ELIMINAR CONTACTO ---\n");
    printf("Ingrese el nombre del contacto que desea eliminar: ");
    scanf("%s", nombreBuscado);

    int indiceEncontrado = -1;

    for (int i = 0; i < *cantidadContactos; i++)
    {
        if (strcmp(contac[i].nombre, nombreBuscado) == 0)
        {
            indiceEncontrado = i;
            break;
        }
    }

    if (indiceEncontrado != -1)
    {
        // Eliminamos el contacto moviendo los elementos siguientes una posicion hacia atras
        for (int i = indiceEncontrado; i < *cantidadContactos - 1; i++)
        {
            contac[i] = contac[i + 1];
        }
        (*cantidadContactos)--;
        printf("Contacto eliminado correctamente.\n");

        // Abre el archivo en modo "wb" para sobrescribir
        FILE* archivo = fopen("contactos.bin", "wb");
        if (archivo == NULL)
        {
            printf("No se pudo abrir el archivo.\n");
            return;
        }

        // Vuelve a escribir todos los contactos en el archivo
        for (int i = 0; i < *cantidadContactos; i++)
        {
            fwrite(&contac[i], sizeof(contacto), 1, archivo);
        }

        fclose(archivo);
    }
    else
    {
        printf("Contacto no encontrado.\n");
    }
    getchar();
}


void buscarContacto(contacto contac[], int cantidadContactos)
{
    limpiarConsola();
    char consulta[50];
    printf("--- BUSCAR CONTACTO ---\n");
    printf("Ingrese el nombre o numero de telefono del contacto que desea buscar: ");
    scanf("%s", consulta);

    int encontrado = 0;

    for (int i = 0; i < cantidadContactos; i++)
    {
        if (strcmp(contac[i].nombre, consulta) == 0 || contac[i].numeroTelefono == atoi(consulta))
        {
            printf("Contacto encontrado:\n");
            printf("Nombre: %s\n", contac[i].nombre);
            printf("Numero de telefono: %d\n", contac[i].numeroTelefono);
            printf("Ciudad: %s\n\n", contac[i].ciudad);
            encontrado = 1;
        }
    }

    if (!encontrado)
    {
        printf("Contacto no encontrado.\n");
    }
    getchar();
}


