//interfaces de las clases
#include "libros.h"
using namespace std;
//FUNCIONES DE CLASE
//constructor de la clase libro
libro::libro(void)
{
	//datos de busqueda
	strcpy(datos.codigo,"");
	//datos de identificacion
	strcpy(datos.nombre,"");
	for(unsigned short j=0; j<MAX_AUTOR; j++)
		strcpy(datos.autor[j],"");
	//datos auxiliares
	datos.copias = 0;
	datos.edicion = 0;
	fecha* fec = new fecha();
	fec->copiar_en(datos.fecha_pub);	
	strcpy(datos.editorial,"");
	//datos de clasificacion
	strcpy(datos.categoria,"");
	datos.disponible = false;
	//datos del objeto
	datos.valido = false;
}
//FUNCIONES DE CLASE DE ARCHIVO
//cargar los datos de los libros en la estructura de datos
unsigned short libro::leer(unsigned long pos)
{
	ifstream archivo;
	archivo.open("datos_libros.dat",ios::binary);
	if(archivo.fail())
		return ARCH_NO_LEER;
	archivo.seekg(pos*sizeof(datos_libro),ios::beg);
	archivo.read((char*)&datos,sizeof(datos_libro));
	archivo.close();
	return 0;
}
//guardar los datos de los libros en un archivo
unsigned short libro::escribir()
{
	ofstream archivo;
	//se abre el archivo para escritura, añadidura y binario
	archivo.open("datos_libros.dat",ios::app|ios::binary);
	//el archivo no existe se crea
	if(archivo.bad())
		archivo.open("datos_libros.dat");
	archivo.write((char*)&datos,sizeof(datos_libro));
	archivo.close();
	return 0;
}
//modificar los datos de los estudiantes en un archivo
unsigned short libro::escribir(unsigned long pos)
{
	fstream archivo;
	archivo.open("datos_libros.dat",ios::in|ios::out|ios::binary);
	if(archivo.fail())
		return ARCH_NO_ESCRIBIR;
	archivo.seekp(pos*sizeof(datos_libro),ios::beg);
	archivo.write((char*)&datos,sizeof(datos_libro));
	archivo.close();
	return 0;
}
//FUNCIONES DE CLASE DE INGRESO
//ingreso por copia de datos en la clase libro
void libro::copiar(datos_libro data)
{
	//datos de busqueda
	strcpy(datos.codigo,data.codigo);
	//datos de identificacion
	strcpy(datos.nombre,data.nombre);
	for(unsigned short j=0; j<MAX_AUTOR; j++)
		strcpy(datos.autor[j],data.autor[j]);
	//datos auxiliares
	datos.copias = data.copias;
	datos.edicion = data.edicion;
	fecha* fec = new fecha();
	fec->ingresar(data.fecha_pub);
	fec->copiar_en(datos.fecha_pub);	
	strcpy(datos.editorial,data.editorial);
	//datos de clasificacion
	strcpy(datos.categoria,data.categoria);
	datos.disponible = data.disponible;
	//datos del objeto
	datos.valido = data.valido;
}
//ingreso de datos desde teclado
void libro::ingresar(void)
{
	//ingresar la cedula
	unsigned short n;
	bool encontrado;
	//hasta tener una codigo valido
	system("cls");
	cout<<"\n\t\tDATOS DEL LIBRO\n\n";
	do
	{
		cout<<setw(25)<<"Codigo? ";
		strcpy(datos.codigo,ingresar_numero("#####"));
		//validar el codigo ingresado
		n = validar_codigo(datos.codigo);
		if(n > 0)
		{
			cout<<setw(25);
			imprimir_error(n);
		}
		//determina si ya existe el estudiante
		unsigned long pos;
		encontrado = buscar_libro(datos,pos);
		if(encontrado)
		{
			cout<<setw(25);
			imprimir_error(LIB_YA_EXISTE);
		}
	}while(n > 0 || encontrado);
	cout<<endl;
	//ingresar el nombre del libro
	cout<<setw(25)<<"Nombre? ";
	cin.getline(datos.nombre,LIB_MAX_NOMBRE);
	//ingresar el autor del libro
	for(unsigned short j=0; j<MAX_AUTOR; j++)
		strcpy(datos.autor[j],"NULL");
	bool otro = true;
	n = 0;
	do
	{
		cout<<setw(25)<<"Nombre del Autor? ";
		cin.getline(datos.autor[n++],LIB_MAX_AUTOR);	
		//otro autor
		if(n < MAX_AUTOR)
		{
			cout<<setw(25)<<"Otro Autor [s/n]? ";
			otro = ingresar_sn();
			cout<<endl;
		}
	}while(n < MAX_AUTOR && otro == true);
	//numero de copia del libro
	cout<<setw(25)<<"No. de Copias? ";	
	datos.copias = ingresar_numero(1,99);
	cout<<endl;
	//numero de edicion del libro
	cout<<setw(25)<<"No. de Edicion? ";
	datos.edicion = ingresar_numero(1,99);
	cout<<endl;
	//fecha de publicacion
	cout<<setw(25)<<"Fecha de Publicacion? ";
	fecha* fec = new fecha();
	fec->ingresar();
	fec->copiar_en(datos.fecha_pub);
	cout<<endl;
	//editorial del libro
	cout<<setw(25)<<"Editorial? ";
	cin.getline(datos.editorial,LIB_MAX_EDITORIAL);
	//categoria del libro
	cout<<setw(25)<<"Categoria? ";
	cin.getline(datos.categoria,LIB_MAX_CATEGORIA);
	//disponible
	cout<<setw(25)<<"Disponible [s/n]? ";
	datos.disponible = ingresar_sn();
	cout<<endl;
	//validar el objeto
	datos.valido = true;		
}
//FUNCIONES DE CLASE DE REPORTE
//imprime los datos
ostream& operator << (ostream& co, const datos_libro &a)
{
	co<<setw(25)<<"Codigo: "			<<a.codigo<<endl;
	co<<setw(25)<<"Nombre: "			<<a.nombre<<endl;
	for(unsigned short j=0; j<MAX_AUTOR; j++)
		co<<setw(25)<<"Autor: "			<<a.autor[j]<<endl;
	co<<setw(25)<<"No. de Copias: "		<<a.copias<<endl;
	co<<setw(25)<<"No. de Edicion: "	<<a.edicion<<endl;	
	co<<setw(25)<<"Publicado el: "		<<a.fecha_pub<<endl;	
	co<<setw(25)<<"Editorial: "			<<a.editorial<<endl;
	co<<setw(25)<<"Categoria: "			<<a.categoria<<endl;
	co<<setw(25)<<"Disponible: "		<<boolalpha<<a.disponible<<endl;
	co<<setw(25)<<"Valido: "			<<boolalpha<<a.valido<<endl;	
}
//ingreso de datos en la clase libro
void libro::copiar_en(datos_libro &data)
{
	//datos de busqueda
	strcpy(data.codigo,datos.codigo);
	//datos de identificacion
	strcpy(data.nombre,datos.nombre);
	for(unsigned short j=0; j<MAX_AUTOR; j++)
		strcpy(data.autor[j],datos.autor[j]);
	//datos auxiliares
	data.copias = datos.copias;
	data.edicion = datos.edicion;
	fecha* fec = new fecha();
	fec->ingresar(datos.fecha_pub);
	fec->copiar_en(data.fecha_pub);
	strcpy(data.editorial,datos.editorial);
	//datos de clasificacion
	strcpy(data.categoria,datos.categoria);
	data.disponible = datos.disponible;
	//datos del objeto
	data.valido = datos.valido;
}
//imprime los datos del libro
void libro::imprimir(void)
{
	if(datos.valido)
	{
		cout<<setw(25)<<"Codigo: "			<<datos.codigo<<endl;
		cout<<setw(25)<<"Nombre: "			<<datos.nombre<<endl;
		for(unsigned short j=0; j<MAX_AUTOR; j++)
			if(strcmp(datos.autor[j],"NULL") != 0 )
				cout<<setw(25)<<"Autor: "	<<datos.autor[j]<<endl;
		//datos numericos
		cout<<setw(25)<<"No. de Copias: "	<<datos.copias<<endl;
		cout<<setw(25)<<"No. de Edicion: "	<<datos.edicion<<endl;
		//fecha de publicacion
		cout<<setw(25)<<"Publicado el: "	<<datos.fecha_pub.completa<<endl;
		cout<<setw(25)<<"Editorial: "		<<datos.editorial<<endl;
		//datos auxiliares
		cout<<setw(25)<<"Categoria: "		<<datos.categoria<<endl;
		cout<<setw(25)<<"Disponible: ";
		cout<<(datos.disponible==true?"Si":"No")<<endl;	
	}
}
//FUNCIONES DE CLASE DE BUSQUEDA
//busca un libro dados los datos
bool libro::comparar(datos_libro data)
{
	return datos == data;
}
//FUNCIONES DE CLASE DE MODIFICACION
//busca un libro dados los datos
void libro::modificar(void)
{
	//hasta tener una cedula valida
	cout<<setw(25)<<"Codigo: "<<datos.codigo<<endl;
	//ingresar el nombre
	cout<<setw(25)<<"Nombre: "<<datos.nombre<<endl;
	cout<<setw(25)<<"Conservar [s/n]? ";
	if(!ingresar_sn())
	{
		cout<<endl;
		cout<<setw(25)<<"Nombre? ";
		cin.getline(datos.nombre,LIB_MAX_NOMBRE);
	}
	else
		cout<<endl;
	//ingresar el autor del libro
	for(unsigned short j=0; j<MAX_AUTOR; j++)
	{
		cout<<setw(25)<<"Autor: "<<datos.autor[j]<<endl;
		cout<<setw(25)<<"Conservar [s/n]? ";
		if(!ingresar_sn())
		{
			cout<<endl;
			cout<<setw(25)<<"Nombre del Autor? ";
			cin.getline(datos.autor[j],LIB_MAX_AUTOR);			
		}
		else
			cout<<endl;
	}
	//numero de copia del libro
	cout<<setw(25)<<"No. de Copias: "<<datos.copias<<endl;
	cout<<setw(25)<<"Conservar [s/n]? ";
	if(!ingresar_sn())
	{
		cout<<endl;
		cout<<setw(25)<<"No. de Copias? ";		
		datos.copias = ingresar_numero(1,99);
		cout<<endl;	
	}
	else
		cout<<endl;
	//numero de edicion del libro
	cout<<setw(25)<<"No. de Edicion: ";
	cout<<datos.edicion<<endl;
	cout<<setw(25)<<"Conservar [s/n]? ";
	if(!ingresar_sn())
	{
		cout<<endl;
		cout<<setw(25)<<"No. de Edicion? ";
		datos.edicion = ingresar_numero(1,99);
		cout<<endl;
	}
	else
		cout<<endl;
	//fecha de publicacion
	cout<<setw(25)<<"Fecha de Publicacion: ";
	cout<<datos.fecha_pub.aaaammdd<<endl;
	cout<<setw(25)<<"Conservar [s/n]? ";
	if(!ingresar_sn())
	{
		cout<<endl;
		cout<<setw(25)<<"Fecha de Publicacion? ";
		fecha* fec = new fecha();
		fec->ingresar();
		fec->copiar_en(datos.fecha_pub);
		cout<<endl;
	}
	else
		cout<<endl;
	//editorial del libro
	cout<<setw(25)<<"Editorial: ";
	cout<<datos.editorial<<endl;
	cout<<setw(25)<<"Conservar [s/n]? ";
	if(!ingresar_sn())
	{
		cout<<endl;
		cout<<setw(25)<<"Editorial? ";
		cin.getline(datos.editorial,20);
	}
	else
		cout<<endl;
	//categoria del libro
	cout<<setw(25)<<"Categoria: ";
	cout<<datos.categoria<<endl;
	cout<<setw(25)<<"Conservar [s/n]? ";
	if(!ingresar_sn())
	{
		cout<<endl;
		cout<<setw(25)<<"Categoria? ";	
		cin.getline(datos.categoria,20);	
	}
	else
		cout<<endl;
	//esta disponible
	cout<<setw(25)<<"Diponible: ";
	cout<<(datos.disponible==true?"Si":"No")<<endl;
	cout<<setw(25)<<"Conservar [s/n]? ";
	if(!ingresar_sn())
	{
		cout<<endl;
		cout<<setw(25)<<"Disponible [s/n]? ";
		datos.disponible = ingresar_sn();
		cout<<endl;
	}
	cout<<endl;
	//validar el objeto
	datos.valido = true;	
}
//FUNCIONES DE CLASE PARA ELIMINACION
//eliminar los datos de la estructura de datos
void libro::validar(bool valor)
{
	datos.valido = valor;
}
//FUNCIONES DE CLASE SOBRECARGADAS
// operador friend de test de igualdad sobrecargado
bool operator== (const datos_libro& a, const datos_libro& b)
{
	for(int i=0; i<MAX_CODIGO; i++)
		if(a.codigo[i] != b.codigo[i])
			return false;
	return true;
}
//FUNCIONES DE USUARIO
//funcion para imprimir el menu del estudiante
void menu_libro(usuario* usu)
{
	char opcion = '*';
	do
	{
		system("cls");
		cout<<"\n\t\t\tLIBROS\n\n";
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
				if(usu->permiso_escribir(USU_LIBRO))
					ingresar_libros();
				break;
			case 'B': 
				buscar_libros();
				break;
			case 'P': 
				imprimir_libros();
				break;
			case 'M':
				if(usu->permiso_escribir(USU_LIBRO))
					modificar_libros();
				break; 
			case 'E':
				if(usu->permiso_escribir(USU_LIBRO))
					eliminar_libros();
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
					n = libros_no_validos();
					if(n > 0)
					{
						cout<<setw(25)<<"Datos no validos: "<<n<<endl;
						//verificación de salida
						cout<<endl;
						cout<<setw(25)<<"Desea eliminarlos [s/n]? ";
						if(ingresar_sn())
							guardar_libros();
					}
				}
				break;
		}
	}while((int)opcion != 27);	
}
//FUNCIONES DE USUARIO DE INGRESO
//ingreso de datos en la clase
void ingresar_libros(void)//MENU DE ALTAS
{
	char opcion = '*';
	do
	{
		system("cls");
		cout<<"\n\t\tINGRESAR LIBRO\n\n";
		cout<<setw(25)<<""<<"TECLA\n";
		cout<<setw(25)<<"Archivo: "		<<"[a/A]\n";
		cout<<setw(25)<<"Teclado: "		<<"[t/T]\n\n";
		cout<<setw(25)<<"Retornar: "	<<"[ESC]\n\n";
		cout<<setw(25)<<"Elija una opcion? ";
		opcion = toupper(getche());
		switch(opcion)
		{
			case 'A': ingresar_archivo_libros();
				break;
			case 'T': ingresar_libro();
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
void ingresar_archivo_libros(void)
{
	//apertura del archivo
	char ruta[LIB_BUFFER];
	cout << endl << endl;
	cout << setw(25) << "Path del archivo CSV? ";
	cin.getline(ruta,LIB_BUFFER);
	//buffer de entrada
	char fila[LIB_BUFFER];
	//archivo
	fstream archivo;
	archivo.open(ruta, ios::in);	
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
	while(archivo.getline(fila,LIB_BUFFER,'\n') != NULL)
	{
		if(strcmp(fila,"") != 0)
		{		
			datos_libro data;
			data = obtener_libro(fila);
			if(!buscar_libro(data,pos))
			{
				libro* lib = new libro();
				lib->copiar(data);
				lib->escribir();
				n++;
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
datos_libro obtener_libro(char* fila)
{
	char campo[LIB_CAMPOS][LIB_MAX];	
	unsigned short indices[LIB_CAMPOS];
	unsigned short n = 0;	
	unsigned short j = 0;
	unsigned short c = 0;
	unsigned short longitud = strlen(fila);
	//todos los caracteres de la linea recorridos
	for(j=0; j<longitud; j++)
		if(fila[j] == ';')
			indices[n++] = j;
	indices[n++] = j;
	if(n != LIB_CAMPOS)
	{
		cout<<setw(25);
		imprimir_error(ARCH_LIB_NO_COMPLETO);
		datos_libro data;
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
			if(i==LIB_CODIGO && c==LIB_MAX_CODIGO-1)
				break;
			if(i==LIB_NOMBRE && c==LIB_MAX_NOMBRE-1)
				break;
			if(i==LIB_AUTOR_1 && c==LIB_MAX_AUTOR-1)
				break;
			if(i==LIB_AUTOR_2 && c==LIB_MAX_AUTOR-1)
				break;
			if(i==LIB_AUTOR_3 && c==LIB_MAX_AUTOR-1)
				break;
			if(i==LIB_FECHA_PUB && c==FEC_MAX)
				break;
			if(i==LIB_EDITORIAL && c==LIB_MAX_EDITORIAL-1)
				break;
			if(i==LIB_CATEGORIA && c==LIB_MAX_CATEGORIA-1)
				break;
		}
		campo[i][c] = '\0';			
	}
	//verifico que sea una cedula valida
	int k;
	k = validar_codigo(campo[0]);
	if(k > 0)
	{
		cout<<setw(25);
		imprimir_error(k);
		datos_libro data;
		return data;
	}
	datos_libro data;
	//numero de codigo valido
	strcpy(data.codigo,campo[LIB_CODIGO]);	
	//nombre del libro
	strcpy(data.nombre,campo[LIB_NOMBRE]);
	//autores del libro			
	strcpy(data.autor[0],campo[LIB_AUTOR_1]);
	strcpy(data.autor[1],campo[LIB_AUTOR_2]);
	strcpy(data.autor[2],campo[LIB_AUTOR_3]);
	//copia del libro
	n = 0;
	for(unsigned short i=0; i<strlen(campo[LIB_COPIA]); i++)
		n = 10 * n + (campo[LIB_COPIA][i] - '0');
	data.copias = n;			
	//numero de edicion del libro
	n = 0;
	for(unsigned short i=0; i<strlen(campo[LIB_EDICION]); i++)
		n = 10 * n + (campo[LIB_EDICION][i] - '0');
	data.edicion = n;
	//fecha de publicacion
	fecha* fec = new fecha();
	fec->ingresar_mmddaaaa(campo[LIB_FECHA_PUB]);
	fec->copiar_en(data.fecha_pub);
	//editorial del libro
	strcpy(data.editorial,campo[LIB_EDITORIAL]);			
	//categoria a la que pertenece
	strcpy(data.categoria,campo[LIB_CATEGORIA]);
	//disponible
	n = 0;
	for(unsigned short i=0; i<strlen(campo[LIB_DISPONIBLE]); i++)
		n = 10 * n + (campo[LIB_DISPONIBLE][i] - '0');
	data.disponible = n==1?true:false;
	//validar el objeto
	data.valido = true;
	//todos los datos han sido ingresados
	return data;
}
//funcion para ingresar desde teclado
void ingresar_libro(void)
{
	do
	{
		libro* lib = new libro();
		lib->ingresar();		
		lib->escribir();//retorna error
		//ingresar mas estudiantes
		cout<<endl;
		cout<<setw(25)<<"Nuevo libro [s/n] ? ";
	}while(ingresar_sn());	
}
//FUNCIONES DE USUARIO DE REPORTE
//funcion para imprimir el archivo de libros
void imprimir_libros(void)//MENU
{
	unsigned long total = 0;
	//ubicar el total de los elementos
	//0 .. total-1
	total = total_libros();
	if(total == 0)
		return;
	unsigned long pos = 0;
	char opcion = '*';
	do
	{
		system("cls");
		cout<<"\n\t\tIMPRIMIR LIBRO\n";
		libro* lib = new libro();
		lib->leer(pos);//retorna error
		cout<<endl;
		lib->imprimir();
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
			case 'H': pos = 0;
			break;
			case 'K': 
				if(pos > 0)
					pos--;
			break;
			case 'M':
				if(pos < (total - 1))
					pos++;
			break;
			case 'P': pos = total - 1;
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
//FUNCIONES DE USUARIO DE BUSQUEDA
//funcion para buscar libros
void buscar_libros(void)//MENU DE BUSQUEDAS
{
	system("cls");
	cout<<"\n\t\tBUSCAR LIBRO\n\n";
	datos_libro data;
	unsigned short n = 0;
	do
	{
		cout<<setw(25)<<"Codigo? ";
		strcpy(data.codigo,ingresar_numero("#####"));
		//validar la codigo ingresada
		n = validar_codigo(data.codigo);
		if(n > 0)
		{
			cout<<setw(25);
			imprimir_error(n);
		}
	}while(n > 0);
	//codigo valida
	cout<<endl;
	unsigned long pos;
	if(buscar_libro(data,pos))
	{
		libro* lib = new libro();
		lib->copiar(data);
		cout<<endl;
		lib->imprimir();
	}
	else
	{
		cout<<setw(25);
		imprimir_error(LIB_NO_ENCONTRADO);
	}
	//se ingresaron los datos
	cout<<endl;
	system("pause");
}
//funcion para buscar un libro en el archivo
bool buscar_libro(datos_libro &data, unsigned long &pos)
{
	//archivo
	fstream archivo;
	archivo.open("datos_libros.dat",ios::in|ios::binary);	
	if(archivo.fail())
		return false;
	pos = 0;
	datos_libro cab;
	archivo.seekp(pos*sizeof(datos_libro),ios::beg);
	archivo.read((char*)&cab,sizeof(datos_libro));
	while(!archivo.eof())
	{
		libro* lib = new libro();
		lib->copiar(cab);
		if(lib->comparar(data))
		{
			lib->copiar_en(data);
			archivo.close();
			return true;
		}
		//leo el siguiente dato
		pos++;
		archivo.seekp(pos*sizeof(datos_libro),ios::beg);
		archivo.read((char*)&cab,sizeof(datos_libro));
	}
	//cierre del archivo
	archivo.close();
	return false;
}
//FUNCIONES DE USUARIO DE MODIFICACION
//funcion para modificar libros
void modificar_libros(void)//MENU DE MODIFICACIONES
{
	system("cls");
	cout<<"\n\t\tMODIFICAR LIBRO\n\n";
	datos_libro data;
	unsigned short n = 0;
	do
	{
		cout<<setw(25)<<"Codigo? ";
		strcpy(data.codigo,ingresar_numero("#####"));
		//validar la codigo ingresada
		n = validar_codigo(data.codigo);
		if(n > 0)
		{
			cout<<setw(25);
			imprimir_error(n);
		}
	}while(n > 0);
	//codigo valida
	unsigned long pos;
	cout<<endl;
	if(buscar_libro(data,pos))
	{
		libro* lib = new libro();
		lib->copiar(data);
		cout<<endl;
		lib->modificar();
		lib->escribir(pos);
	}
	else
	{
		cout<<setw(25);
		imprimir_error(LIB_NO_ENCONTRADO);
	}	
	//se ingresaron los datos
	cout<<endl;
	system("pause");
}
//FUNCIONES DE USUARIO DE ELIMINACION
//funcion para buscar un libro
void eliminar_libros(void)//MENU DE ELMINACIONES
{
	system("cls");
	cout<<"\n\t\tELIMINAR LIBRO\n\n";
	datos_libro data;
	unsigned short n = 0;
	do
	{
		cout<<setw(25)<<"Codigo? ";
		strcpy(data.codigo,ingresar_numero("#####"));
		//validar la codigo ingresada
		n = validar_codigo(data.codigo);
		if(n > 0)
		{
			cout<<setw(25);
			imprimir_error(n);
		}
	}while(n > 0);
	//codigo valida
	unsigned long pos;
	cout<<endl;
	if(buscar_libro(data,pos))
	{
		libro* lib = new libro();
		lib->copiar(data);
		lib->validar(false);
		lib->escribir(pos);
		cout<<endl;
		cout<<data;
	}
	else
	{
		cout<<setw(25);
		imprimir_error(LIB_NO_ENCONTRADO);
	}
	//se ingresaron los datos
	cout<<endl;
	system("pause");
}
//FUNCIONES UTILES
//obtencion del total de estudiantes en el registro
unsigned long total_libros(void)
{
	ifstream archivo;
	archivo.open("datos_libros.dat",ios::binary);
	if(archivo.fail())
		return 0;
	//lee el total de archivos
	unsigned long n = 0;
	datos_libro data;
	archivo.read((char*)&data,sizeof(datos_libro));
	while(!archivo.eof())
	{
		n++;
		archivo.read((char*)&data,sizeof(datos_libro));
	}
	archivo.close();	
	return n;
}
//verifica que existan datos invalidos
unsigned long libros_no_validos(void)
{
	ifstream archivo;
	archivo.open("datos_libros.dat",ios::binary);
	if(archivo.fail())
		return 0;
	//lee el total de archivos
	unsigned long n = 0;
	datos_libro data;
	archivo.read((char*)&data,sizeof(datos_libro));
	while(!archivo.eof())
	{
		if(!data.valido)
			n++;
		archivo.read((char*)&data,sizeof(datos_libro));
	}
	archivo.close();
	return n;	
}
//ARCHIVOS
//verifica que existan datos invalidos
void guardar_libros(void)
{
	//archivo de lectura
	ifstream archivo;
	archivo.open("datos_libros.dat",ios::binary);
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
	datos_libro data;
	archivo.read((char*)&data,sizeof(datos_libro));
	while(!archivo.eof())
	{
		if(data.valido)
			temporal.write((char*)&data,sizeof(datos_libro));
		archivo.read((char*)&data,sizeof(datos_libro));
	}
	//datos escritos
	archivo.close();
	temporal.close();
	//cambio de nombre
	remove("datos_libros.dat");
	rename("temporal.dat","datos_libros.dat");
}
