#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define TAMA 100

struct Tarea {
    int TareaID; //Numerico autoincremental comenzando en 1000
    char *Descripcion; //Descripcion
    int Duracion;// entre 10 - 100
};

struct Nodo {
    struct Tarea T;
    struct Nodo * Siguiente;
  
};

struct Nodo *crearListaVacia();
struct Nodo *crearNodo(int id, char* Descripcion,int duracion);
void insertarNodo (struct Nodo **start, struct Nodo *nuevoNodo);
struct Nodo *buscarNodo (struct Nodo  **start, int idBuscado);
void mostarTareas(struct Nodo **start);
void eliminarNodo(struct Nodo **Start, int idBuscado);
void buscarPorId(struct Nodo * listaPendientes,struct Nodo * listaRealizados,int idBuscado );
void buscarPorPalabra(struct Nodo * listaPendientes,struct Nodo * listaRealizados,char palabra[TAMA] );
int main (){
    int opcion ,id=1000,Duracion , idBuscado;
    struct Nodo * listaPendientes = crearListaVacia();
    struct Nodo * listaRealizados = crearListaVacia();
    char Descripcion[TAMA];
    char palabra[TAMA];
    int stop=1;
    do
    {
        puts("######################################");
        puts("0 - Salir");
        puts("1 - Ingresar Tarea pendiente");
        puts("2- Mostrar lista de Pendientes");
        puts("3- Mostrar lista de Realizadas");
        puts("4- Marcar tareas pendentes como realizadas");
        puts("5- Buscar tarea por id");
        puts("6- Buscar tarea por palara clave");
        puts("######################################");
        do
        {
            scanf("%d",&opcion);
            fflush(stdin);
        } while (opcion<0 || opcion>6);

        switch (opcion)
        {
        case 1:
            do
            {
                
                printf("-----------CARGAR TAREA-----------\n");
                printf("Ingrese la descripcion de la tarea: ");
                gets(Descripcion);
                fflush(stdin);
                srand(time(NULL));
                Duracion=rand() %91 + 10;
                insertarNodo(&listaPendientes,crearNodo(id,Descripcion,Duracion));
                id++;
                printf("\nAnadir otra tarea (1-Si|0-No) ");
                scanf("%d",&stop);
                fflush(stdin);
                
            } while (stop!=0);
            break;
        case 2:
            puts("--------LISTA Pendientes--------");
            mostarTareas(&listaPendientes);
            puts("--------------------------------");
            printf("\n");
            break;
        case 3:
            puts("--------LISTA REALIZADOS--------");
            mostarTareas(&listaRealizados);
            puts("--------------------------------");
            printf("\n");
            break;
        case 4:
            
            printf("\nIngresar el id de la tarea que quiere marcar como Realizada: ");
            fflush(stdin);
            scanf("%d",&idBuscado);

            struct Nodo *aux = listaPendientes;

            while (aux != NULL && aux->T.TareaID!=idBuscado) 
            {
                aux = aux->Siguiente;
            }
            struct Nodo *insertar;
            insertar = crearNodo(aux->T.TareaID, aux->T.Descripcion,aux->T.Duracion);
            insertarNodo (&listaRealizados, insertar);
            eliminarNodo(&listaPendientes,idBuscado);
            break;
        case 5:
            
            printf("Ingrese el id de la tarea: ");
            scanf("%d",&idBuscado);
            printf("\n");
            buscarPorId(listaPendientes,listaRealizados,idBuscado);
            break;
        case 6:
            fflush(stdin);
            printf("Ingrese la palabra: ");
            gets(palabra);
            fflush(stdin);
            printf("\n");
            buscarPorPalabra(listaPendientes,listaRealizados,palabra);
            break;
        }
        

    } while (opcion!=0);
    
    
    
    return 0;
}

struct Nodo *crearListaVacia(){
    return NULL;
}

struct Nodo *crearNodo(int id, char* Descripcion,int duracion){
    struct Nodo *NNodo = (struct Nodo *)malloc(sizeof(struct Nodo));
    NNodo->T.TareaID = id;
    NNodo->T.Descripcion = (char*) malloc(sizeof(char)*TAMA);
    strcpy(NNodo->T.Descripcion, Descripcion);
    NNodo->T.Duracion = duracion;
    NNodo->Siguiente=NULL;
    return NNodo;
}

