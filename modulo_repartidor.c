
/***************************************************
 * 				MÓDULO REPARTIDOR
 *
 * En este módulo se encuentran las funciones que....
 * 
 * 
 ***************************************************/

// Bibliotecas
#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void Validar_Repartidor(MYSQL mysql, char correo[50], char contrasena[50]);
void Menu_Repartidor(MYSQL mysql, char correo[50], char contrasena[50]);
void Consulta_Pedidos_R(MYSQL mysql, char correo[50], char contrasena[50]);
void Cambiar_Estatus_R(MYSQL mysql, char correo[50], char contrasena[50]);

void Validar_Repartidor(MYSQL mysql, char correo[50], char contrasena[50])
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
  
  sprintf(procedimiento,"CALL Validar_Repartidor('%s', '%s', @out)", correo, contrasena);
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
      Menu_Repartidor(mysql,correo,contrasena);
    }
  else
    {
      printf("Usuario no encontrado. Intenta de nuevo.\n");
      exit(1);
    }
}

void Menu_Repartidor(MYSQL mysql, char correo[50], char contrasena[50])
{
  int accion;
  
  printf("Ingresa el número de la actividad que quieres realizar:\n\n");
  printf("1. Consultar pedidos.\n");
  printf("2. Cambiar estatus de pedido.\n");
  scanf("%d", &accion);
  
  switch(accion)
    {
    case 1:
      Consulta_Pedidos_R(mysql, correo, contrasena);
      exit(1);
    case 2:
      Cambiar_Estatus_R(mysql, correo, contrasena);
      exit(1);
    }
} 

void Consulta_Pedidos_R(MYSQL mysql, char correo[50], char contrasena[50])
{
  MYSQL_RES *res;
  MYSQL_ROW row;
  MYSQL_FIELD *fields;
  
  int idPedido;
  unsigned int i = 0;
  
  printf("Los pedidos que tienes asignados son.\n\n");
  
  char procedimiento[150];
  char buffer[1024];
  
  sprintf(procedimiento,"CALL Consulta_Pedidos_R('%s', '%s')", correo, contrasena);
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

void Cambiar_Estatus_R(MYSQL mysql, char correo[50], char contrasena[50])
{
  
  /*CALL porRepartirOp2(id_pedido);*/
  MYSQL_RES *res;
  MYSQL_ROW row;
  MYSQL_FIELD *fields;
  int idPedido;
  unsigned int i = 0;
  int existe;
  
  char procedimiento[150];
  char buffer[1024];
  
  /*Consulta_Pedidos_R(mysql, correo, contrasena); */
  
  printf("Ingresa el numero del pedido al que le modificarás el estatus: \n");
  scanf("%d", &idPedido);
  
  sprintf(procedimiento,"CALL Cambiar_Estatus_R('%d')", idPedido);
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
  
  mysql_free_result(res); // Liberar el resultado
  
}
