//interfaces de las clases
#include "prestamos.h"
using namespace std;
//FUNCIONES DE CLASE
//constructor de la clase prestamo
prestamo::prestamo(void)
{
	strcpy(datos.cedula,"");
	strcpy(datos.codigo,"");
	fecha* fec = new fecha();
	fec->copiar_en(datos.fecha_pre);
	fec->copiar_en(datos.fecha_ent);
	strcpy(datos.nota,"");
	//validar los datos
	datos.valido = false;
}
//FUNCIONES DE CLASE DE ARCHIVO
//cargar los datos de los prestamos en la estructura de datos
unsigned short prestamo::leer(unsigned long pos)
{
	ifstream archivo;
	archivo.open("datos_prestamos.dat",ios::binary);
	if(archivo.fail())
		return ARCH_NO_LEER;
	archivo.seekg(pos*sizeof(datos_prestamo),ios::beg);
	archivo.read((char*)&datos,sizeof(datos_prestamo));
	archivo.close();
	return 0;
}
//guardar los datos de los prestamos en un archivo
unsigned short prestamo::escribir()
{
	ofstream archivo;
	//se abre el archivo para escritura, añadidura y binario
	archivo.open("datos_prestamos.dat",ios::app|ios::binary);
	//el archivo no existe se crea
	if(archivo.bad())
		archivo.open("datos_prestamos.dat");
	archivo.write((char*)&datos,sizeof(datos_prestamo));
	archivo.close();
	return 0;
}
//modificar los datos de los prestamos en un archivo
unsigned short prestamo::escribir(unsigned long pos)
{
	fstream archivo;
	archivo.open("datos_prestamos.dat",ios::in|ios::out|ios::binary);
	if(archivo.fail())
		return ARCH_NO_ESCRIBIR;
	archivo.seekp(pos*sizeof(datos_prestamo),ios::beg);
	archivo.write((char*)&datos,sizeof(datos_prestamo));
	archivo.close();
	return 0;
}
//FUNCIONES DE CLASE DE INGRESO
//ingreso por copia de datos en la clase prestamo
void prestamo::copiar(datos_prestamo data)
{
	strcpy(datos.cedula,data.cedula);
	strcpy(datos.codigo,data.codigo);
	fecha* fec = new fecha();
	fec->ingresar(data.fecha_pre);
	fec->copiar_en(datos.fecha_pre);
	fec->ingresar(data.fecha_ent);
	fec->copiar_en(datos.fecha_ent);
	strcpy(datos.nota,data.nota);
	//validar los datos
	datos.valido = true;
}
//ingreso de datos desde teclado
void prestamo::ingresar(void)
{
	//ingresar la cedula
	unsigned short n;
	//variable para la busqueda
	bool encontrado;
	datos_estudiante est_data;
	system("cls");
	//hasta tener una cedula valida
	cout<<"\n\t\tDATOS DEL ESTUDIANTE\n\n";
	do
	{
		cout<<setw(25)<<"Cedula? ";
		strcpy(est_data.cedula,ingresar_numero("##########"));
		//validar la cedula ingresada
		n = validar_cedula(est_data.cedula);
		if(n > 0)
		{
			cout<<setw(25);
			imprimir_error(n);
		}
		else
		{
			//cedula valida
			//si se encuentra se copia en DATA
			unsigned long est_pos;
			encontrado = buscar_estudiante(est_data,est_pos);
			if(!encontrado)
			{
				cout<<setw(25);
				imprimir_error(EST_NO_ENCONTRADO);
			}
		}
	}while(n > 0 || !encontrado);
	datos_libro lib_data;
	//hasta tener una codigo valido
	cout<<"\n\n\t\tDATOS DEL LIBRO\n\n";
	do
	{
		cout<<setw(25)<<"Codigo? ";
		strcpy(lib_data.codigo,ingresar_numero("#####"));
		//validar el codigo ingresado
		n = validar_codigo(lib_data.codigo);
		if(n > 0)
		{
			cout<<setw(25);
			imprimir_error(n);
		}
		else
		{
			//codigo valida
			//si se encuentra se copia en DATA
			unsigned long lib_pos;
			encontrado = buscar_libro(lib_data,lib_pos);
			if(!encontrado)
			{
				cout<<setw(25);
				imprimir_error(LIB_NO_ENCONTRADO);
			}
		}
	}while(n > 0 || !encontrado);
	cout<<endl<<endl;
	strcpy(datos.cedula,est_data.cedula);
	strcpy(datos.codigo,lib_data.codigo);
	//fecha de prestamo
	cout<<setw(25)<<"Fecha de Prestamo? ";
	fecha* fec = new fecha();
	fec->prestamo();
	fec->copiar_en(datos.fecha_pre);	
	cout<<endl;	
	//fecha de entrega
	cout<<setw(25)<<"Fecha de Entrega? ";
	fec->entrega(datos.fecha_pre);
	fec->copiar_en(datos.fecha_ent);
	cout<<endl;
	//editorial del libro
	cout<<setw(25)<<"Nota? ";
	cin.getline(datos.nota,PRE_MAX_NOTA);
	//validar el objeto
	datos.valido = true;		
}
//FUNCIONES DE CLASE DE REPORTE
//imprime los datos
ostream& operator << (ostream& co, const datos_prestamo &a)
{
	co<<setw(25)<<"Cedula: "		<<a.cedula<<endl;
	co<<setw(25)<<"Codigo: "		<<a.codigo<<endl;		
	co<<setw(25)<<"Prestado el: "	<<a.fecha_pre<<endl;
	co<<setw(25)<<"Entregar el: "	<<a.fecha_ent<<endl;
	co<<setw(25)<<"Nota: "			<<a.nota<<endl;	
	co<<setw(25)<<"Valido: "		<<boolalpha<<a.valido<<endl;	
}
//ingreso de datos en la clase prestamo
void prestamo::copiar_en(datos_prestamo &data)
{
	strcpy(data.cedula,datos.cedula);
	strcpy(data.codigo,datos.codigo);
	fecha* fec = new fecha();
	fec->ingresar(datos.fecha_pre);
	fec->copiar_en(data.fecha_pre);
	fec->ingresar(datos.fecha_ent);
	fec->copiar_en(data.fecha_ent);
	strcpy(data.nota,datos.nota);
	//validar los datos
	data.valido = datos.valido;
}
//imprime los datos del prestamo
void prestamo::imprimir(void)
{
	if(datos.valido)
	{
		cout<<setw(25)<<"Cedula: "		<<datos.cedula<<endl;
		cout<<setw(25)<<"Codigo: "		<<datos.codigo<<endl;
		cout<<setw(25)<<"Prestado el: "	<<datos.fecha_pre.completa<<endl;
		cout<<setw(25)<<"Entregar el: "	<<datos.fecha_ent.completa<<endl;
		if(strcmp(datos.nota,"NULL") != 0)
			cout<<setw(25)<<"Nota: "	<<datos.nota<<endl;
	}
}
//FUNCIONES DE CLASE PARA BUSQUEDA
//busca un estudiante dados los datos
bool prestamo::comparar(datos_estudiante est_data, datos_libro lib_data)
{
	datos_estudiante pre_est_data;
	strcpy(pre_est_data.cedula,datos.cedula);
	datos_libro pre_lib_data;
	strcpy(pre_lib_data.codigo,datos.codigo);
	return est_data == pre_est_data && lib_data == pre_lib_data;
}
//FUNCIONES DE CLASE DE MODIFICACION
//busca un libro dados los datos
void prestamo::modificar(void)
{
	//hasta tener una cedula valida
	cout<<setw(25)<<"Cedula: "<<datos.cedula<<endl;
	//hasta tener una codigo valido
	cout<<setw(25)<<"Codigo: "<<datos.codigo<<endl;
	//fecha de prestamo
	cout<<setw(25)<<"Fecha de Prestamo: "<<datos.fecha_pre.aaaammdd<<endl;
	cout<<setw(25)<<"Conservar [s/n]? ";
	if(!ingresar_sn())
	{
		cout<<endl;
		cout<<setw(25)<<"Fecha de Prestamo? ";	
		fecha* fec_pre = new fecha();
		fec_pre->prestamo();
		fec_pre->copiar_en(datos.fecha_pre);	
		cout<<endl;	
	}
	else
		cout<<endl;
	//fecha de entrega
	cout<<setw(25)<<"Fecha de Entrega: "<<datos.fecha_ent.aaaammdd<<endl;
	cout<<setw(25)<<"Conservar [s/n]? ";
	if(!ingresar_sn())
	{
		cout<<endl;
		cout<<setw(25)<<"Fecha de Entrega? ";
		fecha* fec_ent = new fecha();
		fec_ent->entrega(datos.fecha_pre);
		fec_ent->copiar_en(datos.fecha_ent);
		cout<<endl;
	}
	else
		cout<<endl;
	//notas del prestamo
	cout<<setw(25)<<"Nota: "<<datos.nota<<endl;
	cout<<setw(25)<<"Conservar [s/n]? ";
	if(!ingresar_sn())
	{
		cout<<endl;
		cout<<setw(25)<<"Nota? ";
		cin.getline(datos.nota,PRE_MAX_NOTA);
		cout<<endl;
	}
	else
		cout<<endl<<endl;
	//validar el objeto
	datos.valido = true;
}
//FUNCIONES DE CLASE PARA ELIMINACION
//eliminar los datos de la estructura de datos
void prestamo::validar(bool valor)
{
	datos.valido = valor;
}
//FUNCIONES DE USUARIO
//funcion para imprimir el menu del prestamo
void menu_prestamo(usuario* usu)
{
	char opcion = '*';
	do
	{
		system("cls");
		cout<<"\n\t\t\tPRESTAMOS\n\n";
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
				if(usu->permiso_escribir(USU_PRESTAMO))
					ingresar_prestamos();
				break;
			case 'B': 
				buscar_prestamos();
				break;
			case 'P': 
				imprimir_prestamos();
				break;
			case 'M':
				if(usu->permiso_escribir(USU_PRESTAMO))
					modificar_prestamos();
				break; 
			case 'E':
				if(usu->permiso_escribir(USU_PRESTAMO))
					eliminar_prestamos();
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
					n = prestamos_no_validos();
					if(n > 0)
					{
						cout<<setw(25)<<"Datos no validos: "<<n<<endl;
						//verificación de salida
						cout<<endl;
						cout<<setw(25)<<"Desea eliminarlos [s/n]? ";
						if(ingresar_sn())
							guardar_prestamos();
					}
				}
				break;
		}
	}while((int)opcion != 27);	
}
//FUNCIONES DE USUARIO PARA INGRESO
//ingreso de datos en la clase
void ingresar_prestamos(void)//MENU DE ALTAS
{
	//menu de ingreso de estudiantes
	char opcion = '*';
	do
	{
		system("cls");
		cout<<"\n\t\tINGRESAR PRESTAMO\n\n";
		cout<<setw(25)<<""<<"TECLA\n";
		cout<<setw(25)<<"Archivo: "		<<"[a/A]\n";
		cout<<setw(25)<<"Teclado: "		<<"[t/T]\n\n";
		cout<<setw(25)<<"Retornar: "	<<"[ESC]\n\n";
		cout<<setw(25)<<"Elija una opcion? ";
		opcion = toupper(getche());
		switch(opcion)
		{
			case 'A': ingresar_archivo_prestamos();
				break;
			case 'T': ingresar_prestamo();
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
void ingresar_archivo_prestamos(void)
{
	//apertura del archivo
	char ruta[PRE_BUFFER];
	cout<<endl<<endl;
	cout<<setw(25)<<"Path del archivo CSV? ";
	cin.getline(ruta,PRE_BUFFER);
	//buffer de entrada
	char fila[PRE_BUFFER];
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
	while(archivo.getline(fila,PRE_BUFFER,'\n') != NULL)
	{
		if(strcmp(fila,"") != 0)
		{
			datos_prestamo data;
			data = obtener_prestamo(fila);
			if(!buscar_prestamo(data,pos))
			{
				prestamo* pre = new prestamo();
				pre->copiar(data);
				pre->escribir();
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
datos_prestamo obtener_prestamo(char* fila)
{
	char campo[PRE_CAMPOS][PRE_MAX];	
	unsigned short indices[PRE_CAMPOS];
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
	if(n != PRE_CAMPOS)
	{
		cout<<setw(25);
		imprimir_error(ARCH_PRE_NO_COMPLETO);
		datos_prestamo data;
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
			if(i==PRE_CEDULA && c==MAX_CEDULA)
				break;
			if(i==PRE_CODIGO && c==MAX_CODIGO)
				break;
			if(i==PRE_FECHA_PRE && c==FEC_MAX)
				break;
			if(i==PRE_FECHA_ENT && c==FEC_MAX)
				break;
			if(i==PRE_NOTA && c==PRE_MAX_NOTA-1)
				break;
		}
		campo[i][c] = '\0';			
	}
	//verifico que sea una cedula valida
	int k;
	k = validar_cedula(campo[PRE_CEDULA]);
	if(k > 0)
	{
		cout<<setw(25);
		imprimir_error(k);
		datos_prestamo data;
		return data;
	}
	k = validar_codigo(campo[PRE_CODIGO]);
	if(k > 0)
	{
		cout<<setw(25);
		imprimir_error(k);
		datos_prestamo data;
		return data;
	}
	datos_prestamo data;
	//numero de cedula valida
	strcpy(data.cedula,campo[PRE_CEDULA]);	
	//numero de codigo valido
	strcpy(data.codigo,campo[PRE_CODIGO]);	
	//ingreso de la fecha del prestamo
	fecha* fec_pre = new fecha();
	fec_pre->ingresar_mmddaaaa(campo[PRE_FECHA_PRE]);
	fec_pre->copiar_en(data.fecha_pre);
	//ingreso de la fecha de la entrega
	fecha* fec_ent = new fecha();
	fec_ent->ingresar_mmddaaaa(campo[PRE_FECHA_ENT]);
	fec_ent->copiar_en(data.fecha_ent);
	//ingreso de la direccion
	strcpy(data.nota,campo[PRE_NOTA]);
	//validar el objeto
	data.valido = true;
	//todos los datos han sido ingresados
	return data;
}
//funcion para ingresar desde teclado
void ingresar_prestamo(void)
{
	do
	{
		prestamo* pre = new prestamo();
		pre->ingresar();
		pre->escribir();//retorna error
		//ingresar mas estudiantes
		cout<<endl;
		cout<<setw(25)<<"Nuevo prestamo [s/n] ? ";
	}while(ingresar_sn());	
}
//FUNCIONES DE USUARIO PARA REPORTE
//funcion para imprimir el archivo de estudiantes
void imprimir_prestamos(void)//MENU
{	
	unsigned long total = 0;
	//ubicar el total de los elementos
	//0 .. total-1
	total = total_prestamos();
	if(total == 0)
		return;
	unsigned long pos = 0;
	char opcion = '*';
	do
	{		
		system("cls");
		cout<<"\n\t\tIMPRIMIR PRESTAMO\n";
		prestamo* pre = new prestamo();
		pre->leer(pos);//retorna error
		cout<<endl;
		pre->imprimir();
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
//funcion para buscar prestamos
void buscar_prestamos(void)//MENU DE BUSQUEDAS
{
	system("cls");
	cout<<"\n\t\tBUSCAR PRESTAMO\n\n";
	datos_estudiante est_data;
	unsigned short n = 0;
	do
	{
		cout<<setw(25)<<"Cedula? ";
		strcpy(est_data.cedula,ingresar_numero("##########"));
		//validar la cedula ingresada
		n = validar_cedula(est_data.cedula);
		if(n > 0)
		{
			cout<<setw(25);
			imprimir_error(n);
		}
	}while(n > 0);
	cout<<endl;
	datos_libro lib_data;
	do
	{
		cout<<setw(25)<<"Codigo? ";
		strcpy(lib_data.codigo,ingresar_numero("#####"));
		//validar la codigo ingresada
		n = validar_codigo(lib_data.codigo);
		if(n > 0)
		{
			cout<<setw(25);
			imprimir_error(n);
		}
	}while(n > 0);
	//cedula valida
	datos_prestamo data;
	strcpy(data.cedula,est_data.cedula);
	strcpy(data.codigo,lib_data.codigo);
	cout<<endl;
	unsigned long pos;
	if(buscar_prestamo(data,pos))
	{
		prestamo* pre = new prestamo();
		pre->copiar(data);
		cout<<endl;
		pre->imprimir();
	}
	else
	{
		cout<<setw(25);
		imprimir_error(PRE_NO_ENCONTRADO);
	}
	cout<<endl;
	system("pause");
}
//funcion para buscar un estudiante en el archivo
bool buscar_prestamo(datos_prestamo &data, unsigned long &pos)
{
	//archivo
	fstream archivo;
	archivo.open("datos_prestamos.dat",ios::in|ios::binary);	
	if(archivo.fail())
		return false;
	pos = 0;
	datos_prestamo cab;
	archivo.seekp(pos*sizeof(datos_prestamo),ios::beg);
	archivo.read((char*)&cab,sizeof(datos_prestamo));
	while(!archivo.eof())
	{
		prestamo* pre = new prestamo();
		pre->copiar(cab);
		datos_estudiante est_data;
		strcpy(est_data.cedula,data.cedula);
		datos_libro lib_data;
		strcpy(lib_data.codigo,data.codigo);
		if(pre->comparar(est_data,lib_data))
		{
			pre->copiar_en(data);
			archivo.close();
			return true;
		}
		//leo el siguiente dato
		pos++;
		archivo.seekp(pos*sizeof(datos_prestamo),ios::beg);
		archivo.read((char*)&cab,sizeof(datos_prestamo));
	}
	//cierre del archivo
	archivo.close();
	return false;
}
//FUNCIONES DE USUARIO PARA MODIFICACION
//funcion para modificar estudiantes
void modificar_prestamos(void)//MENU DE MODIFICACIONES
{
	system("cls");
	cout<<"\n\t\tMODIFICAR PRESTAMO\n\n";
	datos_estudiante est_data;
	unsigned short n = 0;
	do
	{
		cout<<setw(25)<<"Cedula? ";
		strcpy(est_data.cedula,ingresar_numero("##########"));
		//validar la cedula ingresada
		n = validar_cedula(est_data.cedula);
		if(n > 0)
		{
			cout<<setw(25);
			imprimir_error(n);
		}
	}while(n > 0);
	cout<<endl;
	datos_libro lib_data;
	do
	{
		cout<<setw(25)<<"Codigo? ";
		strcpy(lib_data.codigo,ingresar_numero("#####"));
		//validar la codigo ingresada
		n = validar_codigo(lib_data.codigo);
		if(n > 0)
		{
			cout<<setw(25);
			imprimir_error(n);
		}
	}while(n > 0);
	//cedula valida
	datos_prestamo data;
	strcpy(data.cedula,est_data.cedula);
	strcpy(data.codigo,lib_data.codigo);
	unsigned long pos;
	cout<<endl;
	if(buscar_prestamo(data,pos))
	{
		prestamo* pre = new prestamo();
		pre->copiar(data);
		cout<<endl;
		pre->modificar();
		pre->escribir(pos);
	}
	else
	{
		cout<<setw(25);
		imprimir_error(PRE_NO_ENCONTRADO);
		cout<<endl;
	}
	//se ingresaron los datos
	system("pause");
}
//FUNCIONES DE USUARIO PARA ELIMINACION
//funcion para buscar un estudiante
void eliminar_prestamos(void)//MENU DE ELMINACIONES
{
	system("cls");
	cout<<"\n\t\tELIMINAR ESTUDIANTE\n\n";
	datos_estudiante est_data;
	unsigned short n = 0;
	do
	{
		cout<<setw(25)<<"Cedula? ";
		strcpy(est_data.cedula,ingresar_numero("##########"));
		//validar la cedula ingresada
		n = validar_cedula(est_data.cedula);
		if(n > 0)
		{
			cout<<setw(25);
			imprimir_error(n);
		}
	}while(n > 0);
	cout<<endl;
	datos_libro lib_data;
	do
	{
		cout<<setw(25)<<"Codigo? ";
		strcpy(lib_data.codigo,ingresar_numero("#####"));
		//validar la codigo ingresada
		n = validar_codigo(lib_data.codigo);
		if(n > 0)
		{
			cout<<setw(25);
			imprimir_error(n);
		}
	}while(n > 0);
	//cedula valida
	datos_prestamo data;
	strcpy(data.cedula,est_data.cedula);
	strcpy(data.codigo,lib_data.codigo);
	unsigned long pos;
	cout<<endl;
	if(buscar_prestamo(data,pos))
	{
		prestamo* pre = new prestamo();
		pre->copiar(data);
		pre->validar(false);
		pre->escribir(pos);
		cout<<endl;
		cout<<data;
	}
	else
	{
		cout<<setw(25);
		imprimir_error(PRE_NO_ENCONTRADO);
	}
	//se ingresaron los datos
	cout<<endl;
	system("pause");
}
//FUNCIONES UTILES
//obtencion del total de prestamos en el registro
unsigned long total_prestamos(void)
{
	ifstream archivo;
	archivo.open("datos_prestamos.dat",ios::binary);
	if(archivo.fail())
		return 0;
	//lee el total de archivos
	unsigned long n = 0;
	datos_prestamo data;
	archivo.read((char*)&data,sizeof(datos_prestamo));
	while(!archivo.eof())
	{
		n++;
		archivo.read((char*)&data,sizeof(datos_prestamo));
	}
	archivo.close();	
	return n;
}
//verifica que existan datos invalidos
unsigned long prestamos_no_validos(void)
{
	ifstream archivo;
	archivo.open("datos_prestamos.dat",ios::binary);
	if(archivo.fail())
		return 0;
	//lee el total de archivos
	unsigned long n = 0;
	datos_prestamo data;
	archivo.read((char*)&data,sizeof(datos_prestamo));
	while(!archivo.eof())
	{
		if(!data.valido)
			n++;
		archivo.read((char*)&data,sizeof(datos_prestamo));
	}
	archivo.close();
	return n;
}
//ARCHIVOS
//verifica que existan datos invalidos
void guardar_prestamos(void)
{
	//archivo de lectura
	ifstream archivo;
	archivo.open("datos_prestamos.dat",ios::binary);
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
	datos_prestamo data;
	archivo.read((char*)&data,sizeof(datos_prestamo));
	while(!archivo.eof())
	{
		if(data.valido)
			temporal.write((char*)&data,sizeof(datos_prestamo));
		archivo.read((char*)&data,sizeof(datos_prestamo));
	}
	//datos escritos
	archivo.close();
	temporal.close();
	//cambio de nombre
	remove("datos_prestamos.dat");
	rename("temporal.dat","datos_prestamos.dat");
}
