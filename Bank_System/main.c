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
} Account;

void create_account()
{
    Account account;
    getchar();
    puts("Introduzca su nombre y apellidos: ");
    scanf("%[^\n]", account.full_name);
    printf("Introduzca su DNI: ");
    scanf("%s", account.client_id);
    printf("Introduzca la contraseña: ");
    scanf("%s", account.password);
    account.balance = 0;
    account.account_id = rand() % 1000000;

    guardar_cuenta(&account);
}

void guardar_cuenta(Account c)
{
    FILE *f;
    if(!(f = fopen("/home/ruby/programacion/c/BankManagement/database/informacion.dat", "ab"))){
        printf("No se ha podido abrir el fichero.");
        return 1;
    }
    fwrite(&c, sizeof(Account), 1, f);
    fclose(f);
}

void print_account(){
    FILE *f;
    Account account;
    if(!(f = fopen("/home/ruby/programacion/c/BankManagement/database/informacion.dat", "rb"))){
        printf("Error al abrir el archivo\n");
        return 2;
    }
    while (fread(&account, sizeof(Account), 1, f)) {
        printf("Nombre: %s\n", account.full_name);
        printf("DNI: %s\n", account.client_id);
        printf("ID de cuenta: %d\n", account.account_id);
        printf("Saldo: %d\n", account.balance);
        printf("\n");
    }
    fclose(f);
}

int login()
{
    char DNI[9];
    char password[10];
    printf("Introduzca su ID(DNI): ");
    scanf("%s", DNI);
    printf("Introduzca su contraseña: ");
    scanf("%s", password);
    if(authenticate(DNI, password)){
        printf("El usuario %d ha iniciado sesion exitosamente", DNI);
    }
    else
        printf("Usted no está registrado como cliente.");
}

int authenticate(char *id, char *password) {
    FILE *f;
    Account account;
    if(!(f = fopen("/home/ruby/programacion/c/BankManagement/database/informacion.dat", "rb"))){
        printf("Error al abrir el archivo\n");
        return 3;
    }
    while (fread(&account, sizeof(Account), 1, f)){
        if (strcmp(account.client_id, id) == 0 && strcmp(account.password, password) == 0) {
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

void imprimir_menu()
{
    printf("[1] Crear nueva cuenta\n");
    printf("[2] Iniciar sesion\n");
    printf("[3] Mostrar cuenta\n");
    printf("[4] Salir\n");
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
                create_account();
                break;
            case 2:
                login();
                break;
            case 3:
                print_account();
                break;
        }
    } while (opcion != 4);

    printf("Saliendo...");
    return 0;
}
