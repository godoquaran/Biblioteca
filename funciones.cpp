//libreria para cout y cin
#include <iostream>
//libreria para setw y setfill
#include <iomanip>
//libreria para los archivos
#include <fstream>
//libreria para NULL
#include <stdlib.h>
//libreria para las funciones de teclado
#include <conio.h>
//acceso al header
#include "funciones.h"
using namespace std;
//VALIDACIONES DE CODIGO
//valida el numero de la cedula del ciudadano
unsigned short validar_cedula(char* c)
{
	//I J K L M N SON ENTEROS
	//valida la cantidad de numeros de la cedula
	//la cedula del estado del ecuador tiene 10 digitos
	if(strlen(c) != MAX_CEDULA)
		return CED_NO_COMPLETA;
	int i = (c[0] - '0');
	i = 10 * i + (c[1] - '0');
	//cout << i << endl;
	//valida que sea una provincia valida
	//el numero debe estar entre 1 y en total de provincias
	if(i <= 0 || i > PROVINCIAS)
		return CED_SIN_PROVINCIA;//no es valida por el numero de provincias
	int j1,j2,j3,j4,j5,j6,j7,j8,j9,j10;
	j1 = (c[0] - '0');
	j2 = (c[1] - '0');
	j3 = (c[2] - '0');
	j4 = (c[3] - '0');
	j5 = (c[4] - '0');
	j6 = (c[5] - '0');
	j7 = (c[6] - '0');
	j8 = (c[7] - '0');
	j9 = (c[8] - '0');
	j10 = (c[9] - '0');
	// El tercer digito es:
	// 9 para sociedades privadas y extranjeros
	// 6 para sociedades publicas
	// menor que 6 (0,1,2,3,4,5) para personas naturales	
	if(j3 == 7 || j3 == 8)
		return CED_NO_VALIDA;//no es valida por el tercer digito
	bool natural,publica,privada;
	natural = publica = privada = false;
	int modulo = 11;
	int k1,k2,k3,k4,k5,k6,k7,k8,k9,k10;
	k1 = k2 = k3 = k4 = k4 = k5 = k6 = k7 = k8 = k9 = k10 = 0;
	//productos para las cedulas naturales
	if(j3 < 6)
	{
		natural = true;
		modulo = 10;
		k1 = j1 * 2;
		if (k1 >= 10)
			k1 -= 9;
		k2 = j2 * 1;
		if (k2 >= 10)
			k2 -= 9;
		k3 = j3 * 2;
		if (k3 >= 10)
			k3 -= 9;
		k4 = j4 * 1;
		if (k4 >= 10)
			k4 -= 9;
		k5 = j5 * 2;
		if (k5 >= 10)
			k5 -= 9;
		k6 = j6 * 1;
		if (k6 >= 10)
			k6 -= 9;
		k7 = j7 * 2;
		if (k7 >= 10)
		k7 -= 9;
		k8 = j8 * 1;
		if (k8 >= 10)
			k8 -= 9;
		k9 = j9 * 2;
		if (k9 >= 10)
			k9 -= 9;		
	}
	//productos para las cedulas publicas
	if(j3 == 6)
	{
		publica = true;
		k1 = j1 * 3;
		k2 = j2 * 2;
		k3 = j3 * 7;
		k4 = j4 * 6;
		k5 = j5 * 5;
		k6 = j6 * 4;
		k7 = j7 * 3;
		k8 = j8 * 2;
		k9 = 0;		
	}
	//productos para las cedulas privadas
	if(j3 == 9)
	{
		privada = true;
		k1 = j1 * 4;
		k2 = j2 * 3;
		k3 = j3 * 2;
		k4 = j4 * 7;
		k5 = j5 * 6;
		k6 = j6 * 5;
		k7 = j7 * 4;
		k8 = j8 * 3;
		k9 = j9 * 2;		
	}
	int suma = 0;	
	suma = k1 + k2 + k3 + k4 + k5 + k6 + k7 + k8 + k9;
	int residuo = 0;
	residuo = suma % modulo;	
	int digitoVerificador = 0;
	// Si residuo=0, dig.ver.=0, caso contrario 10 - residuo
	digitoVerificador = residuo == 0 ? 0 : modulo - residuo;
	if(publica)
	{
		if (digitoVerificador != j9)
			return CED_PUB_NO_VALIDA;//publica, no es valida por el noveno digito de verificacion
		return CED_PUBLICA;//cedula publica		
	}
	if(privada)
	{
		if (digitoVerificador != j10)
			return CED_PRI_NO_VALIDA;//privada, no es valida por el decimo digito de verificacion
		return CED_PRIVADA;//cedula privada
	}
	if(natural)
	{
		if (digitoVerificador != j10)
			return CED_NAT_NO_VALIDA;//natural, no es valida por el decimo digito de verificacion
	}
	//es una cedula valida para una persona natural
	return 0;
}
//funcion para validar el codigo de un libro
unsigned short validar_codigo(char* c)
{
	if(strlen(c) != MAX_CODIGO)
		return COD_NO_COMPLETO;
	return 0;
}
//funcion para ingresar un email
unsigned short validar_email(char* c)
{
	char* arroba = strrchr(c,'@');
	if(arroba != NULL)
	{		
		char* servidor = strrchr(c,'.');
		if(servidor != NULL)
		{
			if(strcmp(servidor,".com") == 0)
				return 0;
			else
				return MAIL_SER_NO_COM;//no es .com
		}
		else
			return MAIL_SER_NO_VALIDO;//no es valido
	}
	return MAIL_SIN_SERVIDOR;//no tiene servidor
}
//INGRESO DE CADENAS
//funcion para ingresar un caracter
char ingresar_caracter(char* c)
{
	int n = strlen(c);
	char opcion[n + 1];
	for(int j=0; j<n; j++)
		opcion[j] = toupper(c[j]);
	opcion[n] = '\0';
	char letra = '*';
	unsigned short i = 0;
	while(i < 1)
	{
		letra = toupper(getche());
		if(strrchr(opcion,letra) == NULL)
			cout << '\b';
		else
			i++;
	}
	return letra;
}
//funcion para ingresar un caracter
bool ingresar_sn(void)
{
	char opcion[] = "SN";
	char letra = '*';
	unsigned short i = 0;
	while(i < 1)
	{
		letra = toupper(getche());
		if(strrchr(opcion,letra) == NULL)
			cout << '\b';
		else
			i++;
	}
	return (letra == 'S');
}
//funcion para enmascarar un ingreso
char* ingresar_clave(unsigned short n)
{
	char* cadena = new char[n];
	char letra = '*';
	unsigned short i = 0;
	do
	{
		letra = getch();
		if((int)letra != 13 && (i < n-1))
			cadena[i++] = letra;
	}while(((int)letra != 13) && (i < n-1));
	cadena[i] = '\0';
	return cadena;
}
//INGRESO DE NUMEROS
//funcion para ingresar un numero
char* ingresar_numero(char* c)
{
	int n = strlen(c);
	cout << c;
	for(int i=0;i<n;i++) 
		cout<<'\b';
	char* codigo = new char[n + 1];
	char digito = '0';
	unsigned short i = 0;
	while(i < n)
	{
		digito = getche();
		if(isdigit(digito))
			codigo[i++] = digito;
		else
			cout << '\b';
	}
	codigo[i] = '\0';
	return codigo;
}
//funcion para ingresar un numero
unsigned short ingresar_numero(unsigned short min, unsigned short max)
{
	unsigned short n = 0;
	//determinar el maximo y el minimo
	if(min > max)
		intercambiar(min,max);
	n = 0;
	//calcular el tamaño de la mascara
	for(unsigned short j=max;j>0;j/=10)
		n++;
	//imprimir mascara
	for(unsigned short j=0;j<n;j++) 
		cout<<'#';		
	for(unsigned short j=0;j<n;j++) 
		cout<<'\b';
	unsigned short anno = 0;
	do
	{
		char* numero = new char[n + 1];
		char digito = '0';
		unsigned short i = 0;
		while(i < n)
		{
			digito = getche();
			if(isdigit(digito))
			{
				numero[i] = digito;
				i++;
			}
			else
				cout << '\b';
		}
		numero[i] = '\0';
		for(unsigned short j=0;j<n;j++)
			anno = anno * 10 + (numero[j] - '0');
		if(anno < min || anno > max)
		{
			for(unsigned short j=0;j<n;j++) 
				cout<<'\b';
			for(unsigned short j=0;j<n;j++) 
				cout<<'#';	
			for(unsigned short j=0;j<n;j++) 
				cout<<'\b';
			anno = 0;
		}			
	}while(anno < min || anno > max);
	//
	return anno;
}
//funcion para intercambiar dos enteros cortos
void intercambiar(unsigned short &a, unsigned short &b)
{
	unsigned short c;
	c = a;
	a = b;
	b = c;
}
//funcion para imprimir un error
void imprimir_error(unsigned short n)
{
	error* err = new error();
	datos_error err_data;
	err->manejar(n,err_data);
	cout<<endl;
	cout<<"Error! "<<err_data.texto<<endl;
	cout<<err_data.mensaje;
	getch();
	cout<<endl;
}
