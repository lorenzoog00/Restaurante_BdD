/***************************************************
* 				MÓDULO GERENTE
*
* En este módulo se encuentran las funciones que....
* 
* 
****************************************************/

// Bibliotecas

#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void Validar_Gerente(MYSQL mysql, char correo[50], char contrasena[50]);
void Menu_Gerente(MYSQL mysql, char correo[50], char contrasena[50]);
void Consulta_Pedidos_G(MYSQL mysql);
void Consulta_num_pedido_G(MYSQL mysql);
void Consulta_status_G(MYSQL mysql);
void Cambiar_Status_G(MYSQL mysql);


void Validar_Gerente(MYSQL mysql, char correo[50], char contrasena[50])
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
  
  sprintf(procedimiento,"CALL Validar_Gerente('%s', '%s', @out)", correo, contrasena);
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
	Menu_Gerente(mysql,correo,contrasena);
      }
    else
      {
	printf("Usuario no encontrado. Intenta de nuevo.\n");
	exit(1);
      }
}

void Menu_Gerente(MYSQL mysql, char correo[50], char contrasena[50])                                                                                                    
{
  int accion;
  
  printf("Ingresa el número de la actividad que quieres realizar:\n\n");
  printf("1. Consulta de pedidos.\n");
  printf("2. Cambio de estatus.\n");
  scanf("%d", &accion);
  
  switch(accion)
    {
    case 1:
      Consulta_Pedidos_G(mysql);
      exit(1);
    case 2:
      Cambiar_Status_G(mysql);
      exit(1);
    default:
      printf("Opción inexistente. Intenta de nuevo.\n");
      
    }
}

void Consulta_Pedidos_G(MYSQL mysql)
{
  int opcion;
  
  printf("Ingresa el modo de consulta de pedido:\n1. Número de pedido\n2. Por status\n");
  scanf("%d", &opcion);
  switch (opcion)
    {
    case 1:
      Consulta_num_pedido_G(mysql);
      exit(1);
    case 2:
      Consulta_status_G(mysql);
      exit(1);
    default:
      printf("Opción no disponible\n");
    }
}

void Consulta_num_pedido_G(MYSQL mysql)
{
  MYSQL_RES *res;
  MYSQL_ROW row;
  MYSQL_FIELD *fields;
  
  int idPedido;
  unsigned int i = 0;
  
  printf("¿Qué número de pedido quieres rastrear?.\n");
  scanf("%d", &idPedido);
  
  char procedimiento[150];
  char buffer[1024];
  
  sprintf(procedimiento,"CALL Rastreo_numPedido_G('%d')", idPedido);
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

void Consulta_status_G(MYSQL mysql)
{
  MYSQL_RES *res;
  MYSQL_ROW row;
  MYSQL_FIELD *fields;
  
  char status[50];
  unsigned int i = 0;
  
  printf("¿Qué status quieres rastrear?\n");
  limpiarBuffer();
  fgets(status, sizeof(status), stdin);
  status[strcspn(status, "\n")] = 0;
  
  char procedimiento[150];
  char buffer[1024];
  
  sprintf(procedimiento,"CALL Rastreo_statusPedido_G('%s')", status);
  strcpy(buffer, procedimiento);
  
  if( mysql_query(&mysql,buffer)){
    fprintf(stderr,"Error al procesar la petición \"%s\" Error: %s\n",buffer,mysql_error(&mysql));
    exit(1);
  }
  
  res = mysql_store_result(&mysql);
  if (res == NULL) {
    fprintf(stderr, "Error al obtener el resultado: %s\n", mysql_error(&mysql));
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
  
  mysql_free_result (res); // Liberar el resultado
}

void Cambiar_Status_G(MYSQL mysql)
{
  MYSQL_RES *res;
  MYSQL_ROW row;
  MYSQL_FIELD *fields;
  int clave;
  char status[50];
  unsigned int i = 0;
  
  printf("Ingresa la clave del pedido al que le quieres cambiar el status:\n");
  scanf("%d", &clave);
  printf("Ingresa el nuevo status:\n");
  limpiarBuffer();
  fgets(status, sizeof(status), stdin);
  status[strcspn(status, "\n")] = 0;
  
  char procedimiento[150];
  char buffer[1024];
  
  sprintf(procedimiento,"CALL Cambio_Status_G('%d','%s')", clave, status);
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
