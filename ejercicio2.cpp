//Correr programa en CMD
//g++ -o ejercicio2 ejercicio2.cpp -pthread

#include <stdio.h>
#include <pthread.h>
#include <unistd.h> 

pthread_mutex_t mutex; 
pthread_cond_t cond_var; 
int silo = 0;           
int bodega = 0;        

// Funcion para la Tostadora 1
void* tostadora1(void* args) {
    for (int i = 0; i < 200; i++) {  
        sleep(1);  
        pthread_mutex_lock(&mutex);
        silo++;  
        printf("Tostadora 1 produjo: 1 lb de cafe tostada\n");
        pthread_cond_broadcast(&cond_var); 
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

// Funcion para la Tostadora 2
void* tostadora2(void* args) {
    for (int i = 0; i < 200; i++) {  
        sleep(1); // Condicion de usar sleep
        pthread_mutex_lock(&mutex);
        silo++;  
        printf("Tostadora 2 produjo: 1 lb de cafe tostada\n");
        pthread_cond_broadcast(&cond_var); 
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

// Funcion para la Empacadora
void* empacadora(void* args) {

    // Esperar hasta que haya al menos 5 lb en el silo inicialmente
    pthread_mutex_lock(&mutex);
    while (silo < 5) {
        pthread_cond_wait(&cond_var, &mutex); 
    }
    pthread_mutex_unlock(&mutex);
    
    while (bodega < 400) {  
        sleep(1); // Condicion de usar sleep
        pthread_mutex_lock(&mutex);

        // Empacar el cafe
        if (silo > 0) {
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

    // Inicializar el mutex y la variable de condición
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_var, NULL);

    // Crear hilos por máquina
    pthread_create(&hilo_tostadora1, NULL, tostadora1, NULL);
    pthread_create(&hilo_tostadora2, NULL, tostadora2, NULL);
    pthread_create(&hilo_empacadora, NULL, empacadora, NULL);

    // Esperar a que los demás hilos terminen 
    pthread_join(hilo_tostadora1, NULL);
    pthread_join(hilo_tostadora2, NULL);
    pthread_join(hilo_empacadora, NULL);

    // Destruir el mutex y la variable de condición
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_var);

    return 0;
}
