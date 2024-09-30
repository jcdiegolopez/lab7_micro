#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

pthread_mutex_t candado;
double montoTotalVentas = 0.0;
double utilidadTotalMes = 0.0;

struct Comida {
    char nombre[30];
    double precio;
    double costo;
    double ventas;
};

void *calcularCostoVentas(void *arg) {
    struct Comida *comida = (struct Comida *)arg;
    

    double montoVentasProducto = comida->ventas * comida->precio;
    double utilidadProducto = montoVentasProducto - (comida->ventas * comida->costo);
    

    pthread_mutex_lock(&candado);
    
    montoTotalVentas += montoVentasProducto;
    utilidadTotalMes += utilidadProducto;
    
    pthread_mutex_unlock(&candado);
    
    printf("Producto: %s\n  Ventas: %.2f\n  Utilidad: %.2f\n", comida->nombre, montoVentasProducto, utilidadProducto);
    
    return NULL;
}

void procesarVentasMes(struct Comida ventas[], int numElementos, const char *mes) {
    pthread_t threads[numElementos];
    
    // Reiniciar variables a cada mes
    montoTotalVentas = 0.0;
    utilidadTotalMes = 0.0;

    for (int i = 0; i < numElementos; i++) {
        struct Comida *comida = &ventas[i];
        pthread_create(&threads[i], NULL, calcularCostoVentas, comida);
    }

    for (int i = 0; i < numElementos; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\nResultados del mes de %s:\n", mes);
    printf("Monto total de ventas: %.2f\n", montoTotalVentas);
    printf("Utilidad total del mes: %.2f\n", utilidadTotalMes);
}

int main() {
    // Arreglo de ventas para el mes de julio
    struct Comida ventasJulio[8] = {
        {"Porción pastel de chocolate", 60.00, 20.0, 300.0},
        {"White mocha", 32.00, 19.20, 400.0},
        {"Café americano 8onz", 22.00, 13.20, 1590.0},
        {"Latte 8onz", 24.00, 17.20, 200.0},
        {"Toffee coffee", 28.00, 20.10, 390.0},
        {"Cappuccino 8onz", 24.00, 17.20, 1455.0},
        {"S'mores Latte", 32.00, 23.0, 800.0},
        {"Café tostado molido", 60.00, 20.0, 60.0}
    };
    
    // Arreglo de ventas para el mes de agosto
    struct Comida ventasAgosto[8] = {
        {"Porción pastel de chocolate", 60.00, 20.0, 250.0},
        {"White mocha", 32.00, 19.20, 380.0},
        {"Café americano 8onz", 22.00, 13.20, 800.0},
        {"Latte 8onz", 24.00, 17.20, 250.0},
        {"Toffee coffee", 28.00, 20.10, 600.0},
        {"Cappuccino 8onz", 24.00, 17.20, 1200.0},
        {"S'mores Latte", 32.00, 23.0, 1540.0},
        {"Café tostado molido", 60.00, 20.0, 15.0}
    };

    int numElementos = sizeof(ventasJulio) / sizeof(ventasJulio[0]);
    pthread_mutex_init(&candado, NULL);

    // Procesar las ventas de julio
    printf("\n\n-------------------Procesando ventas de julio-------------------------\n");
    procesarVentasMes(ventasJulio, numElementos, "Julio");

    // Procesar las ventas de agosto
    printf("\n\n-------------------Procesando ventas de Agosto------------------------\n");
    procesarVentasMes(ventasAgosto, numElementos, "Agosto");

    pthread_mutex_destroy(&candado);
    return 0;
}
