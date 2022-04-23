#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct Tarea{
    int TareaID;
    char *Description;
    int Duracion;
}TAREAS;

void cargarTareas(TAREAS **listaDeTareas, int numeroDeTareas);
void verificarTareas(TAREAS **listadoDeTareas, TAREAS **RealizarTareas, int numeroDeTareas);
void mostrarTareas(TAREAS **TareasPendientes, TAREAS **TareasRealizadas, int numeroDeTrareas);

int main(){
    srand(time(NULL));
    TAREAS **listadoDeTarea, **tareasARealizar;
    int cantidadDeTareas;

    printf("Ingresar la cantidad de tareas: \n");
    scanf("%d",&cantidadDeTareas);

    listadoDeTarea = (TAREAS **)malloc(cantidadDeTareas*sizeof(TAREAS *));
    tareasARealizar = (TAREAS **)malloc(cantidadDeTareas*sizeof(TAREAS *));

    cargarTareas(listadoDeTarea,cantidadDeTareas);

    for (int i = 0; i < cantidadDeTareas; i++){
        tareasARealizar[i] = NULL;
    }
    
    verificarTareas(listadoDeTarea, tareasARealizar, cantidadDeTareas);
    mostrarTareas(listadoDeTarea, tareasARealizar, cantidadDeTareas);

    getchar();
    getchar();
    return 0;
}

void cargarTareas(TAREAS **listaDeTareas, int numeroDeTareas){
    int numeroRandom;
    for (int i = 0; i < numeroDeTareas; i++){

        listaDeTareas[i] = (TAREAS *)malloc(sizeof(TAREAS)*1);

        numeroRandom = rand()%numeroDeTareas + 1;
        listaDeTareas[i]->TareaID = numeroRandom;

        listaDeTareas[i]->Description = (char *)malloc(100*sizeof(char)+1);
        numeroRandom = rand()%3;
        switch (numeroRandom){
        case 0:
            strcpy(listaDeTareas[i]->Description,"SOLDAR");
            break;
        case 1:
            strcpy(listaDeTareas[i]->Description,"MANTENIMIENTO");
            break;
        case 2:
            strcpy(listaDeTareas[i]->Description,"ELECTRICIDAD");
            break;
        }

        listaDeTareas[i]->Duracion = rand() % 91 + 10;
    }
}

void verificarTareas(TAREAS **TareasPendientes, TAREAS **RealizarTareas, int numeroDeTareas){
    int auxiliar;
    for (int i = 0; i < numeroDeTareas; i++){
        do
        {
            printf("\nSe realizo esta tarea de %s?(1:Si, 0:No):",TareasPendientes[i]->Description);
            scanf("%d",&auxiliar);
        } while (auxiliar != 1 && auxiliar !=0);
        
        if (auxiliar == 1){
            RealizarTareas[i] = TareasPendientes[i];
            TareasPendientes[i] = NULL;
        }
    }   
}

void mostrarTareas(TAREAS **TareasPendientes, TAREAS **TareasRealizadas, int numeroDeTareas){
    printf("\n====== TAREAS PENDIENTES ======\n");
    for (int i = 0; i < numeroDeTareas; i++){
        if (TareasPendientes[i] != NULL){
            printf("\nID de la tarea: %d",TareasPendientes[i]->TareaID);
            printf("\nTarea a realizar: %s", TareasPendientes[i]->Description);
            printf("\nDuracion de la tarea: %d horas",TareasPendientes[i]->Duracion);
        }
    }
    printf("\n====== TAREAS REALIZADAS ======\n");
    for (int i = 0; i < numeroDeTareas; i++){
        if (TareasRealizadas[i] != NULL){
            printf("\nID de la tarea: %d",TareasRealizadas[i]->TareaID);
            printf("\nTarea a realizar: %s",TareasRealizadas[i]->Description);
            printf("\nDuracion de la tarea: %d horas",TareasRealizadas[i]->Duracion);
        }
    }
}