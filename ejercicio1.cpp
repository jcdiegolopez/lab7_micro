#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Comida {
    char nombre[30];
    double precio;
    double costo;
    double ventas;
};

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


    int numElementos = sizeof(ventasAgosto) / sizeof(ventasAgosto[0]);

    for (int i = 0; i < numElementos; i++) {
        printf("Producto: %s\n", ventasAgosto[i].nombre);
        printf("Precio: $%.2f\n", ventasAgosto[i].precio);
        printf("Costo: $%.2f\n", ventasAgosto[i].costo);
        printf("Ventas: $%.2f\n", ventasAgosto[i].ventas);
        printf("---------------------------------\n");
    }

    return 0;
}
