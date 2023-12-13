/***************************************************
* 				MÓDULO CLIENTE
*
* En este módulo se encuentran las funciones que....
* 
* 
* */

// Bibliotecas
#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void Validar_Cliente(MYSQL mysql, char correo[50], char contrasena[50]);
void Menu_Cliente(MYSQL mysql, char correo[50], char contrasena[50]);
void Menu_Pedido(MYSQL mysql, char correo[50]);
void Alta_Pedido_C(MYSQL mysql, char correo[50]);
void Agregar_Platillo_C(MYSQL mysql, char correo[50]);
void Precio_Pedido_C(MYSQL mysql, char correo[50]);
void Desplegar_menu(MYSQL mysql);
void Modifica_datos(MYSQL mysql, char correo[50]);
void modifica(MYSQL mysql, char palabra[50], char correo [50]);
void Seguimiento_C(MYSQL mysql, char correo[50]);


void Validar_Cliente(MYSQL mysql, char correo[50], char contrasena[50])
{
    int existe;
    MYSQL_RES *res;
    MYSQL_ROW row;
    MYSQL_FIELD *fields;
    unsigned int i = 0;

    printf("Ingrese su correo: ");
    scanf("%s", correo);
    printf("Ingrese la contraseña: ");
    scanf("%s", contrasena);

// AQUI VA EL QUERY QUE BUSCA EN LA TABLA

// Ejecuta el query

    char procedimiento[150];
    char buffer[1024];

    sprintf(procedimiento,"CALL Validar_Cliente('%s', '%s', @out)", correo, contrasena);
    strcpy(buffer,procedimiento);

    if( mysql_query(&mysql,buffer) ){
        fprintf(stderr,"Error al procesar la petición \"%s\" Error: %s\n",buffer,mysql_error(&mysql));
        exit(1);
    }
    // Agregar una consulta para obtener el valor de la variable de salida
    if(mysql_query(&mysql, "SELECT @out AS ValorSalida")){
        fprintf(stderr,"Error al obtener el valor de salida: %s\n", mysql_error(&mysql));
        exit(1);
    }

    res = mysql_store_result(&mysql);
    if(res == NULL){
        fprintf(stderr,"Error al almacenar el resultado: %s\n", mysql_error(&mysql));
        exit(1);
    }

    row = mysql_fetch_row(res);
    if(row == NULL){
        fprintf(stderr,"Error al leer la fila: %s\n", mysql_error(&mysql));
        exit(1);
    }

    existe = atoi(row[0]); // Convertir el resultado a entero
    mysql_free_result(res); // Liberar el resultado

    if(existe == 0)
    {
    printf("Usuario correcto.\n");
    Menu_Cliente(mysql,correo,contrasena);
    }
    else
    {
    printf("Usuario no encontrado. Intenta de nuevo.\n");
    exit(1);
    }
}

void Menu_Cliente(MYSQL mysql, char correo[50], char contrasena[50])
{
    int accion;

    printf("Ingresa el número de la actividad que quieres realizar:\n\n");
    printf("1. Modificación de datos.\n");
    printf("2. Alta de pedido.\n");
    printf("3. Seguimiento de pedido.\n");
    scanf("%d", &accion);

    switch(accion)
    {
    case 1:
        Modifica_datos(mysql,correo);
        exit(1);
    case 2:
        Desplegar_menu(mysql);
        Alta_Pedido_C(mysql, correo);
        Menu_Pedido(mysql, correo);
        exit(1);
    case 3:
        Seguimiento_C(mysql, correo);
        exit(1);
    default:
        printf("Opción inexistente. Intenta de nuevo.\n");
    }
}

void Modifica_datos(MYSQL mysql, char correo[50])
{
    char n_columna[50];
    char xcosa[50];
    int opcion;
    char palabra[50];

    printf("\nSelecciona el número de la columna que quieres modificar:\n0. Salir\n1. nombre\n2. Apellido paterno\n3. Apellido materno\n4. dirección\n5. teléfono\n6.correo\n7. contraseña\n8. Número de tarjeta\n");
    scanf("%d", &opcion);
    switch(opcion)
    {
        case 1:
            strcpy(palabra, "nombre");
            modifica(mysql, palabra, correo);
            exit(1);
        case 2:
            strcpy(palabra, "apaterno");
            modifica(mysql, palabra, correo);
            exit(1);
        case 3:
            strcpy(palabra, "amaterno");
            modifica(mysql, palabra, correo);
            exit(1);
        case 4:
            strcpy(palabra, "direccion");
            modifica(mysql, palabra, correo);
            exit(1);
        case 5:
            strcpy(palabra, "telefono");
            modifica(mysql, palabra, correo);
            exit(1);
        case 6:
            strcpy(palabra, "correo");
            modifica(mysql, palabra, correo);
            exit(1);
        case 7:
            strcpy(palabra, "contrasenia");
            modifica(mysql, palabra, correo);
            exit(1);
        case 8:
            strcpy(palabra, "numtarjeta");
            modifica(mysql, palabra, correo);
            exit(1);
        case 0:
            exit(1);
        default:
            printf("\nRespuesta inválida, por favor selecciona uno de los números designados\n");
            Modifica_datos(mysql, correo);
    }
}

