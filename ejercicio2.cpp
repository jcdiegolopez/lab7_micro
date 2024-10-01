//Correr programa en CMD
//g++ -o ejercicio2 ejercicio2.cpp -pthread

#include <stdio.h>
#include <pthread.h>
#include <unistd.h> 

pthread_mutex_t mutex; 
int silo = 0;           
int bodega = 0;        

// Función para la Tostadora 1
void* tostadora1(void* args) {
    for (int i = 0; i < 200; i++) {  
        sleep(1);  
        pthread_mutex_lock(&mutex);
        silo++;  
        printf("Tostadora 1 produjo: 1 lb de cafe tostada\n");
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

// Función para la Tostadora 2
void* tostadora2(void* args) {
    for (int i = 0; i < 200; i++) {  
        sleep(1); //Condicion de usar sleep
        pthread_mutex_lock(&mutex);
        silo++;  
        printf("Tostadora 2 produjo: 1 lb de cafe tostada\n");
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

// Función para la Empacadora
void* empacadora(void* args) {
    while (bodega < 400) {  
        sleep(1); //Condicion de usar sleep
        pthread_mutex_lock(&mutex);
        if (silo >= 5) {  
            silo--;      
            bodega++;    
            printf("\nEmpacadora produjo: 1 bolsa de 1 lb de cafe\n");
            printf("Lbs de cafe en silo: %d\n", silo);
            printf("Lbs de cafe en bodega: %d\n", bodega);
        }
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t hilo_tostadora1, hilo_tostadora2, hilo_empacadora;

    // Inicializar el mutex
    pthread_mutex_init(&mutex, NULL);

    //Condicion de crear un hilo por maquina
    pthread_create(&hilo_tostadora1, NULL, tostadora1, NULL);
    pthread_create(&hilo_tostadora2, NULL, tostadora2, NULL);
    pthread_create(&hilo_empacadora, NULL, empacadora, NULL);

    //Esperar a que los demas hilos terminen 
    pthread_join(hilo_tostadora1, NULL);
    pthread_join(hilo_tostadora2, NULL);
    pthread_join(hilo_empacadora, NULL);

    // Destruir el mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}
