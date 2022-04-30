#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

typedef struct Tarea{
    int TareaID;
    char *Description;
    int Duracion;
}TAREAS;

void cargarTareas(TAREAS **listaDeTareas, int numeroDeTareas);
void verificarTareas(TAREAS **listadoDeTareas, TAREAS **RealizarTareas, int numeroDeTareas);
void mostrarTareas(TAREAS **TareasPendientes, TAREAS **TareasRealizadas, int numeroDeTrareas);
void busquedaPorPalabra(TAREAS **listadoDeTareas, int numeroDeTareas, char *palabraClave);
void busquedaPorId(TAREAS **listadoDeTareas, int numeroDeTareas, int idDeLaTareaBuscada);


int main(){
    srand(time(NULL));
    TAREAS **listadoDeTarea, **tareasARealizar;
    int cantidadDeTareas;

    printf("Ingresar la cantidad de tareas: \n");
    scanf("%d",&cantidadDeTareas);

    listadoDeTarea = (TAREAS **)malloc(cantidadDeTareas*sizeof(TAREAS *));

    cargarTareas(listadoDeTarea,cantidadDeTareas);

    //BUSQUEDA POR PALABRA EN RAMA2
    char *palabraClave, *Buff;
    Buff = (char *)malloc(100*sizeof(char));

    printf("\nIngrese la palabra clave que desea buscar: ");
    fflush(stdin);
    gets(Buff);

    palabraClave = (char *)malloc(strlen(Buff)+1*sizeof(char));
    strcpy(palabraClave, Buff);

    busquedaPorPalabra(listadoDeTarea, cantidadDeTareas, palabraClave);
    free(Buff);
    free(palabraClave);
    //////////////////////////////////////////////////////////////////

    //BUSQUEDA POR ID EN RAMA MASTER
    int idRequerido;

    printf("\nIngrese el id correspondiente de la tarea que desea buscar: ");
    fflush(stdin);
    scanf("%d",&idRequerido);

    busquedaPorId(listadoDeTarea, cantidadDeTareas, idRequerido);
    //////////////////////////////////////////////////////////////////
    
    tareasARealizar = (TAREAS **)malloc(cantidadDeTareas*sizeof(TAREAS *));

    for (int i = 0; i < cantidadDeTareas; i++){
        tareasARealizar[i] = NULL;
    }
    
    verificarTareas(listadoDeTarea, tareasARealizar, cantidadDeTareas);
    mostrarTareas(listadoDeTarea, tareasARealizar, cantidadDeTareas); 
    

    for (int i = 0; i < cantidadDeTareas; i++){
        if (listadoDeTarea[i] !=  NULL){
            free(listadoDeTarea[i]->Description);
        }
        free(listadoDeTarea[i]);
    }

    for (int  i = 0; i < cantidadDeTareas; i++){
        if (tareasARealizar[i] != NULL){
            free(tareasARealizar[i]->Description);
        }
        free(tareasARealizar[i]);
    }
    
    free(listadoDeTarea);
    free(tareasARealizar);

    getchar();
    getchar();
    return 0;
}

void cargarTareas(TAREAS **listaDeTareas, int numeroDeTareas){
    int numeroRandom;
    for (int i = 0; i < numeroDeTareas; i++){

        listaDeTareas[i] = (TAREAS *)malloc(sizeof(TAREAS)*1);

        listaDeTareas[i]->TareaID = i + 1;

        listaDeTareas[i]->Description = (char *)malloc(100*sizeof(char)+1);
        numeroRandom = rand()%3;
        switch (numeroRandom){
        case 0:
            strcpy(listaDeTareas[i]->Description,"Reclutar nuevos profesionales");
            break;
        case 1:
            strcpy(listaDeTareas[i]->Description,"Mantenimiento de maquinas industriales");
            break;
        case 2:
            strcpy(listaDeTareas[i]->Description,"Conexion de luz en la industria");
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

void busquedaPorPalabra(TAREAS **listadoDeTareas, int numeroDeTareas, char *palabraClave){
    for (int i = 0; i < numeroDeTareas; i++){
        if (strstr(listadoDeTareas[i]->Description, palabraClave) != NULL){
            printf("\n------ TAREA ENCONTRADA ------");
            printf("\nID de la tarea: %d",listadoDeTareas[i]->TareaID);
            printf("\nDescripcion de la tarea: %s",listadoDeTareas[i]->Description);
            printf("\nDuracion de la tarea: %d Horas\n",listadoDeTareas[i]->Duracion);
            return;
        } 
    }
    printf("\nNo se encontro ninguna tarea relacionada con la palabra que usted introdujo\n");
}

void busquedaPorId(TAREAS **listadoDeTareas, int numeroDeTareas, int idDeLaTareaBuscada){
    for (int i = 0; i < numeroDeTareas; i++){
        if (listadoDeTareas[i]->TareaID == idDeLaTareaBuscada){
            printf("\n------ TAREA ENCONTRADA POR ID --------");
            printf("\nID de la tarea: %d",listadoDeTareas[i]->TareaID);
            printf("\nDescripcion de la tarea: %s",listadoDeTareas[i]->Description);
            printf("\nDuracion de la tarea: %d Horas\n",listadoDeTareas[i]->Duracion);
            return;
        }
    }
    printf("\nNo se encontro ninguna tarea con ese numero de ID\n");
}