void modifica(MYSQL mysql, char palabra[50], char correo [50])
{
    char nuevo[50];
    MYSQL_RES *res;
    unsigned int i = 0;
    MYSQL_ROW row;
    MYSQL_FIELD *fields;
    int existe;
    printf("\n¿Cuál será tu %s nuev@?\n", palabra);
    scanf("%s", nuevo);

    char procedimiento[150];
    char buffer[1024];

    sprintf(procedimiento,"CALL Actualizar_Info_C('%s', '%s', '%s')", palabra, nuevo, correo);
    strcpy(buffer,procedimiento);

    if( mysql_query(&mysql,buffer) ){
        fprintf(stderr,"Error al procesar la petición \"%s\" Error: %s\n",buffer,mysql_error(&mysql));
        exit(1);
    }
res = mysql_store_result(&mysql);
    if (res == NULL) {
        fprintf(stderr, "Error al obtener el resultado: %s\n", mysql_error(&mysql));
    }

    // Despliega el resultado del query
    while( (row = mysql_fetch_row(res)) ){
        i = 0;

        for( i=0 ; i < mysql_num_fields(res); i++ ){
            if(row[i] != NULL){
                printf("%s ",row[i]);
            }
            else{
                printf(" \n");
            }
        }
        fputc('\n',stdout);
    }

    mysql_free_result(res);
}

void Seguimiento_C(MYSQL mysql, char correo[50])// FALTA EN MI CUENTA EL SP Seguimiento
{
    MYSQL_RES *res;
    MYSQL_ROW row;
    MYSQL_FIELD *fields;

    unsigned int i = 0;

    char procedimiento[150];
    char buffer[1024];

    sprintf(procedimiento,"CALL Seguimiento_Pedido_C('%s')", correo);
    strcpy(buffer, procedimiento);

    if( mysql_query(&mysql,buffer) ){
        fprintf(stderr,"Error al procesar la petición \"%s\" Error: %s\n",buffer,mysql_error(&mysql));
        exit(1);
    }

    res = mysql_store_result(&mysql);
    if (res == NULL) {
        fprintf(stderr, "Error al obtener el resultado: %s\n", mysql_error(&mysql));
        exit(1);
    }

     printf("El status de tu pedido es: ");
    // Despliega el resultado del query
    while( (row = mysql_fetch_row(res)) ){
        i = 0;
        for( i=0 ; i < mysql_num_fields(res); i++ ){
      if(row[i] != NULL){
            printf("%s ",row[i]);
      }
      else{
        printf(" \n");
      }
    }
    fputc('\n',stdout);
    }

    mysql_free_result (res); // Liberar el resultado
}

void Alta_Pedido_C(MYSQL mysql, char correo[50])
{
  MYSQL_RES *res;
  MYSQL_ROW row;
  MYSQL_FIELD *fields;
  
  int clave_pedido;
  int cantidad;
  unsigned int i = 0;
  char procedimiento[150];
  char buffer[1024];
  
  printf("Por favor, ingresa el numero de tu primer o unico platillo que se agregara a tu pedido: \n");
  scanf("%d",&clave_pedido);
  printf("Ingresa la cantidad que quieres de ese platillo:\n");
  scanf("%d", &cantidad);
  
  //aqui se manda a llamar el SP
  sprintf(procedimiento, "CALL Alta_Pedido_C('%s','%d','%d')",correo, clave_pedido, cantidad);
  strcpy(buffer,procedimiento);
  
  
   if( mysql_query(&mysql,buffer) ){
        fprintf(stderr,"Error al procesar la petición \"%s\" Error: %s\n",buffer,mysql_error(&mysql));
        exit(1);
    }

    res = mysql_store_result(&mysql);
    if (res == NULL) {
        fprintf(stderr, "Error al obtener el resultado: %s\n", mysql_error(&mysql));
        exit(1);
    }

     printf("El status de tu pedido es: ");
    // Despliega el resultado del query
    while( (row = mysql_fetch_row(res)) ){
        i = 0;
        for( i=0 ; i < mysql_num_fields(res); i++ ){
      if(row[i] != NULL){
            printf("%s ",row[i]);
      }
      else{
        printf(" \n");
      }
    }
    fputc('\n',stdout);
    }

    mysql_free_result (res); // Liberar el resultado
}

void Menu_Pedido(MYSQL mysql, char correo[50])
{
  
  int opcion;
  
    do {
        printf("Elige una opción: \n\n");
        printf("1. Agregar un platillo.\n");
        printf("0. Salir.\n");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                Agregar_Platillo_C(mysql, correo);
                break;
            case 0:
                printf("\nVas a precio pedido\n");
                //Precio_Pedido_C(mysql, correo);
                printf("Gracias por usar este programa. Adiós.\n");
                exit(1);  // Salir del programa completamente
            default:
                printf("Opción inexistente. Intenta de nuevo.\n");
                exit(1);
        }
    } while (opcion != 0);
}

