#include <ostream>
#ifndef _ESTUDIANTES_H_
#define _ESTUDIANTES_H_
//tamaños maximos
#define EST_BUFFER 215
#define EST_MAX 50
#define EST_CAMPOS 10
//tamaños de campos
#define EST_MAX_NOMBRE 40
#define EST_MAX_INSTITUCION 30
#define EST_MAX_SEXO 1
#define EST_MAX_DIRECCION 50
#define EST_MAX_EMAIL 40
#define EST_MAX_TELEFONO 8
#define EST_MAX_MOVIL 10
//campos de ingreso
#define EST_CEDULA 0
#define EST_NOMBRE 1
#define EST_ANNO 2
#define EST_INSTITUCION 3
#define EST_SEXO 4
#define EST_FEC_NACIMIENTO 5
#define EST_DIRECCION 6
#define EST_EMAIL 7
#define EST_TELEFONO 8
#define EST_MOVIL 9
//estructura de datos para almecenar a un estudiante
struct datos_estudiante
{
	//datos de busqueda
	//cedula total 10 digitos
	char cedula[MAX_CEDULA+1];
	//datos de identificacion
	//nombres y apellidos del estudiante
	char nombre[EST_MAX_NOMBRE];
	//anno, semestre o nivel al que pertenece
	unsigned short anno;
	//institucion a la que pertenece
	char institucion[EST_MAX_INSTITUCION];
	//datos de clasificacion
	//genero del estudiante
	char sexo;
	//fecha del nacimiento
	datos_fecha fecha_nac;
	//datos personales
	//direccion del estudiante o NULL
	char direccion[EST_MAX_DIRECCION];
	//correo electronico del estudiante o NULL
	char email[EST_MAX_EMAIL];
	//telefono fijo del estudiante
	char telefono[EST_MAX_TELEFONO];
	//celular del estudiante
	char movil[EST_MAX_MOVIL];
	//datos del objeto
	//valida el objeto para la eliminacion
	bool valido;
};
//clase para almacenar a los estudiantes
//de la universidad nacional quary
//que utilizaran la biblioteca
//realizando prestamos de los mismos
class estudiante
{
private:
	//estructura de datos
	datos_estudiante datos;
public:
	//constructor por defecto
	estudiante(void);
	//ARCHIVO
	//leer un estudiante
	unsigned short leer(unsigned long);
	//ingresar un estudiante
	unsigned short escribir(void);
	//modificar un estudiante
	unsigned short escribir(unsigned long);
	//copia los datos de un estudiante
	void copiar(datos_estudiante data);
	//obtiene una copia de los datos de un estudiante
	void copiar_en(datos_estudiante &data);
	//ALTAS
	//ingresar un nuevo estudiante
	void ingresar(void);
	//REPORTES
	//imprimir los datos de un estudiante
	void imprimir(void);
	//BUSQUEDAS
	//compara los datos de un estudiante
	bool comparar(datos_estudiante data);
	//MODIFICACIONES
	//modifica un estudiante
	void modificar(void);
	//ELIMINACIONES
	//validar un estudiante
	void validar(bool);
	//SOBRECARGADAS
	friend ostream& operator<< (ostream&, const datos_estudiante&);
	friend bool operator== (const datos_estudiante&, const datos_estudiante&);//compara las estructuras de datos de dos estudiantes
};
//funcion para el menu de seleccion de actividad
void menu_estudiante(usuario*);
//ALTAS
//funcion para ingresar los estudiantes
void ingresar_estudiantes(void);//MENU DE ALTAS
	//funcion para ingresar estudiantes desde un archivo
	void ingresar_archivo_estudiantes(void);//ALTAS DE ARCHIVO
		//funcion para obtener los campos de un archivo
		datos_estudiante obtener_estudiante(char*);
	//funcion para ingresar un estudiante desde teclado
	void ingresar_estudiante(void);//ALTA DE TECLADO
//REPORTES
//funcion para imprimir una lista de estudiantes
void imprimir_estudiantes(void);//MENU DE IMPRESION
//BUSQUEDAS
//funcion para buscar estudiantes en el archivo
void buscar_estudiantes(void);//MENU DE BUSQUEDAS
	//funcion para buscar un estudiante dada la clave de busqueda
	bool buscar_estudiante(datos_estudiante&, unsigned long&);//BUSQUEDA
//MODIFICACIONES
//funcion para modificar estudiantes
void modificar_estudiantes(void);//MENU DE MODIFICACIONES
//ELIMINACIONES
//funcion para eliminar estudiantes
void eliminar_estudiantes(void);//MENU DE ELIMINACIONES
//UTILES
//funcion para obtener el total de datos de estudiantes
unsigned long total_estudiantes(void);
//funcion que verifica datos validos
unsigned long estudiantes_no_validos(void);
//ARCHIVOS
//funcion para guardar los datos validos
void guardar_estudiantes(void);
#endif
