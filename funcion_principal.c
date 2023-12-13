/***************************************************
* 				FUNCIÓN PRINCIPAL
*
* En este módulo se encuentran las funciones que....
* 
* 
****************************************************/

#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int Ingresar_Tipo();
void limpiarBuffer();

// Funciones Cliente.

extern void Validar_Cliente(MYSQL mysql, char correo[50], char contrasena[50]);

// Funciones Repartidor.
extern void Validar_Repartidor(MYSQL mysql, char correo[50], char contrasena[50]);

// Funciones Gerente
extern void Validar_Gerente(MYSQL mysql, char correo[50], char contrasena[50]);


int main (int argc, char **argv)
{
    unsigned int i = 0;
    char buffer[1024];
    unsigned int num_fields;
    int Opcion;
    char correo[50];
    char contrasena[50];

    char *server = "localhost";
    char *user = "if19jgm"; // Usuario (nuestro)\

    char *passwd = "215536";
    char *db = "if19jgm";

    // Variables para lograr la comunicación con la BD y que vienen incluidas en la librería mysql.h\

    MYSQL mysql;  /*Estructura que representa el manejador de la conexión a la base de datos.*/
    MYSQL_RES *res; /*Estructura que representa el resultado de un query que regresa renglones (resul set)*/
    MYSQL_ROW row; /*Este tipo de datos es el utilizado para obtener un solo renglón como resultado de un query.\

                         Los renglones pueden ser obtenidos llamando a la función mysql_fetch_row().*/
    MYSQL_FIELD *fields; /*Esta estructura contiene información acerca del campo obtenido, tal y como su nombre,\

                                        tipo y tamaño. Los campos de una tabla se pueden obtener mandando llamar a la función\

                                        mysql_fetch_field(). Los valores de los campos no son parte de esta estructura sino que se\

                                        encuentran en la estructura MYSQL_ROW.*/

   if( argc != 2 ){
      fputs("Error: parametros incorrectos <\"query\">\n", stderr);
      return 1;
    }

    mysql_init(&mysql); // Prepara la conexión al servidor de bases de datos\


    // Se conecta al servidor de base de datos y verifica que no haya error\

    if(!mysql_real_connect(&mysql, server, user, passwd, db, 0, NULL, 0)){   //0, NULL, 0 es por default\
                                                                                                                                                      
      fprintf(stderr, "Error al conectarse a la BD: Error: %s\n",mysql_error(&mysql));
      return(0);
    }

    // Se conecta a la base de datos deseada\

    if( mysql_select_db(&mysql,argv[1]) ){
        fprintf(stderr,"No existe la base de datos seleccionada: Error: %s\n",mysql_error(&mysql));
        exit(1);
    }
	do
	  {
	    Opcion = Ingresar_Tipo();
	    switch(Opcion)
	      {
	      case 1:
		Validar_Cliente(mysql, correo, contrasena);
	      case 2:
		Validar_Gerente(mysql, correo, contrasena);
	      case 3:
		Validar_Repartidor(mysql, correo, contrasena);
	      case 0:
		printf("Gracias por usar este programa. Adiós.\n");
	      default:
		printf("Opción inexistente. Intenta de nuevo.\n");
		
	      }
	  }while(Opcion != 0);
	mysql_close(&mysql);
	return 0;
}

int Ingresar_Tipo()
{                                                                                                                                                   
  int Opc;
  
  printf("Restaurant El Bosque de China\n");
  printf("Ingrese el número de su tipo de usuario:\n");
  printf("1. Cliente.\n");
  printf("2. Gerente.\n");
  printf("3. Repartidor.\n");
  printf("0. Salir.\n");
  scanf("%d",&Opc);
  __fpurge(stdin);
  return Opc;
}

void limpiarBuffer()
{                                                                                      
  int c;
  while ((c = getchar()) != '\n' && c != EOF) { }
}
