#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct
{
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
    char filename[255];
    FILE *f, *f1;
    sprintf(filename, "/home/ruby/programacion/c/BankManagement/database/%s.dat", c.client_id);
    if(!(f = fopen(filename, "ab"))){
        printf("No se ha podido abrir el fichero.");
        return 1;
    }

    if(!(f1 = fopen("/home/ruby/programacion/c/BankManagement/database/informacion.dat", "ab"))){
        printf("No se ha podido abrir el fichero.");
        return 2;
    }

    fwrite(&c, sizeof(Account), 1, f);
    fwrite(&c, sizeof(Account), 1, f1);

    fclose(f);
    fclose(f1);
}

/*void print_accounts(){ //PARA ADMINS
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
}*/

void print_account(char *id)
{
    FILE *f;
    Account account;
    char filename[200];
    sprintf(filename,"/home/ruby/programacion/c/BankManagement/database/%s.dat", id);
    if(!(f = fopen(filename, "rb"))){
        printf("Error al abrir el archivo\n");
        return 2;
    }
    while (fread(&account, sizeof(Account), 1, f)) {
        printf("Nombre: %s\n", account.full_name);
        printf("DNI: %s\n", account.client_id);
        printf("ID de cuenta: %d\n", account.account_id);
        printf("Saldo: %.2f\n", (float) account.balance/100);
        printf("\n");
    }
    fclose(f);
}

int login(char *id)
{
    char DNI[9];
    char password[10];
    printf("Introduzca su ID(DNI): ");
    scanf("%s", DNI);
    printf("Introduzca su contraseña: ");
    scanf("%s", password);
    if(authenticate(DNI, password)){
        printf("El usuario %s ha iniciado sesion exitosamente", DNI);
        strcpy(id, DNI);
        return 1;
    }
    else{
        printf("Usted no está registrado como cliente.");
        return 0;
    }
}

int authenticate(char *id, char *password)
{
    FILE *f;
    Account account;
    char filename[200];

    sprintf(filename,"/home/ruby/programacion/c/BankManagement/database/%s.dat", id);
    if(!(f = fopen(filename, "rb"))){
        printf("Error al abrir el archivo\n");
        return 2;
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

void deposit(char *id)
{
    char filename[255];
    FILE *f;
    Account account;
    int amount;

    sprintf(filename,"/home/ruby/programacion/c/BankManagement/database/%s.dat", id);

    if(!(f = fopen(filename, "rb+"))){
        printf("Error al abrir el archivo\n");
        return 1;
    }

    fread(&account, sizeof(Account), 1, f);

    float amountAux;
    printf("Introduzca la cuantía a depositar: ");
    scanf("%f", &amountAux);
    amount = amountAux * 100;

    account.balance += amount;

    printf("\033[32mSe han depositado %.2f€\033[0m\n", (float)amount/100);
    printf("Saldo actual: %.2f", (float) account.balance/100);
    rewind(f);
    fwrite(&account, sizeof(Account), 1, f);

    fclose(f);
}

void withdraw(char *id)
{
    char filename[255];
    FILE *f;
    Account account;
    int amount;

    sprintf(filename,"/home/ruby/programacion/c/BankManagement/database/%s.dat", id);

    if(!(f = fopen(filename, "rb+"))){
        printf("Error al abrir el archivo\n");
        return 1;
    }

    fread(&account, sizeof(Account), 1, f);

    float amountAux;
    printf("Introduzca la cuantía a retirar: ");
    scanf("%f", &amountAux);
    amount = amountAux * 100;

    account.balance -= amount;

    printf("\033[31mSe han retirado %.2f€\033[0m\n", (float)amount/100);
    printf("Saldo actual: %.2f", (float) account.balance/100);
    rewind(f);
    fwrite(&account, sizeof(Account), 1, f);

    fclose(f);

}

void delete_account(char *id)
{
    char filename[255];
    sprintf(filename,"/home/ruby/programacion/c/BankManagement/database/%s.dat", id);
    if(!remove(filename))
        printf("Cuenta %s eliminada", id);
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
    printf("[2] Ingresar dinero\n");
    printf("[3] Retirar dinero\n");
    printf("[4] Hacer transferencia\n");
    printf("[5] Cerrar sesión\n");
    printf("[6] Eliminar cuenta\n");
    printf("\nSeleccione una opción: ");
}

int main()
{
    srand(time(NULL));
    printf("¡Bienvenido!\n¿Que operación desea realizar?\n");
    int option, option2, session_active = 0;
    char id[9];
    do {
        imprimir_menu();
        scanf("%d", &option);
        switch (option) {
            case 1:
                create_account();
                break;
            case 2:
                if(login(id)){
                    session_active = 1;
                    do{
                        printf("\n\033[36mSesion %s activa\033[0m\n", id);
                        imprimir_menu_login();
                        scanf("%d", &option2);
                        switch(option2){
                            case 1: print_account(id);
                            break;
                            case 2: deposit(id);
                            break;
                            case 3: withdraw(id);
                            break;
                            case 4: printf("Todavia no esta disponible esta funcion");
                            break;
                            case 5: session_active = 0;
                                    printf("\033[36mCerrando la sesión %s...\033[0m\n", id);
                            break;
                            case 6: delete_account(id);
                            break;
                        }
                    } while (option2 != 7 && session_active == 1);
                }
                break;
        }
    } while (option != 3);

    printf("Saliendo...");
    return 0;
}

