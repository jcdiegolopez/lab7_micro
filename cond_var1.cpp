/*---------------------------------------
* UNIVERSIDAD DEL VALLE DE GUATEMALA
* Sistemas Operativos
* Autor: Andrés Mondragón Contreras
* Mod.: KB
* Ver.: 1.01
* Fecha: 2023/08/29
*
* References:
* ------
* "Sincronización: Mutex, Variables condición y Semáforos."  
* Universidad Nacional Autonoma de Mexico
* Facultad de Ingenieria
* "Laboratorio Intel para la academia"
* ---------------------------------------
* Variables de condición p/acceder a 
* region crítica 
* variables de condición.
*----------------------------------------
*/

#include <stdio.h>
#include <pthread.h>

pthread_mutex_t candado;
pthread_cond_t cond;

void *menos(void *arg)
{
	int i;
	int *x = (int *)arg;
	for (i = 0; i < 9; i++) {
		pthread_mutex_lock(&candado);				//  -1 -2 -3 -4 -5 -6 -7 -8 -9 -8 -7 -6 -5 ... 0
													//  1 2 3 4 5 6 7 8 9 8 7 6 5 4 ...0
		*x = *x - 1;
		printf("%3d", *x);
		pthread_mutex_unlock(&candado);			// despierta al hilo que está esperando
	}
	pthread_cond_signal(&cond);
	return NULL;
}


void *mas(void *arg)
{
	int i;
	int *x = (int *)arg;
	pthread_mutex_lock(&candado);
	if (*x == 0)
		pthread_cond_wait(&cond, &candado);			//AQUÍ// bloquea al hilo que la llama hasta que la señal signal se habilita sobre cond
	for (i = 0; i < 5; i++) {
	*x = *x + 1;
	printf("%5d", *x);
	}
	
	pthread_mutex_unlock(&candado);
	return NULL;
}

int main()
{
	pthread_t hilo_mas, hilo_menos;
	int x = 0;
	
	pthread_mutex_init(&candado, NULL);
	pthread_cond_init(&cond, NULL);
	
	pthread_create(&hilo_mas, NULL, mas, (void *)&x);
	pthread_create(&hilo_menos, NULL, menos, (void *)&x);

	pthread_join(hilo_mas, NULL);
	pthread_join(hilo_menos, NULL);
	printf("\n");
	
	
	pthread_cond_destroy (&cond);

}