void insertarNodo (struct Nodo **start, struct Nodo *nuevoNodo){
    nuevoNodo->Siguiente = *start;
    *start = nuevoNodo;
}

void mostarTareas(struct Nodo **start){
    struct Nodo * aux = *start; 
    while (aux != NULL)
    {   
        puts("---Tarea---");
        printf("Id: %d \n", aux->T.TareaID);
        puts("Descripcion:");
        puts(aux->T.Descripcion);
        printf("Duracion de la tarea: %d\n", aux->T.Duracion);

        aux = aux->Siguiente;
    }
}

struct Nodo *buscarNodo (struct Nodo  **start, int idBuscado){
    struct Nodo * aux = *start;
    while (aux!=NULL && aux->T.TareaID!=idBuscado)
    {
        aux = aux ->Siguiente;
    }
    
    return aux;
}

void eliminarNodo(struct Nodo **Start, int idBuscado){
    struct Nodo **aux = Start;

    while (*aux!=NULL && (*aux)->T.TareaID!=idBuscado)
    {
        aux = &(*aux)->Siguiente;
    }
    if (*aux)
    {
        struct Nodo *temp = *aux;
        *aux = (*aux)->Siguiente;
        free(temp);
    }
}

void buscarPorId(struct Nodo * listaPendientes,struct Nodo * listaRealizados,int idBuscado ){
    struct Nodo * aux1 = listaPendientes;
    struct Nodo * aux2 = listaRealizados;
    int bandera = 0;
    while (aux1!=NULL && bandera==0)
    {
        if (aux1->T.TareaID==idBuscado)
        {
        puts("---Tarea---");
        printf("Id: %d \n", aux1->T.TareaID);
        puts("Descripcion:");
        puts(aux1->T.Descripcion);
        printf("Duracion de la tarea: %d\n", aux1->T.Duracion);
        puts("Tarea encontrada en lista de Pendientes");
        bandera=1;
        }else{
            aux1 = aux1->Siguiente;
        }
    }
    if (bandera==0)
    {
        while (aux2!=NULL && bandera==0)
        {
            if (aux2->T.TareaID==idBuscado){
            puts("---Tarea---");
            printf("Id: %d \n", aux2->T.TareaID);
            puts("Descripcion:");
            puts(aux2->T.Descripcion);
            printf("Duracion de la tarea: %d\n", aux2->T.Duracion);
            puts("Tarea encontrada en Lista Realizados");
            bandera=1;
            }else{
                aux2 = aux2->Siguiente;
            }
        }
    }
    if (bandera==0)
    {
        puts("La tarea no se encuentra en ninguna lista");
    }
    
    
}

void buscarPorPalabra(struct Nodo * listaPendientes,struct Nodo * listaRealizados,char palabra[TAMA] ){
    struct Nodo * aux1 = listaPendientes;
    struct Nodo * aux2 = listaRealizados;
    int bandera = 0;
    while (aux1!=NULL && bandera==0)
    {
        if (strstr(aux1->T.Descripcion, palabra))
        {
            puts("---Tarea---");
            printf("Id: %d \n", aux1->T.TareaID);
            puts("Descripcion:");
            puts(aux1->T.Descripcion);
            printf("Duracion de la tarea: %d\n", aux1->T.Duracion);
            puts("Tarea encontrada en Lista Pendientes");
            bandera=1;
        }
        aux1 = aux1->Siguiente;
    }
    if (bandera==0)
    {
        while (aux2!=NULL && bandera==0)
        {
            if (strstr(aux2->T.Descripcion, palabra))
            {
                puts("---Tarea---");
                printf("Id: %d \n", aux2->T.TareaID);
                puts("Descripcion:");
                puts(aux2->T.Descripcion);
                printf("Duracion de la tarea: %d\n", aux2->T.Duracion);
                puts("Tarea encontrada en Lista Realizados");
                bandera=1;
            }
            aux2 = aux2->Siguiente;
        }
    }
    if (bandera == 0)
    {
        puts("La tarea no se encuentra en ninguna lista");
    }
    
}