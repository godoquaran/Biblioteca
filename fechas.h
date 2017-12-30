#include <ostream>
#ifndef _FECHAS_H_
#define _FECHAS_H_
//TAMAÑOS ASIGNADOS
#define FEC_MAX 10
#define FEC_COMPLETA 25
#define ANNO_MIN 1900
//estructura de datos para almacenar los errores
struct datos_fecha
{
	//datos en formatos
	//MM/DD/AAAA[NULL]
	//0123456789[10]
	char mmddaaaa[FEC_MAX+1];
	//AAAA/MM/DD[NULL]
	//0123456789[10]
	char aaaammdd[FEC_MAX+1];
	//DD de MM de AAAA
	char completa[FEC_COMPLETA];
	//datos individuales
	unsigned short dia_semana;
	unsigned short dia;
	unsigned short mes;
	unsigned short anno;	
};
//clase para manejar fechas
class fecha
{
private:
	//estructura de datos
	datos_fecha datos;
public:
	//constructor por defecto
	fecha(void);
	//copia los datos de una fecha
	void copiar(datos_fecha);
	//obtiene una copia de los datos de una fecha
	void copiar_en(datos_fecha&);
	//imprime la fecha en diferentes formatos
	void actualizar(void);
	//funcion para obtener la fecha actual
	datos_fecha obtener_actual(void);
	//funcion para obtener la fecha en el formato MM/DD/AAAA
	char* obtener_mmddaaaa(datos_fecha);
	//funcion para obtener la fecha en el formato AAAA/MM/DD
	char* obtener_aaaammdd(datos_fecha);
	//funcion para obtener la fecha en formato largo
	char* obtener_completa(datos_fecha);	
	//funcion para ingresar una fecha
	void ingresar(void);
	//funcion para ingresar una fecha
	void ingresar(datos_fecha);
	//funcion para ingresar una fecha ingresada en el formato MM/DD/AAAA
	void ingresar_mmddaaaa(char*);
	//funcion para ingresar una fecha de prestamo
	void prestamo(void);
	//funcion para ingresar una fecha de entrega dada un fecha de prestamo
	void entrega(datos_fecha);
	//funcion para calcular la edad
	void calcular_edad(datos_fecha, unsigned short&);
	//fecha actual con el dia de la semana
	void calcular_dia_semana(datos_fecha, unsigned short&);
	// Sobrecarga de operadores de comparación
	friend int operator> (const datos_fecha&, const datos_fecha&);
	friend int operator< (const datos_fecha&, const datos_fecha&);
	friend int operator== (const datos_fecha&, const datos_fecha&);
	// Sobrecarga del operador de inserción en el flujo de salida
	friend ostream& operator<< (ostream&, const datos_fecha&);	
};
#endif
