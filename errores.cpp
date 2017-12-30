//funciones de copiar y longitud
#include <string>
//funciones de ancho de cadena
#include <iomanip>
//acceso al header
#include "errores.h"
using namespace std;
//constructor de errores
error::error(void)
{
	//
}
//funcion para el manejo del error
void error::manejar(unsigned short numero, datos_error &data)
{
	for(unsigned short i=0; i<ERR_TOTAL; i++)
	{
		unsigned short n = 0;
		for(unsigned short j=0; j<strlen(errores[i][ERR_NUMERO]); j++)
		{
			n = 10 * n + (errores[i][ERR_NUMERO][j] - '0');
			if(n == numero)
			{
				data.numero = n;
				strcpy(data.texto,errores[i][ERR_TEXTO]);
				strcpy(data.mensaje,errores[i][ERR_MENSAJE]);
				return;
			}
		}
	}
}
