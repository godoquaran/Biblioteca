#ifndef _FUNCIONES_H_
#define _FUNCIONES_H_
//MAXIMOS DE CADENA
#define MAX_CEDULA 10
#define MAX_CODIGO 5
#define MAX_TIEMPO 8
#define MAX_USUARIO 20
#define MAX_SERVIDOR 20
#define MAX_AREA 3
#define MAX_NUMERO 6
//VALIDAR CODIGOS
#define PROVINCIAS 22
//struct tm
//{
	//int	tm_sec;		/* Seconds: 0-59 (K&R says 0-61?) */
	//int	tm_min;		/* Minutes: 0-59 */
	//int	tm_hour;	/* Hours since midnight: 0-23 */
	//int	tm_mday;	/* Day of the month: 1-31 */
	//int	tm_mon;		/* Months *since* january: 0-11 */
	//int	tm_year;	/* Years since 1900 */
	//int	tm_wday;	/* Days since Sunday (0-6) */
	//int	tm_yday;	/* Days since Jan. 1: 0-365 */
	//int	tm_isdst;	/* +1 Daylight Savings Time, 0 No DST,
				// * -1 don't know */
//};
struct datos_tiempo
{	
	char tiempo[MAX_TIEMPO+1];
	unsigned short segundo;
	unsigned short minuto;
	unsigned short hora;
};
//estructura para almacenar un email
struct datos_email
{
	char fecha[MAX_USUARIO+MAX_SERVIDOR];
	char usuario[MAX_USUARIO];
	char servidor[MAX_SERVIDOR];
};
//estructura para almacenar un numero telefonico
struct datos_telefono
{
	char fecha[MAX_AREA+MAX_NUMERO];
	char area[MAX_AREA];
	char numero[MAX_NUMERO];
};
//VALIDACIONES DE CODIGO
//valida el numero de la cedula del ciudadano
unsigned short validar_cedula(char*);
//funcion para validar un codigo
unsigned short validar_codigo(char*);
//funcion para ingresar un email
unsigned short validar_email(char*);
//INGRESO DE CADENAS
//funcion para ingresar un caracter
char ingresar_caracter(char*);
//funcion para ingresar si o no
bool ingresar_sn(void);
//funcion para enmascarar un ingreso
char* ingresar_clave(unsigned short);
//INGRESO DE NUMEROS
//funcion para ingresar un codigo numerico
char* ingresar_numero(char*);
//funcion para ingresar un numero
unsigned short ingresar_numero(unsigned short, unsigned short);
//funcion para intercambiar dos enteros cortos
void intercambiar(unsigned short&, unsigned short&);
//funcion para imprimir un error
void imprimir_error(unsigned short);
#endif
