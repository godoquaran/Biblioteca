//para utilizar cadenas
#include <string>
//encabezado
#include "usuarios.h"
using namespace std;
//FUNCIONES DE CLASE
//constructor por defecto
usuario::usuario(void)
{
	strcpy(datos.nombre,"");
	strcpy(datos.clave,"");
	for(unsigned short i=0; i<USU_PERMISOS; i++)
		for(unsigned short j=0; j<USU_CLASES; j++)
			datos.permisos[i][j] = false;
}
//FUNCIONES DE CLASE PARA ARCHIVO
//cargar los datos del usuario en la estructura de datos
unsigned short usuario::leer(unsigned long pos)
{
	ifstream archivo;
	archivo.open("datos_usuarios.dat",ios::binary);
	if(archivo.fail())
		return ARCH_NO_LEER;
	archivo.seekg(pos*sizeof(datos_usuario),ios::beg);
	archivo.read((char*)&datos,sizeof(datos_usuario));
	archivo.close();
	return 0;
}
//guardar los datos del usuario en un archivo
unsigned short usuario::escribir(void)
{
	ofstream archivo;
	//se abre el archivo para escritura, añadidura y binario
	archivo.open("datos_usuarios.dat",ios::app|ios::binary);
	//el archivo no existe se crea
	if(archivo.bad())
		archivo.open("datos_usuarios.dat");
	archivo.write((char*)&datos,sizeof(datos_usuario));
	archivo.close();
	return 0;
}
//modificar los datos del usuario en el archivo
unsigned short usuario::escribir(unsigned long pos)
{
	fstream archivo;
	archivo.open("datos_usuarios.dat",ios::in|ios::out|ios::binary);
	if(archivo.fail())
		return ARCH_NO_ESCRIBIR;
	archivo.seekp(pos*sizeof(datos_usuario),ios::beg);
	archivo.write((char*)&datos,sizeof(datos_usuario));
	archivo.close();
	return 0;
}
//FUNCIONES DE CLASE PARA INGRESO
//ingreso por copia de datos en la clase usuario
void usuario::copiar(datos_usuario data)
{
	//datos de busqueda
	strcpy(datos.nombre,data.nombre);
	strcpy(datos.clave,data.clave);
	for(unsigned short i=0; i<USU_PERMISOS; i++)
		for(unsigned short j=0; j<USU_CLASES; j++)
			datos.permisos[i][j] = data.permisos[i][j];	
	//datos del objeto
	datos.valido = data.valido;
}
//ingreso de datos de un nuevo usuario desde teclado
void usuario::ingresar(void)
{
	unsigned long pos;
	bool encontrado;
	system("cls");
	//hasta tener una cedula valida
	cout<<"\n\t\tDATOS DEL USUARIO\n\n";
	do
	{
		//ingresar el nombre
		cout<<setw(25)<<"Nombre? ";
		cin.getline(datos.nombre,USU_MAX_NOMBRE);
		encontrado = buscar_usuario(datos,pos);
		if(encontrado)
		{
			cout<<setw(25);
			imprimir_error(USU_YA_EXISTE);
		}
	}while(encontrado);
	//ingresar la clave
	char nombre[USU_MAX_CLAVE];
	do
	{
		cout<<setw(25)<<"Clave? ";
		strcpy(datos.clave,ingresar_clave(USU_MAX_CLAVE));
		cout<<endl;
		cout<<setw(25)<<"Reingrese la Clave? ";
		strcpy(nombre,ingresar_clave(USU_MAX_CLAVE));
		cout<<endl;
		if(strcmp(datos.clave,nombre) != 0)
		{
			cout<<setw(25)<<"Error! ";
			cout<<"La clave no coincide"<<endl;
		}
	}while(strcmp(datos.clave,nombre) != 0);
	//permisos para estudiantes
	cout<<setw(25)<<"Clase Estudiantes: "<<endl;
	cout<<setw(25)<<"Leer [s/n]? ";
	datos.permisos[USU_LEER][USU_ESTUDIANTE] = ingresar_sn();
	cout<<endl;
	cout<<setw(25)<<"Escribir [s/n]? ";
	datos.permisos[USU_ESCRIBIR][USU_ESTUDIANTE] = ingresar_sn();	
	cout<<endl;
	//permisos para libros
	cout<<setw(25)<<"Clase Libros: "<<endl;
	cout<<setw(25)<<"Leer [s/n]? ";
	datos.permisos[USU_LEER][USU_LIBRO] = ingresar_sn();
	cout<<endl;
	cout<<setw(25)<<"Escribir [s/n]? ";
	datos.permisos[USU_ESCRIBIR][USU_LIBRO] = ingresar_sn();	
	cout<<endl;
	//permisos para prestamos
	cout<<setw(25)<<"Clase Prestamos: "<<endl;
	cout<<setw(25)<<"Leer [s/n]? ";
	datos.permisos[USU_LEER][USU_PRESTAMO] = ingresar_sn();
	cout<<endl;
	cout<<setw(25)<<"Escribir [s/n]? ";
	datos.permisos[USU_ESCRIBIR][USU_PRESTAMO] = ingresar_sn();	
	cout<<endl;
	//permisos para usuarios
	cout<<setw(25)<<"Clase Usuarios: "<<endl;
	cout<<setw(25)<<"Leer [s/n]? ";
	datos.permisos[USU_LEER][USU_USUARIO] = ingresar_sn();
	cout<<endl;
	cout<<setw(25)<<"Escribir [s/n]? ";
	datos.permisos[USU_ESCRIBIR][USU_USUARIO] = ingresar_sn();	
	cout<<endl;	
	//validar el objeto
	datos.valido = true;		
}
//FUNCIONES DE CLASE PARA REPORTE
//imprime los datos
ostream& operator << (ostream& co, const datos_usuario &a)
{
	co<<setw(25)<<"Nombre: "<<a.nombre<<endl;
	co<<setw(25)<<"Clase Estudiante: "<<endl;
	co<<setw(25)<<"Leer: "<<boolalpha<<a.permisos[USU_LEER][USU_ESTUDIANTE]<<endl;
	co<<setw(25)<<"Escribir: "<<boolalpha<<a.permisos[USU_ESCRIBIR][USU_ESTUDIANTE]<<endl;
	co<<setw(25)<<"Clase Libro: "<<endl;
	co<<setw(25)<<"Leer: "<<boolalpha<<a.permisos[USU_LEER][USU_LIBRO]<<endl;
	co<<setw(25)<<"Escribir: "<<boolalpha<<a.permisos[USU_ESCRIBIR][USU_LIBRO]<<endl;
	co<<setw(25)<<"Clase Prestamo: "<<endl;
	co<<setw(25)<<"Leer: "<<boolalpha<<a.permisos[USU_LEER][USU_PRESTAMO]<<endl;
	co<<setw(25)<<"Escribir: "<<boolalpha<<a.permisos[USU_ESCRIBIR][USU_PRESTAMO]<<endl;
	co<<setw(25)<<"Clase Usuario: "<<endl;
	co<<setw(25)<<"Leer: "<<boolalpha<<a.permisos[USU_LEER][USU_USUARIO]<<endl;
	co<<setw(25)<<"Escribir: "<<boolalpha<<a.permisos[USU_ESCRIBIR][USU_USUARIO]<<endl;
}
//ingreso de datos en la clase usuario
void usuario::copiar_en(datos_usuario &data)
{
	//datos de busqueda
	strcpy(data.nombre,datos.nombre);
	//datos de identificacion
	strcpy(data.clave,datos.clave);
	for(unsigned short i=0; i<USU_PERMISOS; i++)
		for(unsigned short j=0; j<USU_CLASES; j++)
			data.permisos[i][j] = datos.permisos[i][j];	
	//datos del objeto
	data.valido = datos.valido;
}
//imprime los datos del usuario
void usuario::imprimir(void)
{
	if(datos.valido)
		cout<<setw(25)<<"Nombre: "<<datos.nombre<<endl;
}
//FUNCIONES DE CLASE PARA BUSQUEDA
//busca un usuario en el archivo y valida la sesion
void usuario::sesion(void)
{
	unsigned short n;
	cout<<endl;
	do
	{
		//ingresar el nombre
		cout<<setw(25)<<"Nombre? ";
		cin.getline(datos.nombre,USU_MAX_NOMBRE);
		cout<<setw(25)<<"Clave? ";
		strcpy(datos.clave,ingresar_clave(USU_MAX_CLAVE));
		cout<<endl;
		unsigned long pos;
		if(!buscar_usuario(datos,pos))
		{
			cout<<setw(25);
			imprimir_error(USU_NO_ENCONTRADO);
			n++;
		}
		else		
			return;
	}while(n<3);
	//usuario sin permisos
	for(unsigned short i=0; i<USU_PERMISOS; i++)
		for(unsigned short j=0; j<USU_CLASES; j++)
			datos.permisos[i][j] = false;
}
//busca un usuario dados los datos
bool usuario::comparar(datos_usuario data)
{
	return datos == data;
}
//determina si un usuario tiene permiso para leer de una clase
bool usuario::permiso_leer(unsigned short clase)
{
	if(clase==USU_ESTUDIANTE || clase==USU_LIBRO || clase==USU_PRESTAMO || clase==USU_USUARIO)
		return datos.permisos[USU_LEER][clase];
	return false;
}
//determina si un usuario tiene permiso para escribir de una clase
bool usuario::permiso_escribir(unsigned short clase)
{
	if(clase==USU_ESTUDIANTE || clase==USU_LIBRO || clase==USU_PRESTAMO || clase==USU_USUARIO)
		return datos.permisos[USU_ESCRIBIR][clase];
	return false;
}
//FUNCIONES DE CLASE PARA MODIFICACION
//busca un estudiante dados los datos
void usuario::modificar(void)
{
	unsigned long pos;
	cout<<setw(25)<<"Nombre: "<<datos.nombre<<endl;
	//funcion para validar una clave
	//ingresar la clave
	char nombre[USU_MAX_CLAVE];
	do
	{
		cout<<setw(25)<<"Clave? ";
		strcpy(datos.clave,ingresar_clave(USU_MAX_CLAVE));
		cout<<endl;
		cout<<setw(25)<<"Reingrese la Clave? ";
		strcpy(nombre,ingresar_clave(USU_MAX_CLAVE));
		cout<<endl;
		if(strcmp(datos.clave,nombre) != 0)
		{
			cout<<setw(25)<<"Error! ";
			cout<<"La clave no coincide"<<endl;
		}
	}while(strcmp(datos.clave,nombre) != 0);
	//permisos para estudiantes
	cout<<setw(25)<<"Clase Estudiantes: "<<endl;
	cout<<setw(25)<<"Leer: "<<boolalpha<<datos.permisos[USU_LEER][USU_ESTUDIANTE]<<endl;
	cout<<setw(25)<<"Leer [s/n]? ";
	datos.permisos[USU_LEER][USU_ESTUDIANTE] = ingresar_sn();
	cout<<endl;
	cout<<setw(25)<<"Escribir: "<<boolalpha<<datos.permisos[USU_ESCRIBIR][USU_ESTUDIANTE]<<endl;
	cout<<setw(25)<<"Escribir [s/n]? ";
	datos.permisos[USU_ESCRIBIR][USU_ESTUDIANTE] = ingresar_sn();	
	cout<<endl;
	//permisos para libros
	cout<<setw(25)<<"Clase Libros: "<<endl;
	cout<<setw(25)<<"Leer: "<<boolalpha<<datos.permisos[USU_LEER][USU_LIBRO]<<endl;
	cout<<setw(25)<<"Leer [s/n]? ";
	datos.permisos[USU_LEER][USU_LIBRO] = ingresar_sn();
	cout<<endl;
	cout<<setw(25)<<"Escribir: "<<boolalpha<<datos.permisos[USU_ESCRIBIR][USU_LIBRO]<<endl;
	cout<<setw(25)<<"Escribir [s/n]? ";
	datos.permisos[USU_ESCRIBIR][USU_LIBRO] = ingresar_sn();	
	cout<<endl;
	//permisos para prestamos
	cout<<setw(25)<<"Clase Prestamo: "<<endl;
	cout<<setw(25)<<"Leer: "<<boolalpha<<datos.permisos[USU_LEER][USU_PRESTAMO]<<endl;
	cout<<setw(25)<<"Leer [s/n]? ";
	datos.permisos[USU_LEER][USU_PRESTAMO] = ingresar_sn();
	cout<<endl;
	cout<<setw(25)<<"Escribir: "<<boolalpha<<datos.permisos[USU_ESCRIBIR][USU_PRESTAMO]<<endl;
	cout<<setw(25)<<"Escribir [s/n]? ";
	datos.permisos[USU_ESCRIBIR][USU_PRESTAMO] = ingresar_sn();	
	cout<<endl;
	//permisos para usuarios
	cout<<setw(25)<<"Clase Usuarios: "<<endl;
	cout<<setw(25)<<"Leer: "<<boolalpha<<datos.permisos[USU_LEER][USU_USUARIO]<<endl;
	cout<<setw(25)<<"Leer [s/n]? ";
	datos.permisos[USU_LEER][USU_USUARIO] = ingresar_sn();
	cout<<endl;
	cout<<setw(25)<<"Escribir: "<<boolalpha<<datos.permisos[USU_ESCRIBIR][USU_USUARIO]<<endl;
	cout<<setw(25)<<"Escribir [s/n]? ";
	datos.permisos[USU_ESCRIBIR][USU_USUARIO] = ingresar_sn();	
	cout<<endl;	
	//validar el objeto
	datos.valido = true;
}
//FUNCIONES DE CLASE PARA ELIMINACION
//eliminar los datos de la estructura de datos
void usuario::validar(bool valor)
{
	datos.valido = valor;
}
//FUNCIONES DE CLASE SOBRECARGADAS
// operador friend de test de igualdad sobrecargado
bool operator== (const datos_usuario& a, const datos_usuario& b)
{
	if(strlen(a.nombre) != strlen(b.nombre))
		return false;
	for(int i=0; i<strlen(a.nombre); i++)
		if(a.nombre[i] != b.nombre[i])
			return false;
	return true;
}
//FUNCIONES DE USUARIO
//funcion para imprimir el menu de usuarios
void menu_usuario(usuario* usu)
{
	char opcion = '*';
	do
	{
		system("cls");
		cout<<"\n\t\t\tUSUARIOS\n\n";
		cout<<setw(25)<<""<<"TECLA\n";
		cout<<setw(25)<<"Ingresar: "	<<"[i/I]\n";//ALTA	
		cout<<setw(25)<<"Buscar: "		<<"[b/B]\n";//BUSQUEDA
		cout<<setw(25)<<"Imprimir: "	<<"[p/P]\n";//REPORTE	
		cout<<setw(25)<<"Modificar: "	<<"[m/M]\n";//MODIFICACION
		cout<<setw(25)<<"Eliminar: "	<<"[e/E]\n\n";//BAJA
		cout<<setw(25)<<"Retornar: "	<<"[ESC]\n\n";//EXIT
		cout<<setw(25)<<"Elija una opcion? ";
		opcion = toupper(getche());
		switch(opcion)
		{
			case 'I':
				if(usu->permiso_escribir(USU_USUARIO))
					ingresar_usuarios();
				break;
			case 'B':
				buscar_usuarios();
				break;
			case 'P': 
				imprimir_usuarios();
				break;
			case 'M':
				if(usu->permiso_escribir(USU_USUARIO))
					modificar_usuarios();
				break; 
			case 'E':
				if(usu->permiso_escribir(USU_USUARIO))
					eliminar_usuarios();
				break; 
			default:
				cout<<endl<<endl;			
				if((int)opcion != 27)
				{	
					cout<<setw(25)<<"Opcion no valida! ";
					getch();					
				}
				else
				{
					unsigned long n;
					n = usuarios_no_validos();
					if(n > 0)
					{
						cout<<setw(25)<<"Datos no validos: "<<n<<endl;
						//verificación de salida
						cout<<endl;
						cout<<setw(25)<<"Desea eliminarlos [s/n]? ";
						if(ingresar_sn())
							guardar_usuarios();
					}
				}
				break;
		}
	}while((int)opcion != 27);	
}
//FUNCIONES DE USUARIO PARA INGRESO
//ingreso de datos en la clase
void ingresar_usuarios(void)//MENU DE ALTAS
{
	//menu de ingreso de usuarios
	char opcion = '*';
	do
	{
		system("cls");
		cout<<"\n\t\tINGRESAR USUARIO\n\n";
		cout<<setw(25)<<""<<"TECLA\n";
		cout<<setw(25)<<"Archivo: "		<<"[a/A]\n";
		cout<<setw(25)<<"Teclado: "		<<"[t/T]\n\n";
		cout<<setw(25)<<"Retornar: "	<<"[ESC]\n\n";
		cout<<setw(25)<<"Elija una opcion? ";
		opcion = toupper(getche());
		switch(opcion)
		{
			case 'A': ingresar_archivo_usuarios();
				break;
			case 'T': ingresar_usuario();
				break;
			default: 
				if((int)opcion != 27)
				{
					cout<<endl<<endl;
					cout<<setw(25)<<"Opcion no valida! ";
					getch();					
				}
				break;
		}
	}while((int)opcion != 27);	
}
//funcion para ingresar desde archivo
void ingresar_archivo_usuarios(void)
{
	//apertura del archivo
	char ruta[USU_BUFFER];
	cout<<endl<<endl;
	cout<<setw(25)<<"Path del archivo CSV? ";
	cin.getline(ruta,USU_BUFFER);
	//buffer de entrada
	char fila[USU_BUFFER];
	//archivo
	fstream archivo;
	archivo.open(ruta,ios::in);
	if(archivo.fail())
	{		
		cout<<setw(25);
		imprimir_error(ARCH_NO_LEER);
		archivo.close();
		return;
	}
	unsigned long n = 0;
	unsigned long pos;
	//leer el archivo texto
	while(archivo.getline(fila,USU_BUFFER,'\n') != NULL)
	{
		if(strcmp(fila,"") != 0)
		{
			datos_usuario data;
			data = obtener_usuario(fila);
			if(!buscar_usuario(data,pos))
			{
				usuario* usu = new usuario();
				usu->copiar(data);
				usu->escribir();
				n++;//leidos
			}
		}
	}
	//cierre del archivo
	archivo.close();
	//se ingresaron los datos
	cout<<endl;
	cout<<setw(25)<<"Datos leidos: "<<n<<"\n\n";
	system("pause");
}
//permite dividir la cadena en campos diferentes
datos_usuario obtener_usuario(char* fila)
{
	char campo[USU_CAMPOS][USU_MAX];	
	unsigned short indices[USU_CAMPOS];
	unsigned short n = 0;	
	unsigned short j = 0;
	unsigned short c = 0;
	unsigned short longitud = strlen(fila);
	//todos los caracteres de la linea recorridos
	for(j=0; j<longitud; j++)
		if(fila[j] == ';')
			indices[n++] = j;
	indices[n++] = j;
	//dato de devolucion	
	if(n != USU_CAMPOS)
	{
		cout<<setw(25);
		imprimir_error(ARCH_USU_NO_COMPLETO);
		datos_usuario data;
		return data;
	}
	//recorro los indices
	for(unsigned short i=0; i<n; i++)
	{
		unsigned short inicio = 0;
		if(i>0)
			inicio = indices[i-1] + 1;
		//llenado de campos
		c = 0;	
		for(j=inicio; j<indices[i]; j++)
		{
			campo[i][c] = fila[j];
			c++;
			if(i==USU_NOMBRE && c==USU_MAX_NOMBRE-1)
				break;
			if(i==USU_CLAVE && c==USU_MAX_CLAVE-1)
				break;
		}
		campo[i][c] = '\0';			
	}
	datos_usuario data;
	//nombre del usuario
	strcpy(data.nombre,campo[USU_NOMBRE]);	
	//clave del usuario
	strcpy(data.clave,campo[USU_CLAVE]);	
	//permisos
	for(unsigned short i=0; i<USU_PERMISOS; i++)
		for(unsigned short j=0; j<USU_CLASES; j++)
			data.permisos[i][j] = false;
	//validar el objeto
	data.valido = true;
	//todos los datos han sido ingresados
	return data;
}
//funcion para ingresar desde teclado
void ingresar_usuario(void)
{
	do
	{
		usuario* usu = new usuario();
		usu->ingresar();
		usu->escribir();//retorna error
		//ingresar mas estudiantes
		cout<<endl;
		cout<<setw(25)<<"Nuevo usuario [s/n] ? ";
	}while(ingresar_sn());	
}
//FUNCIONES DE USUARIO PARA REPORTE
//funcion para imprimir el archivo de usuarios
void imprimir_usuarios(void)//MENU
{	
	unsigned long total = 0;
	//ubicar el total de los elementos
	//0 .. total-1
	total = total_usuarios();
	if(total == 0)
		return;
	unsigned long pos = 0;
	char opcion = '*';
	do
	{		
		system("cls");
		cout<<"\n\t\tIMPRIMIR USUARIO\n";
		usuario* usu = new usuario();
		usu->leer(pos);//retorna error
		cout<<endl;
		usu->imprimir();
		cout<<endl;
		cout<<setw(25)<<""<<"TECLA\n";
		cout<<setw(25)<<"Primero: "		<<"[ARRIBA]\n";
		cout<<setw(25)<<"Anterior: "	<<"[IZQUIERDA]\n";
		cout<<setw(25)<<"Siguiente: "	<<"[DERECHA]\n";
		cout<<setw(25)<<"Ultimo: "		<<"[ABAJO]\n\n";
		cout<<setw(25)<<"Retornar: "	<<"[ESC]\n\n";
		cout<<setw(25)<<"Elija una opcion? ";
		opcion = getch();
		ungetch(opcion);
		opcion = getch();
		switch(opcion)
		{
			case 'H': 
				pos = 0;
			break;
			case 'K': 
				if(pos > 0)
					pos--;
			break;
			case 'M':
				if(pos < (total - 1))
					pos++;
			break;
			case 'P': 
				pos = total - 1;
			break;
			default: 
				if((int)opcion != 27)
				{
					cout<<endl<<endl;
					cout<<setw(25)<<"Opcion no valida! ";
					getch();					
				}
			break;
		}
	}while((int)opcion != 27);
}
//FUNCIONES DE USUARIO PARA BUSQUEDA
//funcion para buscar usuarios
void buscar_usuarios(void)//MENU DE BUSQUEDAS
{
	system("cls");
	cout<<"\n\t\tBUSCAR USUARIO\n\n";
	datos_usuario data;
	//ingresar el nombre
	cout<<setw(25)<<"Nombre? ";
	cin.getline(data.nombre,USU_MAX_NOMBRE);
	unsigned long pos;
	if(buscar_usuario(data,pos))
	{
		usuario* usu = new usuario();
		usu->copiar(data);
		cout<<endl;
		usu->imprimir();
	}
	else
	{
		cout<<setw(25);
		imprimir_error(USU_NO_ENCONTRADO);
	}
	cout<<endl;
	system("pause");
}
//funcion para buscar un usuario en el archivo
bool buscar_usuario(datos_usuario &data, unsigned long &pos)
{
	//archivo
	fstream archivo;
	archivo.open("datos_usuarios.dat",ios::in|ios::binary);	
	if(archivo.fail())
		return false;
	pos = 0;
	datos_usuario cab;
	archivo.seekp(pos*sizeof(datos_usuario),ios::beg);
	archivo.read((char*)&cab,sizeof(datos_usuario));
	while(!archivo.eof())
	{
		usuario* usu = new usuario();
		usu->copiar(cab);
		if(usu->comparar(data))
		{
			usu->copiar_en(data);
			archivo.close();
			return true;
		}
		//leo el siguiente dato
		pos++;
		archivo.seekp(pos*sizeof(datos_usuario),ios::beg);
		archivo.read((char*)&cab,sizeof(datos_usuario));
	}
	//cierre del archivo
	archivo.close();
	return false;
}
//FUNCIONES DE USUARIO PARA MODIFICACION
//funcion para modificar estudiantes
void modificar_usuarios(void)//MENU DE MODIFICACIONES
{
	system("cls");
	cout<<"\n\t\tMODIFICAR USUARIO\n\n";
	datos_usuario data;
	//ingresar el nombre
	cout<<setw(25)<<"Nombre? ";
	cin.getline(data.nombre,USU_MAX_NOMBRE);
	unsigned long pos;
	if(buscar_usuario(data,pos))
	{
		usuario* usu = new usuario();
		usu->copiar(data);
		cout<<endl;
		usu->modificar();
		usu->escribir(pos);
	}
	else
	{
		cout<<setw(25);
		imprimir_error(USU_NO_ENCONTRADO);
	}
	//se ingresaron los datos
	cout<<endl;
	system("pause");
}
//FUNCIONES DE USUARIO PARA ELIMINACION
//funcion para buscar un estudiante
void eliminar_usuarios(void)//MENU DE ELMINACIONES
{
	system("cls");
	cout<<"\n\t\tELIMINAR USUARIO\n\n";
	datos_usuario data;
	//ingresar el nombre
	cout<<setw(25)<<"Nombre? ";
	cin.getline(data.nombre,USU_MAX_NOMBRE);
	unsigned long pos;
	cout<<endl;
	if(buscar_usuario(data,pos))
	{
		usuario* usu = new usuario();
		usu->copiar(data);
		usu->validar(false);
		usu->escribir(pos);
		cout<<data;
	}
	else
	{
		cout<<setw(25);
		imprimir_error(USU_NO_ENCONTRADO);
	}
	//se ingresaron los datos
	cout<<endl;
	system("pause");
}
//FUNCIONES UTILES
//obtencion del total de usuarios en el registro
unsigned long total_usuarios(void)
{
	ifstream archivo;
	archivo.open("datos_usuarios.dat",ios::binary);
	if(archivo.fail())
		return 0;
	//lee el total de archivos
	unsigned long n = 0;
	datos_usuario data;
	archivo.read((char*)&data,sizeof(datos_usuario));
	while(!archivo.eof())
	{
		n++;
		archivo.read((char*)&data,sizeof(datos_usuario));
	}
	archivo.close();	
	return n;
}
//verifica que existan datos invalidos
unsigned long usuarios_no_validos(void)
{
	ifstream archivo;
	archivo.open("datos_usuarios.dat",ios::binary);
	if(archivo.fail())
		return 0;
	//lee el total de archivos
	unsigned long n = 0;
	datos_usuario data;
	archivo.read((char*)&data,sizeof(datos_usuario));
	while(!archivo.eof())
	{
		if(!data.valido)
			n++;
		archivo.read((char*)&data,sizeof(datos_usuario));
	}
	archivo.close();
	return n;
}
//ARCHIVOS
//verifica que existan datos invalidos
void guardar_usuarios(void)
{
	//archivo de lectura
	ifstream archivo;
	archivo.open("datos_usuarios.dat",ios::binary);
	if(archivo.fail())
	{
		cout<<setw(25);
		imprimir_error(ARCH_NO_LEER);
		return;
	}
	//archivo de escritura
	ofstream temporal;
	temporal.open("temporal.dat",ios::app|ios::binary);
	if(temporal.fail())
	{
		cout<<setw(25);
		imprimir_error(ARCH_NO_ESCRIBIR);
		archivo.close();
		return;
	}
	//datos validos
	unsigned long pos = 0;
	datos_usuario data;
	archivo.read((char*)&data,sizeof(datos_usuario));
	while(!archivo.eof())
	{
		if(data.valido)
			temporal.write((char*)&data,sizeof(datos_usuario));
		archivo.read((char*)&data,sizeof(datos_usuario));
	}
	//datos escritos
	archivo.close();
	temporal.close();
	//cambio de nombre
	remove("datos_usuarios.dat");
	rename("temporal.dat","datos_usuarios.dat");
}
