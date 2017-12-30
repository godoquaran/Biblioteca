#include <ostream>
#ifndef _PRESTAMOS_H_
#define _PRESTAMOS_H_
//tamaños maximos
#define PRE_MAX 80
#define PRE_BUFFER 125
#define PRE_CAMPOS 5
//tamaños de campos
#define PRE_MAX_NOTA 80
//campos de ingreso
#define PRE_CEDULA 0
#define PRE_CODIGO 1
#define PRE_FECHA_PRE 2
#define PRE_FECHA_ENT 3
#define PRE_NOTA 4
//estructura de datos para almacenar datos de un prestamo
struct datos_prestamo
{
	char cedula[MAX_CEDULA+1];//clave principal del estudiante
	char codigo[MAX_CODIGO+1];//clave principal del libro
	datos_fecha fecha_pre;//MM/DD//AAAA fecha del prestamo
	datos_fecha fecha_ent;//MM/DD/AAAA fecha de la entrega
	char nota[PRE_MAX_NOTA];//anotaciones texto para el prestamo
	bool valido;//valida el objeto para las eliminaciones
};
//clase para almacenar un prestamo de libro
//se utilizan codigos de busqueda
//un libro dado a un estudiante
class prestamo
{
//propiedades de los prestamos de los libros
private:
	datos_prestamo datos;//prestamos realizados
//funciones de la clase prestamos de libros
public:
	prestamo();//constructor por defecto de la clase prestamo
	//ARCHIVO
	unsigned short leer(unsigned long);//leer un prestamo
	unsigned short escribir(void);//ingresar un nuevo prestamo
	unsigned short escribir(unsigned long);//modificar un prestamo
	void copiar(datos_prestamo);//copia los datos de un prestamo
	void copiar_en(datos_prestamo&);//obtiene una copia de los datos de un prestamo
	//ALTAS
	void ingresar(void);//ingresar un nuevo prestamo
	//REPORTES
	void imprimir(void);//imprimir los datos de un prestamo
	//BUSQUEDAS
	bool comparar(datos_estudiante, datos_libro);//compara los datos de un prestamo
	//ELIMINACIONES
	void validar(bool);//validar un prestamo
	//MODIFICACIONES
	void modificar(void);//modifica un prestamo
	//SOBRECARGADAS
	friend ostream& operator<< (ostream&, const datos_prestamo&);
	friend bool operator== (const datos_estudiante&, const datos_estudiante&);//compara las estructuras de datos de dos estudiantes
	friend bool operator== (const datos_libro&, const datos_libro&);//compara dos estructuras de datos de libros
};
//funcion para el menu de seleccion de actividades
void menu_prestamo(usuario*);
//ALTAS
//funcion para ingresar los prestamos
void ingresar_prestamos(void);//MENU DE ALTAS
	//funcion para ingresar prestamos desde un archivo
	void ingresar_archivo_prestamos(void);//ALTAS DE ARCHIVO
		//funcion para obtener los campos de un archivo
		datos_prestamo obtener_prestamo(char*);
	//funcion para ingresar un prestamo desde teclado
	void ingresar_prestamo(void);//ALTA DE TECLADO
//REPORTES
//funcion para imprimir una lista de prestamos
void imprimir_prestamos(void);//MENU DE IMPRESION
//BUSQUEDAS
//funcion para buscar prestamos en el archivo
void buscar_prestamos(void);//MENU DE BUSQUEDAS
	//funcion para buscar un prestamo dada la clave de busqueda
	bool buscar_prestamo(datos_prestamo&, unsigned long&);//BUSQUEDA
//MODIFICACIONES
//funcion para modificar prestamos
void modificar_prestamos(void);//MENU DE MODIFICACIONES
//ELIMINACIONES
//funcion para eliminar prestamos
void eliminar_prestamos(void);//MENU DE ELIMINACIONES
//UTILES
//funcion para obtener el total de datos de prestamos
unsigned long total_prestamos(void);
//funcion que verifica datos validos
unsigned long prestamos_no_validos(void);
//ARCHIVOS
//funcion para guardar los datos validos
void guardar_prestamos(void);
#endif
