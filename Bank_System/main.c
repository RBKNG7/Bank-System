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
    scanf(" %[^\n]", account.full_name);
    printf("Introduzca su DNI: ");
    scanf("%s", account.client_id);
    printf("Introduzca la contraseña: ");
    scanf("%s", account.password);
    account.balance = 0;
    account.account_id = rand()%100000;

    guardar_cuenta(account);
}

void guardar_cuenta(Account c)
{
    char filename[200];
    FILE *f, *f1;
    sprintf(filename, "/home/ruby/programacion/c/BankManagement/database/%s.dat", c.client_id);
    if(!(f = fopen(filename, "ab"))){
        printf("No se ha podido abrir el fichero.");
        return 1;
    }

    if(!(f = fopen("/home/ruby/programacion/c/BankManagement/database/%s.dat", "ab"))){
        printf("No se ha podido abrir el fichero.");
        return 2;
    }

    fwrite(&c, sizeof(Account), 1, f);
    fwrite(&c, sizeof(Account), 1, f1);

    fclose(f);
    fclose(f1);
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
        printf("El usuario %s ha iniciado sesion exitosamente", DNI);
        return 1;
    }
    else{
        printf("Usted no está registrado como cliente.");
        return 0;
    }

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
    printf("\n[1] Crear nueva cuenta\n");
    printf("[2] Iniciar sesion\n");
    printf("[3] Salir\n");
    printf("Seleccione una opción: ");
}

void imprimir_menu_login()
{
    printf("\n[1] Mostrar datos\n");
    printf("Seleccione una opción: ");
}



int main() {

    srand(time(NULL));
    printf("¡Bienvenido!\n¿Que operación desea realizar?\n");
    int opcion, opcion2;
    do {

        imprimir_menu();
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                create_account();
                break;
            case 2:
                if(login())
                {
                    imprimir_menu_login();
                    scanf("%d", &opcion2);

                    switch(opcion2){
                        case 1: print_account();
                        break;
                    }
                }
                break;
        }
    } while (opcion != 3);

    printf("Saliendo...");
    return 0;
}