void Agregar_Platillo_C(MYSQL mysql, char correo[50]) {
    MYSQL_RES *res;
    MYSQL_ROW row;
    unsigned int i;
    char procedimiento[150];
    char buffer[1024];
    int clave_pedido, cantidad;

    printf("\nPor favor, ingresa el numero del platillo que quieres agregar a tu pedido: ");
    scanf("%d", &clave_pedido);
    printf("\nIngresa la cantidad que quieres de ese platillo: ");
    scanf("%d", &cantidad);

    // Llamada al Stored Procedure
    sprintf(procedimiento, "CALL Agrega_Pedido_C('%s', %d, %d)", correo, clave_pedido, cantidad);
    strcpy(buffer, procedimiento);

    if (mysql_query(&mysql, buffer)) {
        fprintf(stderr, "Error al procesar el query \"%s\" Error: %s\n", buffer, mysql_error(&mysql));
        exit(1);
    }

    // Procesar cada conjunto de resultados
    do {
        res = mysql_store_result(&mysql);
        if (res) {
            // Procesar y mostrar los resultados
            while ((row = mysql_fetch_row(res))) {
                for (i = 0; i < mysql_num_fields(res); i++) {
                    if (row[i] != NULL) {
                        printf("%s ", row[i]);
                    } else {
                        printf(" \n");
                    }
                }
                printf("\n");
            }
            mysql_free_result(res);
        } else {
            if (mysql_field_count(&mysql) > 0) {
                fprintf(stderr, "Error al obtener el resultado: %s\n", mysql_error(&mysql));
                exit(1);
            }
        }
    } while (!mysql_next_result(&mysql));
}

void Precio_Pedido_C(MYSQL mysql, char correo[50]) {
    MYSQL_RES *res;
    MYSQL_ROW row;
    char procedimiento[150];
    char buffer[1024];

    // Llama al Stored Procedure
    sprintf(procedimiento, "CALL Precio_Pedido_C('%s', @out)", correo);
    strcpy(buffer, procedimiento);

    // Ejecuta el Stored Procedure
    if (mysql_query(&mysql, buffer)) {
        fprintf(stderr, "Error al procesar el query \"%s\" Error: %s\n", buffer, mysql_error(&mysql));
        exit(1);
    }

    // Asegúrate de procesar todos los conjuntos de resultados que pueda haber devuelto el Stored Procedure
    do {
        res = mysql_store_result(&mysql);
        if (res) {
            mysql_free_result(res);
        }
    } while (!mysql_next_result(&mysql));

    // Ahora es seguro ejecutar la siguiente consulta para obtener el valor de salida
    if (mysql_query(&mysql, "SELECT @out")) {
        fprintf(stderr, "Error al obtener el valor de salida: %s\n", mysql_error(&mysql));
        exit(1);
    }

    res = mysql_store_result(&mysql);
    if (res == NULL) {
        fprintf(stderr, "Error al almacenar el resultado: %s\n", mysql_error(&mysql));
        exit(1);
    }

    row = mysql_fetch_row(res);
    if (row == NULL) {
        fprintf(stderr, "Error al leer la fila: %s\n", mysql_error(&mysql));
        mysql_free_result(res);
        exit(1);
    }

    // Suponiendo que el valor de salida es un entero
    int precio = atoi(row[0]);
    printf("\nEl precio total de tu pedido es de %d.\n", precio);

    mysql_free_result(res); // No olvides liberar el resultado
}





void Desplegar_menu(MYSQL mysql)
{
MYSQL_RES *res;
 MYSQL_ROW row;
 MYSQL_FIELD *fields;

unsigned int i = 0;

    char buffer[1024];
 // sprintf(procedimiento,"SELECT id_platillos as numero_platillo, nombre,  precio, descripcion FROM platillos");
    strcpy(buffer,"SELECT id_platillos as numero_platillo, nombre,  precio, descripcion FROM platillos");

   if( mysql_query(&mysql,buffer) ){
        fprintf(stderr,"Error al procesar el query \"%s\" Error: %s\n",buffer,mysql_error(&mysql));
        exit(1);
    }

    // Obtiene el query
    if( !(res = mysql_store_result(&mysql)) ){
        fprintf(stderr,"Error al obtener el resultado Error: %s\n",mysql_error(&mysql));
        exit(1);
    }


    // Despliega el resultado del query
    while( (row = mysql_fetch_row(res)) ){
        i = 0;

        for( i=0 ; i < mysql_num_fields(res); i++ ){
          if(row[i] != NULL){
            printf("%s ",row[i]);
          }
          else{
            printf(" \n");
          }
        }
        fputc('\n',stdout);
    }


mysql_free_result(res); //libera el resultado

}