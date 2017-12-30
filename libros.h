#include <ostream>
#ifndef _LIBROS_H_
#define _LIBROS_H_
//tamaños maximos
#define LIB_BUFFER 245
#define LIB_CAMPOS 11
#define LIB_MAX 80
//tamaños de campos
#define MAX_AUTOR 3
#define LIB_MAX_CODIGO 6
#define LIB_MAX_NOMBRE 80
#define LIB_MAX_AUTOR 30
#define LIB_MAX_EDITORIAL 20
#define LIB_MAX_CATEGORIA 20
//campos de ingreso
#define LIB_CODIGO 0
#define LIB_NOMBRE 1
#define LIB_AUTOR_1 2
#define LIB_AUTOR_2 3
#define LIB_AUTOR_3 4
#define LIB_COPIA 5
#define LIB_EDICION 6
#define LIB_FECHA_PUB 7
#define LIB_EDITORIAL 8
#define LIB_CATEGORIA 9
#define LIB_DISPONIBLE 10
//estructura de datos para almacenar datos de un libro
struct datos_libro
{
	//datos de busqueda
	char codigo[MAX_CODIGO+1];//codigo de 5 digitos para el libro, clave de busqueda
	//datos de identificacion
	char nombre[LIB_MAX_NOMBRE];//nombre del libro
	char autor[MAX_AUTOR][LIB_MAX_AUTOR];//nombre del autor del libro, permite hasta tres autores
	//datos auxiliares
	unsigned short copias;//cantidad disponible de este ejemplar
	unsigned short edicion;//numero de edicion del libro
	datos_fecha fecha_pub;//fecha de publicacion
	char editorial[LIB_MAX_EDITORIAL];//editorial del libro
	//datos de clasificacion
	char categoria[LIB_MAX_CATEGORIA];//tipo del libro
	bool disponible;//si el libro esta disponible o no para el prestamo
	//datos de objeto
	bool valido;//valida el objeto para la eliminacion
};
//clase para almacenar a los libros
//que se almacenaran en la biblioteca
//y que seran solicitados en prestamo
class libro
{
private:
	datos_libro datos;
public:
	libro(void);
	//ARCHIVO
	//leer un libro
	unsigned short leer(unsigned long);
	//ingresar un nuevo libro
	unsigned short escribir(void);
	//modificar un libro
	unsigned short escribir(unsigned long);
	//copia los datos de un estudiante
	void copiar(datos_libro);
	//obtiene una copia de los datos de un estudiante
	void copiar_en(datos_libro&);
	//ALTAS
	//ingresar un nuevo libro
	void ingresar(void);
	//REPORTES
	//imprimir los datos de un libro
	void imprimir(void);
	//BUSQUEDAS
	//compara los datos de un libro
	bool comparar(datos_libro data);
	//MODIFICACIONES
	//modifica un libro
	void modificar(void);
	//ELIMINACIONES
	//validar un libro
	void validar(bool);
	//SOBRECARGADAS
	friend ostream& operator<< (ostream&, const datos_libro&);
	friend bool operator== (const datos_libro&, const datos_libro&);//compara dos estructuras de datos de libros
};
//funcion para el menu de seleccion de actividad
void menu_libro(usuario*);
//ALTAS
//funcion para ingresar los libros
void ingresar_libros(void);//MENU DE ALTAS
	//funcion para ingresar libros desde un archivo
	void ingresar_archivo_libros(void);//ALTAS DE ARCHIVO
		//funcion para obtener los campos de un archivo
		datos_libro obtener_libro(char*);
	//funcion para ingresar un libro desde teclado
	void ingresar_libro(void);//ALTA DE TECLADO
//REPORTES
//funcion para imprimir una lista de prestamos
void imprimir_libros(void);//MENU DE IMPRESION
//BUSQUEDAS
//funcion para buscar libros en el archivo
void buscar_libros(void);//MENU DE BUSQUEDAS
	//funcion para buscar un libro dada la clave de busqueda
	bool buscar_libro(datos_libro&, unsigned long&);//BUSQUEDA
//MODIFICACIONES
//funcion para modificar libros
void modificar_libros(void);//MENU DE MODIFICACIONES
//ELIMINACIONES
//funcion para eliminar libros
void eliminar_libros(void);//MENU DE ELIMINACIONES
//UTILES
//funcion para obtener el total de datos de libros
unsigned long total_libros(void);
//funcion que verifica datos validos
unsigned long libros_no_validos(void);
//ARCHIVOS
//funcion para guardar los datos validos
void guardar_libros(void);
#endif
