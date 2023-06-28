#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct{
    char full_name[60];
    char client_id[9];
    int account_id;
    char password[10];
    int balance;
} Cuenta;

void crear_cuenta()
{
    Cuenta cuenta;
    getchar();
    puts("Introduzca su nombre y apellidos: ");
    scanf("%[^\n]", cuenta.full_name);
    printf("Introduzca su DNI: ");
    scanf("%s", cuenta.client_id);
    printf("Introduzca la contraseña: ");
    scanf("%s", cuenta.password);
    cuenta.balance = 0;
    cuenta.account_id = rand() % 1000000;

    guardar_cuenta(&cuenta, cuenta.client_id);
}

void guardar_cuenta(Cuenta c)
{
    FILE *f;
    if(!(f = fopen("/home/ruby/programacion/c/BankManagement/database/informacion.dat", "ab"))){
        printf("No se ha podido abrir el fichero.");
        return 1;
    }
    fwrite(&c, sizeof(Cuenta), 1, f);
    fclose(f);
}

void imprimir_cuenta(){
    FILE *f;
    Cuenta cuenta;
    if(!(f = fopen("/home/ruby/programacion/c/BankManagement/database/informacion.dat", "rb"))){
        printf("Error al abrir el archivo\n");
        return 2;
    }
    while (fread(&cuenta, sizeof(Cuenta), 1, f)) {
        printf("Nombre: %s\n", cuenta.full_name);
        printf("DNI: %s\n", cuenta.client_id);
        printf("ID de cuenta: %d\n", cuenta.account_id);
        printf("Saldo: %d\n", cuenta.balance);
        printf("\n");
    }
    fclose(f);

}

void imprimir_menu()
{
    printf("1. Crear nueva cuenta\n");
    printf("Seleccione una opción: ");
}

int main() {

    srand(time(NULL));
    printf("¡Bienvenido!\n¿Que operación desea realizar?\n");
    int opcion;
    do {

        imprimir_menu();
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                crear_cuenta();
                break;
            case 2: imprimir_cuenta();
                break;
            default:
                printf("Escoja una opción válida\n");
        }
    } while (opcion != 3);

    printf("Saliendo...");
    return 0;
}
