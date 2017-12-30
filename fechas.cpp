//libreria para las funciones de teclado
#include <conio.h>
//header de fechas
#include "fechas.h"
using namespace std;
//constructor
fecha::fecha(void)
{
	strcpy(datos.mmddaaaa,"");
	strcpy(datos.aaaammdd,"");
	strcpy(datos.completa,"");
	datos.dia_semana = 0;
	datos.dia = 0;
	datos.mes = 0;
	datos.anno = 0;	
}
//copia los datos de una fecha
void fecha::copiar(datos_fecha data)
{
	strcpy(datos.mmddaaaa,data.mmddaaaa);
	strcpy(datos.aaaammdd,data.aaaammdd);
	strcpy(datos.completa,data.completa);
	datos.dia_semana = data.dia_semana;
	datos.dia = data.dia;
	datos.mes = data.mes;
	datos.anno = data.anno;
}
//obtiene una copia de los datos de una fecha
void fecha::copiar_en(datos_fecha &data)
{
	strcpy(data.mmddaaaa,datos.mmddaaaa);
	strcpy(data.aaaammdd,datos.aaaammdd);
	strcpy(data.completa,datos.completa);
	data.dia_semana = datos.dia_semana;
	data.dia = datos.dia;
	data.mes = datos.mes;
	data.anno = datos.anno;	
}
//imprime la hora
void fecha::actualizar(void)
{
	//cadenas con hora y fecha completas de la estructura
	strcpy(datos.mmddaaaa,obtener_mmddaaaa(datos));
	strcpy(datos.aaaammdd,obtener_aaaammdd(datos));
	strcpy(datos.completa,obtener_completa(datos));
	//dia de la semana
	calcular_dia_semana(datos,datos.dia_semana);
}
// operador friend de test de igualdad sobrecargado
int operator> (const datos_fecha &a, const datos_fecha &b)
{
	if (a.anno>b.anno)
		return 1;
	else if(a.anno==b.anno && a.mes>b.mes)
		return 1;
	else if(a.anno==b.anno && a.mes==b.mes && a.dia>b.dia)
		return 1;
	else
		return 0;
}
int operator< (const datos_fecha &a, const datos_fecha &b)
{
	if (a.anno<b.anno)
		return 1;
	else if(a.anno==b.anno && a.mes<b.mes)
		return 1;
	else if(a.anno==b.anno && a.mes==b.mes && a.dia<b.dia)
		return 1;
	else
		return 0;
}
int operator== (const datos_fecha &a, const datos_fecha &b)
{
	if (a.dia==b.dia && a.mes==b.mes && a.anno==b.anno)
		return 1;
	else
		return 0;
}
//imprime la fecha
ostream& operator << (ostream& co, const datos_fecha &a)
{
	char* meses[] = {"Sin mes","Enero","Febrero","Marzo","Abril","Mayo","Junio","Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre"};
	char* dias[] = {"Sin dia","Domingo","Lunes","Martes","Miercoles","Jueves","Viernes","Sabado"};	
	if(a.dia_semana > 0)
		co<<dias[a.dia_semana]<<", "<<a.dia<<" de "<<meses[a.mes]<<" de "<<a.anno;
	else
		co<<a.dia<<" de "<<meses[a.mes]<<" de "<<a.anno;	
}
//funcion para obtener la fecha actual
//int	tm_sec;		/* Seconds: 0-59 (K&R says 0-61?) */
//int	tm_min;		/* Minutes: 0-59 */
//int	tm_hour;	/* Hours since midnight: 0-23 */
//int	tm_mday;	/* Day of the month: 1-31 */
//int	tm_mon;		/* Months *since* january: 0-11 */
//int	tm_year;	/* Years since 1900 */
//int	tm_wday;	/* Days since Sunday (0-6) */
//int	tm_yday;	/* Days since Jan. 1: 0-365 */
//int	tm_isdst;	/* +1 Daylight Savings Time, 0 No DST,
					/* -1 don't know */
