#ifndef _USUARIOS_H_
#define _USUARIOS_H_
//maximos para la clase
#define USU_BUFFER 52
#define USU_CAMPOS 2
#define USU_MAX 20
//maximos para la estructura de datos
#define USU_MAX_NOMBRE 20
#define USU_MAX_CLAVE 20
//indices de los campos
#define USU_NOMBRE 0
#define USU_CLAVE 1
//tamaños del arreglo
#define USU_PERMISOS 2
#define USU_CLASES 4
//acceso al arreglo
#define USU_LEER 0
#define USU_ESCRIBIR 1
//acceso a las clases
#define USU_ESTUDIANTE 0
#define USU_LIBRO 1
#define USU_PRESTAMO 2
#define USU_USUARIO 3
//estructura de datos para almacenar los datos del usuario
struct datos_usuario
{
	//datos de busqueda
	//nombre del usuario
	char nombre[USU_MAX_NOMBRE];
	//datos personales
	//clave del usuario
	char clave[USU_MAX_CLAVE];
	//permisos de lectura/escritura por clase
	bool permisos[USU_PERMISOS][USU_CLASES];
	//datos del objeto
	//determina si el registro es valido o no
	bool valido;
};
//clase para almacenar los datos del usuario
class usuario
{
private:
	//estructura de datos
	datos_usuario datos;
public:
	usuario(void);
	//ARCHIVO
	//leer un usuario
	unsigned short leer(unsigned long);
	//ingresar un usuario
	unsigned short escribir(void);
	//modificar un usuario
	unsigned short escribir(unsigned long);
	//copia los datos de un usuario
	void copiar(datos_usuario data);
	//obtiene una copia de los datos de un usuario
	void copiar_en(datos_usuario&);
	//ALTAS
	//ingresar un nuevo usuario desde teclado
	void ingresar(void);
	//REPORTES
	//imprimir los datos de un usuario
	void imprimir(void);
	//BUSQUEDAS
	//busca un usuario en el archivo y valida la sesion
	void sesion(void);
	//compara las estructuras de datos de dos usuarios
	bool comparar(datos_usuario);
	//determina si un usuario tiene permiso para leer de una clase
	bool permiso_leer(unsigned short);
	//determina si un usuario tiene permiso para escribir de una clase
	bool permiso_escribir(unsigned short);
	//MODIFICACIONES
	void modificar(void);//modifica un usuario
	//ELIMINACIONES
	void validar(bool);//validar un usuario
	//SOBRECARGADAS
	friend ostream& operator<< (ostream&, const datos_usuario&);
	friend bool operator== (const datos_usuario&, const datos_usuario&);
};
//funcion para el menu de seleccion de actividad
void menu_usuario(usuario*);
//ALTAS
//funcion para ingresar los usuarios
void ingresar_usuarios(void);//MENU DE ALTAS
	//funcion para ingresar usuarios desde un archivo
	void ingresar_archivo_usuarios(void);//ALTAS DE ARCHIVO
		//funcion para obtener los campos de un archivo
		datos_usuario obtener_usuario(char*);
	//funcion para ingresar un estudiante desde teclado
	void ingresar_usuario(void);//ALTA DE TECLADO
//REPORTES
//funcion para imprimir una lista de usuarios
void imprimir_usuarios(void);//MENU DE IMPRESION
//BUSQUEDAS
//funcion para buscar usuarios en el archivo
void buscar_usuarios(void);//MENU DE BUSQUEDAS
	//funcion para buscar un estudiante dada la clave de busqueda
	bool buscar_usuario(datos_usuario&, unsigned long&);//BUSQUEDA
//MODIFICACIONES
//funcion para modificar usuarios
void modificar_usuarios(void);//MENU DE MODIFICACIONES
//ELIMINACIONES
//funcion para eliminar usuarios
void eliminar_usuarios(void);//MENU DE ELIMINACIONES
//UTILES
//funcion para obtener el total de datos de usuarios
unsigned long total_usuarios(void);
//funcion que verifica datos validos
unsigned long usuarios_no_validos(void);
//ARCHIVOS
//funcion para guardar los datos validos
void guardar_usuarios(void);
#endif
