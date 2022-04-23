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

int main(){
    TAREAS **listadoDeTarea, **tareasARealizar;
    int cantidadDeTareas;

    printf("Ingresar la cantidad de tareas: \n");
    scanf("%d",&cantidadDeTareas);

    listadoDeTarea = (TAREAS **)malloc(cantidadDeTareas*sizeof(TAREAS));
    tareasARealizar = (TAREAS **)malloc(cantidadDeTareas*sizeof(TAREAS));

    cargarTareas(listadoDeTarea,cantidadDeTareas);
    verificarTareas(listadoDeTarea, tareasARealizar, cantidadDeTareas);

    getchar();
    getchar();
    return 0;
}

void cargarTareas(TAREAS **listaDeTareas, int numeroDeTareas){
    int numeroRandom;
    for (int i = 0; i < numeroDeTareas; i++){

        listaDeTareas[i] = (TAREAS *)malloc(sizeof(TAREAS));

        numeroRandom = rand()%numeroDeTareas + 1;
        listaDeTareas[i]->TareaID = numeroRandom;

        listaDeTareas[i]->Description = (char *)malloc(100*sizeof(char));
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

        free(listaDeTareas[i]->Description);
    }
}

void verificarTareas(TAREAS **TareasPendientes, TAREAS **RealizarTareas, int numeroDeTareas){
    int auxiliar;
    for (int i = 0; i < numeroDeTareas; i++){
        RealizarTareas[i] = (TAREAS *)malloc(sizeof(TAREAS));

        printf("\n------ Tarea numero %d - %s - Duracion: %d ------",TareasPendientes[i]->TareaID, TareasPendientes[i]->Description, TareasPendientes[i]->Duracion);

        do
        {
            printf("\n¿Se realizo esta tarea?(1:Si, 0:No):");
            scanf("%d",&auxiliar);
        } while (auxiliar != 1 && auxiliar !=0);
        
        if (auxiliar == 1){
            RealizarTareas[i] = TareasPendientes[i];
            TareasPendientes[i] = NULL;
        }   
    }   
}