datos_fecha fecha::obtener_actual(void)
{
	//fecha actual
	time_t lt;   
	lt = time(NULL); 
	//hora y fecha del sistema
	struct tm *hoy; 
	hoy = localtime(&lt);
	//estructura
	datos_fecha data;
	//fecha actual	
	data.dia_semana	= (unsigned short)hoy->tm_wday;
	data.dia_semana	+= 1;
	data.dia		= (unsigned short)hoy->tm_mday;
	data.mes		= (unsigned short)hoy->tm_mon;
	data.mes		+= 1;
	data.anno		= (unsigned short)hoy->tm_year;
	data.anno		+= 1900;
	//cadenas con fecha y hora completa de la estructura
	strcpy(data.mmddaaaa,obtener_mmddaaaa(data));
	strcpy(data.aaaammdd,obtener_aaaammdd(data));
	strcpy(data.completa,obtener_completa(data));
	return data;
}
//funcion para obtener la fecha en el formato MM/DD/AAAA
char* fecha::obtener_mmddaaaa(datos_fecha data)
{
	unsigned short n = 0;
	char* date = new char[FEC_MAX+1];
	memset(date,'0',FEC_MAX);
	//MM/DD/AAAA[NULL]
	//0123456789[10]
	date[2] = date[5] = '/';
	//mes actual
	n = 1;
	for(unsigned short j=data.mes; j>0; j/=10)
		date[n--] = ('0' + (j % 10));
	//dia actual
	n = 4;
	for(unsigned short j=data.dia; j>0; j/=10)
		date[n--] = ('0' + (j % 10));
	//anno actual
	n = 9;
	for(unsigned short j=data.anno; j>0; j/=10)
		date[n--] = ('0' + (j % 10));
	date[FEC_MAX] = '\0';
	return date;
}
//funcion para obtener la fecha en el formato AAAA/MM/DD
char* fecha::obtener_aaaammdd(datos_fecha data)
{
	unsigned short n = 0;
	char* date = new char[FEC_MAX+1];
	memset(date,'0',FEC_MAX);
	//AAAA/MM/DD[NULL]
	//0123456789[10]
	date[4] = date[7] = '/';
	//anno actual
	n = 3;
	for(unsigned short j=data.anno; j>0; j/=10)
		date[n--] = ('0' + (j % 10));
	//mes actual
	n = 6;
	for(unsigned short j=data.mes; j>0; j/=10)
		date[n--] = ('0' + (j % 10));
	//dia actual
	n = 9;
	for(unsigned short j=data.dia; j>0; j/=10)
		date[n--] = ('0' + (j % 10));
	date[FEC_MAX] = '\0';
	return date;
}
//funcion para obtener la fecha en formato completo
char* fecha::obtener_completa(datos_fecha data)
{
	char* meses[] = 
	{"sem niS","orenE","orerbeF","ozraM","lirbA","oyaM","oinuJ","oiluJ","otsogA","erbmeitpeS","erbutcO","erbmeivoN","erbmeiciD"};
	unsigned short n = 0;
	char* date = new char[FEC_COMPLETA];
	char* sep = " ed ";
	//anno actual
	for(unsigned short j=data.anno; j>0; j/=10)
		date[n++] = ('0' + (j % 10));
	date[n] = '\0';
	strcat(date,sep);
	strcat(date,meses[data.mes]);
	strcat(date,sep);
	//dia actual
	n = strlen(date);
	for(unsigned short j=data.dia; j>0; j/=10)
		date[n++] = ('0' + (j % 10));
	date[n] = '\0';
	strrev(date);
	return date;
}
//funcion para ingresar una fecha de nacimiento
void fecha::ingresar(void)
{
	//fecha y tiempo actual
	datos_fecha hoy;
	hoy = obtener_actual();
	//igualar fechas
	copiar(hoy);
	//año maximo y minimo para un nacimiento actual
	//ahora la fecha
	char* buffer = new char[5];	
	//imprimir mascara
	cout<<"AAAA/MM/DD";
	for(unsigned short j=0;j<FEC_MAX;j++)
		cout<<'\b';
	char digito;
	unsigned short i;	
	//ingresar el año
	do
	{
		i = 0;
		while(i < 4)
		{
			digito = getche();
			if(isdigit(digito))
				buffer[i++] = digito;
			else
				cout<<'\b';
		}
		datos.anno = 0;
		for(unsigned short j=0; j<4; j++)
			datos.anno = 10 * datos.anno + (buffer[j] - '0');
		if(datos.anno < ANNO_MIN || datos > hoy)
		{
			for(unsigned short j=0;j<4;j++)
				cout<<'\b';
			cout<<"AAAA";
			for(unsigned short j=0;j<4;j++)
				cout<<'\b';
		}
	}while(datos.anno < ANNO_MIN || datos > hoy);
	//determina is es bisiesto
	unsigned short bis = 0;
	bis = datos.anno%4 == 0 && datos.anno%100 != 0 || datos.anno%400 == 0;
	//siguiente campo
	cout<<'/';
	//ingresar el mes
	do
	{
		i = 0;
		while(i < 2)
		{
			digito = getche();
			if(isdigit(digito))
				buffer[i++] = digito;
			else
				cout<<'\b';
		}
		datos.mes = 0;
		for(unsigned short j=0; j<2; j++)
			datos.mes = 10 * datos.mes + (buffer[j] - '0');
		//verifica si el año es el actual y el mes es mayor que el actual
		if(datos.mes<1 || datos.mes>12 || datos > hoy)
		{
			for(unsigned short j=0; j<2; j++)
				cout<<'\b';
			cout<<"MM";
			for(unsigned short j=0; j<2; j++)
				cout<<'\b';
		}
	}while(datos.mes < 1 || datos.mes > 12 || datos > hoy);
	//46911
	unsigned short meses[] = {0,31,28+bis,31,30,31,30,31,31,30,31,30,31};
	//						  0, 1,     2, 3, 4, 5, 6, 7, 8, 9,10,11,12
	//siguiente campo
	cout<<'/';
	//ingresar el dia
	do
	{
		i = 0;
		while(i < 2)
		{
			digito = getche();			
			if(isdigit(digito))
				buffer[i++] = digito;
			else
				cout<<'\b';
		}
		datos.dia = 0;
		for(unsigned short j=0; j<2; j++)
			datos.dia = 10 * datos.dia + (buffer[j] - '0');
		//verifica si el año es el actual y el mes es mayor que el actual
		if(datos.dia < 1 || datos.dia > meses[datos.mes] || datos > hoy)
		{
			for(unsigned short j=0;j<2;j++)
				cout<<'\b';
			cout<<"DD";
			for(unsigned short j=0;j<2;j++)
				cout<<'\b';
		}
	}while(datos.dia < 1 || datos.dia > meses[datos.mes] || datos > hoy);
	//cadenas con hora y fecha completas de la estructura
	actualizar();
}
//funcion para ingresar una fecha
void fecha::ingresar(datos_fecha data)
{
	datos.dia = data.dia;
	datos.mes = data.mes;
	datos.anno = data.anno;	
	actualizar();
}
//funcion para ingresar una fecha
void fecha::ingresar_mmddaaaa(char* c)
{
	//MM/DD/AAAA[NULL]
	//0123456789[10]
	//mes 
	datos.mes = 0;
	for(unsigned short j=0; j<2; j++)
		datos.mes = 10 * datos.mes + (c[j] - '0');	
	//dia 
	datos.dia = 0;
	for(unsigned short j=3; j<5; j++)
		datos.dia = 10 * datos.dia + (c[j] - '0');	
	//anno actual
	datos.anno = 0;
	for(unsigned short j=6; j<10; j++)
		datos.anno = 10 * datos.anno + (c[j] - '0');
	//llenar los campos faltantes
	actualizar();
}
//funcion para ingresar una fecha de prestamo
void fecha::prestamo(void)
{
	//fecha y tiempo actual
	datos_fecha hoy;
	hoy = obtener_actual();
	//igualar fechas
	copiar(hoy);
	//AAAA/MM/DD[NULL]
	//0123456789[10]
	cout<<hoy.aaaammdd;
	for(unsigned short j=0;j<FEC_MAX;j++)
		cout<<'\b';
	//fecha calculada
	char* buffer = new char[5];
	char digito;
	unsigned short i;
	//ingresar el anno
	do
	{
		i = 0;
		while(i < 4)
		{
			digito = getche();
			//se ha ingresado la fecha actual + ENTER
			if(i == 0 && (int)digito == 13)
			{
				copiar(hoy);
				actualizar();
				return;
			}
			if(isdigit(digito))
				buffer[i++] = digito;
			else
				cout<<'\b';
		}
		datos.anno = 0;
		for(unsigned short j=0; j<4; j++)
			datos.anno = 10 * datos.anno + (buffer[j] - '0');
		if(datos < hoy)
		{
			for(unsigned short j=0;j<4;j++)
				cout<<'\b';
			for(unsigned short j=0;j<4;j++)
				cout<<hoy.aaaammdd[j];
			for(unsigned short j=0;j<4;j++)
				cout<<'\b';
		}
	}while(datos < hoy);	
	//determina is es bisiesto
	unsigned short bis = 0;
	bis = datos.anno%4 == 0 && datos.anno%100 != 0 || datos.anno%400 == 0;
	//siguiente campo
	cout<<'/';
	//ingreso del mes
	do
	{
		i = 0;
		while(i < 2)
		{
			digito = getche();
			//se ha ingresado la fecha actual + ENTER
			if(i == 0 && (int)digito == 13)
			{
				datos.mes = hoy.mes;
				datos.dia = hoy.dia;
				actualizar();
				return;
			}			
			if(isdigit(digito))
				buffer[i++] = digito;
			else
				cout<<'\b';
		}
		datos.mes = 0;
		for(unsigned short j=0; j<2; j++)
			datos.mes = 10 * datos.mes + (buffer[j] - '0');
		if(datos.mes < 1 || datos.mes > 12 || datos < hoy)
		{
			for(unsigned short j=0;j<2;j++)
				cout<<'\b';
			for(unsigned short j=5; j<7; j++)
				cout<<hoy.aaaammdd[j];
			for(unsigned short j=0;j<2;j++)
				cout<<'\b';
			i = 0;
			datos.mes = 0;
		}
	}while(datos.mes < 1 || datos.mes > 12 || datos < hoy);
	//46911
	unsigned short meses[] = {0,31,28+bis,31,30,31,30,31,31,30,31,30,31};
	//						  0, 1,     2, 3, 4, 5, 6, 7, 8, 9,10,11,12
	//siguiente campo
	cout<<'/';
	//ingreso del dia
	do
	{
		i = 0;
		while(i < 2)
		{
			digito = getche();
			//se ha ingresado la fecha actual + ENTER
			if(i == 0 && (int)digito == 13)
			{
				datos.dia = hoy.dia;
				actualizar();
				return;
			}				
			if(isdigit(digito))
				buffer[i++] = digito;
			else
				cout<<'\b';
		}
		datos.dia = 0;
		for(unsigned short j=0; j<2; j++)
			datos.dia = 10 * datos.dia + (buffer[j] - '0');
		if(datos.dia < 1 || datos.dia > meses[datos.mes] || datos < hoy)
		{
			for(unsigned short j=0;j<2;j++)
				cout<<'\b';
			for(unsigned short j=8; j<10; j++)
				cout<<hoy.aaaammdd[j];
			for(unsigned short j=0;j<2;j++)
				cout<<'\b';
		}
	}while(datos.dia < 1 || datos.dia > meses[datos.mes] || datos < hoy);
	//imprime las cadenas completas para la estructura
	actualizar();
}
//funcion para ingresar una fecha de entrega dada una fecha de prestamo
void fecha::entrega(datos_fecha prestamo)
{
	//AAAA/MM/DD[NULL]
	//0123456789[10]
	cout<<prestamo.aaaammdd;
	//copiar la fecha inicial
	copiar(prestamo);
	for(unsigned short j=0;j<FEC_MAX;j++)
		cout<<'\b';
	//fecha calculada
	char* buffer = new char[5];
	char digito;
	unsigned short i;
	//ingresar el anno
	do
	{
		i = 0;
		while(i < 4)
		{
			digito = getche();
			//se ha ingresado la fecha actual + ENTER
			if(i == 0 && (int)digito == 13)
			{
				copiar(prestamo);
				actualizar();
				return;
			}
			if(isdigit(digito))
				buffer[i++] = digito;
			else
				cout<<'\b';
		}
		datos.anno = 0;
		for(unsigned short j=0; j<4; j++)
			datos.anno = 10 * datos.anno + (buffer[j] - '0');
		if(datos < prestamo)
		{
			for(unsigned short j=0;j<4;j++)
				cout<<'\b';
			for(unsigned short j=0;j<4;j++)
				cout<<prestamo.aaaammdd[j];
			for(unsigned short j=0;j<4;j++)
				cout<<'\b';
		}
	}while(datos < prestamo);	
	//determina is es bisiesto
	unsigned short bis = 0;
	bis = datos.anno%4 == 0 && datos.anno%100 != 0 || datos.anno%400 == 0;
	//siguiente campo
	cout<<'/';
	//ingreso del mes
	do
	{
		i = 0;
		while(i < 2)
		{
			digito = getche();
			//se ha ingresado la fecha actual + ENTER
			if(i == 0 && (int)digito == 13)
			{
				datos.mes = prestamo.mes;
				datos.dia = prestamo.dia;
				actualizar();
				return;
			}			
			if(isdigit(digito))
				buffer[i++] = digito;
			else
				cout<<'\b';
		}
		datos.mes = 0;
		for(unsigned short j=0; j<2; j++)
			datos.mes = 10 * datos.mes + (buffer[j] - '0');
		if(datos.mes < 1 || datos.mes > 12 || datos < prestamo)
		{
			for(unsigned short j=0;j<2;j++)
				cout<<'\b';
			for(unsigned short j=5; j<7; j++)
				cout<<prestamo.aaaammdd[j];
			for(unsigned short j=0;j<2;j++)
				cout<<'\b';
		}
	}while(datos.mes < 1 || datos.mes > 12 || datos < prestamo);
	//46911
	unsigned short meses[] = {0,31,28+bis,31,30,31,30,31,31,30,31,30,31};
	//						  0, 1,     2, 3, 4, 5, 6, 7, 8, 9,10,11,12
	//siguiente campo
	cout<<'/';
	//ingreso del dia
	do
	{
		i = 0;
		while(i < 2)
		{
			digito = getche();
			//se ha ingresado la fecha actual + ENTER
			if(i == 0 && (int)digito == 13)
			{
				datos.dia = prestamo.dia;
				actualizar();
				return;
			}				
			if(isdigit(digito))
				buffer[i++] = digito;
			else
				cout<<'\b';
		}
		datos.dia = 0;
		for(unsigned short j=0; j<2; j++)
			datos.dia = 10 * datos.dia + (buffer[j] - '0');
		if(datos.dia < 1 || datos.dia > meses[datos.mes] || datos < prestamo)
		{
			for(unsigned short j=0;j<2;j++)
				cout<<'\b';
			for(unsigned short j=8; j<10; j++)
				cout<<prestamo.aaaammdd[j];
			for(unsigned short j=0;j<2;j++)
				cout<<'\b';
		}
	}while(datos.dia < 1 || datos.dia > meses[datos.mes] || datos < prestamo);
	//imprime las cadenas completas para la estructura
	actualizar();
}
//funcion para calcular la edad
void fecha::calcular_edad(datos_fecha data, unsigned short &edad)
{
	//fecha y tiempo actual
	datos_fecha hoy;
	hoy = obtener_actual();
	//edad
	edad = hoy.anno - data.anno;
	if ((hoy.mes <= data.mes) && (hoy.dia < data.dia))
		edad -= 1;
}
//fecha actual con el dia de la semana
void fecha::calcular_dia_semana(datos_fecha data, unsigned short &dia)
{
	data.mes 		-= 1;
	data.anno 		-= 1900;
	struct tm natal;	
	natal.tm_sec 	= 0;   /* seconds, 0-59 */ 
	natal.tm_min 	= 0;   /* minutes, 0-59 */ 
	natal.tm_hour 	= 0;  /* hours, 0-23 */ 
	natal.tm_mday 	= data.dia;  /* day of the month, 1-31 */ 
	natal.tm_mon 	= data.mes;   /* months since Jan, 0-11 */ 
	natal.tm_year 	= data.anno;  /* years from 1900 */ 
	natal.tm_wday 	= 0;  /* days since Sunday, 0-6 */ 
	natal.tm_yday 	= 0;  /* days since Jan 1, 0-365 */ 
	natal.tm_isdst 	= 0; /* daylight saving time indicator */ 
	mktime(&natal);
	dia = natal.tm_wday + 1;
}
