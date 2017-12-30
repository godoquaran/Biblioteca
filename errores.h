#ifndef _ERRORES_H_
#define _ERRORES_H_
//tamaños de buffer
#define ERR_TOTAL 29
#define ERR_CAMPOS 3
//maximos tamaños asignados
#define ERR_MAX_TEXTO 30
#define ERR_MAX_MENSAJE 175
//campos de ingreso
#define ERR_NUMERO 0
#define ERR_TEXTO 1
#define ERR_MENSAJE 2
//errores posibles de cedula
#define CED_NO_COMPLETA 100
#define CED_SIN_PROVINCIA 101
#define CED_NO_VALIDA 102
#define CED_PUB_NO_VALIDA 103
#define CED_PUBLICA 104
#define CED_PRI_NO_VALIDA 105
#define CED_PRIVADA 106
#define CED_NAT_NO_VALIDA 107
//errores posibles de email
#define MAIL_SIN_SERVIDOR 108
#define MAIL_SER_NO_VALIDO 109
#define MAIL_SER_NO_COM 110
//errores posibles de archivo
#define ARCH_NO_RUTA 111
#define ARCH_NO_LEER 112
#define ARCH_EST_NO_COMPLETO 114
#define ARCH_ERR_NO_COMPLETO 115
#define ARCH_LIB_NO_COMPLETO 116
#define ARCH_PRE_NO_COMPLETO 117
#define ARCH_USU_NO_COMPLETO 118
#define ARCH_NO_ESCRIBIR 119
#define EST_YA_EXISTE 120
#define LIB_YA_EXISTE 121
#define USU_YA_EXISTE 122
//errores posibles de codigo
#define COD_NO_COMPLETO 123
//errores posibles de fecha
#define FEC_NO_COMPLETA 124
#define FEC_SIN_FORMATO 125
//errores posibles de clase
#define EST_NO_ENCONTRADO 126
#define LIB_NO_ENCONTRADO 127
#define PRE_NO_ENCONTRADO 128
#define USU_NO_ENCONTRADO 129
//estructura de datos para almacenar los errores
struct datos_error
{
	unsigned short numero;
	char texto[ERR_MAX_TEXTO];
	char mensaje[ERR_MAX_MENSAJE];
};
static char* errores[ERR_TOTAL][ERR_CAMPOS] = {
{"100","Cedula incompleta","La cedula no tiene los 10 digitos de las cedulas ecuatorianas."},
{"101","Provincia incorrecta","La cedula no tiene asignada una provincia valida para el estado del ecuador."},
{"102","Cedula no valida","La cedula no pertenece a una persona natural, ni a una sociedad privada o extranjera, ni a una sociedad publica."},
{"103","Cedula no valida","La cedula es publica, pero su digito de verificacion no es valido."},
{"104","Cedula publica","La cedula es publica."},
{"105","Cedula no valida","La cedula es privada, pero su digito de verificacion no es valido."},
{"106","Cedula privada","La cedula es privada."},
{"107","Cedula no valida","La cedula es de una persona natural, pero su digito de verificacion no es valido."},
{"108","Email sin servidor","El email no tiene un servidor."},
{"109","Servidor no valido","El email no tiene un servidor valido."},
{"110","Servidor no valido","El servidor no es .com."},
{"111","Ruta no valida","No es una ruta valida para el archivo."},
{"112","Archivo no legible","No se pudo leer el archivo."},
{"114","Archivo no valido","El archivo de estudiantes no tiene los 10 campos."},
{"115","Archivo no valido","El archivo de errores no tiene los 3 campos."},
{"116","Archivo no valido","El archivo de libros no tiene los 12 campos."},
{"117","Archivo no valido","El archivo de prestamos no tiene los 5 campos."},
{"118","Archivo no valido","El archivo de usuarios no tiene los 2 campos."},
{"119","Archivo no escribible","No se pudo escribir en el archivo."},
{"120","Estudiante repetido","El estudiante ya esta ingresado en la biblioteca."},
{"121","Libro repetido","El libro ya esta ingresado en la biblioteca."},
{"122","Usuario repetido","El usuario ya esta ingresado en la biblioteca."},
{"123","Codigo no valido","El codigo del libro no tiene 5 digitos."},
{"124","Fecha incompleta","La fecha no esta completa."},
{"125","Fecha sin formato","La fecha no tiene uno de los formatos predefinidos."},
{"126","Estudiante no existe","El estudiante no se encuentra en el archivo."},
{"127","Libro no existe","El libro no se encuentra en el archivo."},
{"128","Prestamo no existe","El prestamo no se encuentra en el archivo."},
{"129","Usuario no existe","El usuario no se encuentra en el archivo."},
};
//clase para manejar los errores
class error
{
public:
	error(void);
	void manejar(unsigned short numero, datos_error &data);//manejo de un error//solo si existe en el arreglo
};
#endif
