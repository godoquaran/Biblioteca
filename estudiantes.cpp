//interfaces de las clases
#include "estudiantes.h"
using namespace std;
//FUNCIONES DE CLASE
//constructor por defecto
estudiante::estudiante(void)
{
	//datos de busqueda
	strcpy(datos.cedula,"");
	//datos de identificacion
	strcpy(datos.nombre,"");
	datos.anno = 0;
	strcpy(datos.institucion,"");
	//datos de clasificacion
	datos.sexo = 'M';
	fecha* fec = new fecha();
	fec->copiar_en(datos.fecha_nac);
	//datos personales
	strcpy(datos.direccion,"");
	strcpy(datos.email,"");	
	strcpy(datos.telefono,"");
	strcpy(datos.movil,"");
	//datos del objeto
	datos.valido = false;
}
//FUNCIONES DE CLASE PARA ARCHIVO
//cargar los datos del estudiante en la estructura de datos
unsigned short estudiante::leer(unsigned long pos)
{
	ifstream archivo;
	archivo.open("datos_estudiantes.dat",ios::binary);
	if(archivo.fail())
		return ARCH_NO_LEER;
	archivo.seekg(pos*sizeof(datos_estudiante),ios::beg);
	archivo.read((char*)&datos,sizeof(datos_estudiante));
	archivo.close();
	return 0;
}
//guardar los datos del estudiante en un archivo
unsigned short estudiante::escribir(void)
{
	ofstream archivo;
	//se abre el archivo para escritura, añadidura y binario
	archivo.open("datos_estudiantes.dat",ios::app|ios::binary);
	//el archivo no existe se crea
	if(archivo.bad())
		archivo.open("datos_estudiantes.dat");
	archivo.write((char*)&datos,sizeof(datos_estudiante));
	archivo.close();
	return 0;
}
//modificar los datos del estudiantes en el archivo
unsigned short estudiante::escribir(unsigned long pos)
{
	fstream archivo;
	archivo.open("datos_estudiantes.dat",ios::in|ios::out|ios::binary);
	if(archivo.fail())
		return ARCH_NO_ESCRIBIR;
	archivo.seekp(pos*sizeof(datos_estudiante),ios::beg);
	archivo.write((char*)&datos,sizeof(datos_estudiante));
	archivo.close();
	return 0;
}
//FUNCIONES DE CLASE PARA INGRESO
//ingreso por copia de datos en la clase estudiante
void estudiante::copiar(datos_estudiante data)
{
	//datos de busqueda
	strcpy(datos.cedula,data.cedula);
	//datos de identificacion
	strcpy(datos.nombre,data.nombre);
	datos.anno = data.anno;
	strcpy(datos.institucion,data.institucion);
	//datos de clasificacion
	datos.sexo = data.sexo;
	fecha* fec = new fecha();
	fec->copiar(data.fecha_nac);
	fec->copiar_en(datos.fecha_nac);
	//datos personales
	strcpy(datos.direccion,data.direccion);
	strcpy(datos.email,data.email);	
	strcpy(datos.telefono,data.telefono);
	strcpy(datos.movil,data.movil);
	//datos del objeto
	datos.valido = data.valido;
}
//ingreso de datos desde teclado
void estudiante::ingresar(void)
{
	//ingresar la cedula
	unsigned short n = 0;
	bool encontrado;
	//hasta tener una cedula valida
	system("cls");
	cout<<"\n\t\tDATOS DEL ESTUDIANTE\n\n";
	do
	{
		cout<<setw(25)<<"Cedula? ";
		strcpy(datos.cedula,ingresar_numero("##########"));
		//validar la cedula ingresada
		n = validar_cedula(datos.cedula);
		if(n > 0)
		{
			cout<<setw(25);
			imprimir_error(n);
		}
		//determina si ya existe el estudiante
		unsigned long pos;
		encontrado = buscar_estudiante(datos,pos);
		if(encontrado)
		{
			cout<<setw(25);
			imprimir_error(EST_YA_EXISTE);
		}
	}while(n > 0 || encontrado);
	cout<<endl;
	//ingresar el nombre
	cout<<setw(25)<<"Nombre Completo? ";
	cin.getline(datos.nombre,EST_MAX_NOMBRE);
	//años de estudio del estudiante
	cout<<setw(25)<<"Anno/Semestre/Grado? ";		
	datos.anno = ingresar_numero(1,10);
	cout<<endl;
	//institucion o titulo del estudiante
	cout<<setw(25)<<"Institucion/Empresa? ";
	cin.getline(datos.institucion,EST_MAX_INSTITUCION);
	//sexo
	cout<<setw(25)<<"Sexo [f/m]? ";
	datos.sexo = ingresar_caracter("FM");
	cout<<endl;
	//edad
	cout<<setw(25)<<"Fecha de Nacimiento? ";
	fecha* fec = new fecha();
	fec->ingresar();
	fec->copiar_en(datos.fecha_nac);
	cout<<endl;
	//direccion
	cout<<setw(25) << "Direccion? ";
	cin.getline(datos.direccion,EST_MAX_DIRECCION);
	//correo electronico
	do
	{
		cout<<setw(25) << "Email? " ;
		cin.getline(datos.email,EST_MAX_EMAIL);
		n = validar_email(datos.email);
		if(n > 0)
		{
			cout<<setw(25);
			imprimir_error(n);
		}
	}while(n > 0);
	//numero de telefono fijo
	cout<<setw(25)<<"Telefono? ";
	strcpy(datos.telefono,ingresar_numero("#######"));
	cout<<endl;	
	//numero de celular 
	cout<<setw(25)<<"Celular? ";
	strcpy(datos.movil,ingresar_numero("#########"));
	cout<<endl;
	//validar el objeto
	datos.valido = true;		
}
//FUNCIONES DE CLASE PARA REPORTE
//imprime los datos
ostream& operator << (ostream& co, const datos_estudiante &a)
{
	co<<setw(25)<<"Cedula: "		<<a.cedula<<endl;
	co<<setw(25)<<"Nombre: "		<<a.nombre<<endl;		
	co<<setw(25)<<"Nacimiento: "	<<a.fecha_nac<<endl;
	co<<setw(25)<<"Anno: "			<<a.anno<<endl;
	co<<setw(25)<<"Institucion: "	<<a.institucion<<endl;	
	co<<setw(25)<<"Direccion: "		<<a.direccion<<endl;	
	co<<setw(25)<<"Email: "			<<a.email<<endl;
	co<<setw(25)<<"Telefono: "		<<a.telefono<<endl;
	co<<setw(25)<<"Movil: "			<<a.movil<<endl;
	co<<setw(25)<<"Valido: "		<<boolalpha<<a.valido<<endl;	
}
//ingreso de datos en la clase estudiante
void estudiante::copiar_en(datos_estudiante &data)
{
	//datos de busqueda
	strcpy(data.cedula,datos.cedula);
	//datos de identificacion
	strcpy(data.nombre,datos.nombre);
	data.anno = datos.anno;
	strcpy(data.institucion,datos.institucion);
	//datos de clasificacion
	data.sexo = datos.sexo;
	fecha* fec = new fecha();
	fec->copiar(datos.fecha_nac);
	fec->copiar_en(data.fecha_nac);
	//datos personales
	strcpy(data.direccion,datos.direccion);
	strcpy(data.email,datos.email);	
	strcpy(data.telefono,datos.telefono);
	strcpy(data.movil,datos.movil);
	//datos del objeto
	data.valido = datos.valido;
}
//imprime los datos del estudiante
void estudiante::imprimir(void)
{
	if(datos.valido)
	{
		cout<<setw(25)<<"Cedula: "<<datos.cedula<<endl;
		cout<<setw(25)<<"Nombre: "<<datos.nombre<<endl;
		fecha* fec = new fecha();
		unsigned short edad;
		fec->calcular_edad(datos.fecha_nac,edad);
		cout<<setw(25)<<"Edad: "<<edad<<endl;
		cout<<setw(25)<<"Anno: "<<datos.anno<<endl;
		cout<<setw(25)<<"Institucion: "<<datos.institucion<<endl;		
		if(strcmp(datos.direccion,"NULL") != 0)
			cout<<setw(25)<<"Direccion: "<<datos.direccion<<endl;	
		if(strcmp(datos.email,"NULL") != 0)
			cout<<setw(25)<<"Email: "<<datos.email<<endl;
		if(strcmp(datos.telefono,"NULL") != 0)
			cout<<setw(25)<<"Telefono: "<<datos.telefono<<endl;
		if(strcmp(datos.movil,"NULL") != 0)
			cout<<setw(25)<<"Movil: "<<datos.movil<<endl;
	}
}
//FUNCIONES DE CLASE PARA BUSQUEDA
//busca un estudiante dados los datos
bool estudiante::comparar(datos_estudiante data)
{
	return datos == data;
}
//FUNCIONES DE CLASE PARA MODIFICACION
//busca un estudiante dados los datos
void estudiante::modificar(void)
{
	//hasta tener una cedula valida
	cout<<setw(25)<<"Cedula: "<<datos.cedula<<endl;
	bool opcion;
	//ingresar el nombre
	cout<<setw(25)<<"Nombre Completo: "<<datos.nombre<<endl;
	cout<<setw(25)<<"Conservar [s/n]? ";
	if(!ingresar_sn())
	{
		cout<<endl;
		cout<<setw(25)<<"Nombre Completo? ";
		cin.getline(datos.nombre,40);
	}
	else
		cout<<endl;
	//años de estudio del estudiante
	cout<<setw(25)<<"Anno/Semestre/Grado: "<<datos.anno<<endl;
	cout<<setw(25)<<"Conservar [s/n]? ";
	if(!ingresar_sn())
	{
		cout<<endl;
		cout<<setw(25)<<"Anno/Semestre/Grado? ";		
		datos.anno = ingresar_numero(1,10);
		cout<<endl;
	}
	else
		cout<<endl;
	//institucion o titulo del estudiante
	cout<<setw(25)<<"Institucion/Empresa: "<<datos.institucion<<endl;
	cout<<setw(25)<<"Conservar [s/n]? ";
	if(!ingresar_sn())
	{
		cout<<endl;
		cout<<setw(25)<<"Institucion/Empresa? ";
		cin.getline(datos.institucion,30);
	}
	else
		cout<<endl;
	//sexo
	cout<<setw(25)<<"Sexo [f/m]: "<<datos.sexo<<endl;
	cout<<setw(25)<<"Conservar [s/n]? ";
	if(!ingresar_sn())
	{
		cout<<endl;
		cout<<setw(25)<<"Sexo [f/m]? ";
		datos.sexo = ingresar_caracter("FM");
		cout<<endl;
	}
	else
		cout<<endl;
	//edad
	cout<<setw(25)<<"Fecha de Nacimiento: "<<datos.fecha_nac.aaaammdd<<endl;
	cout<<setw(25)<<"Conservar [s/n]? ";
	if(!ingresar_sn())
	{
		cout<<endl;
		cout<<setw(25)<<"Fecha de Nacimiento? ";
		fecha* fec = new fecha();
		fec->ingresar();
		fec->copiar_en(datos.fecha_nac);
		cout<<endl;
	}
	else
		cout<<endl;
	//direccion
	cout<<setw(25)<<"Direccion: "<<datos.direccion<<endl;
	cout<<setw(25)<<"Conservar [s/n]? ";
	if(!ingresar_sn())
	{
		cout<<endl;
		cout<<setw(25)<<"Direccion? ";
		cin.getline(datos.direccion,50);
	}
	else
		cout<<endl;
	cout<<setw(25)<<"Email: "<<datos.email<<endl;
	cout<<setw(25)<<"Conservar [s/n]? ";
	if(!ingresar_sn())
	{
		cout<<endl;
		unsigned short n = 0;
		//correo electronico
		do
		{
			cout<<setw(25) << "Email? " ;
			cin.getline(datos.email,40);
			n = validar_email(datos.email);
			if(n > 0)
			{
				cout<<setw(25);
				imprimir_error(n);
			}
		}while(n > 0);
	}
	else
		cout<<endl;
	//numero de telefono fijo
	cout<<setw(25)<<"Telefono: "<<datos.telefono<<endl;
	cout<<setw(25)<<"Conservar [s/n]? ";
	if(!ingresar_sn())
	{
		cout<<endl;
		cout<<setw(25)<<"Telefono? ";
		strcpy(datos.telefono,ingresar_numero("#######"));
		cout<<endl;
	}
	else
		cout<<endl;
	//numero de celular 
	cout<<setw(25)<<"Celular: "<<datos.movil<<endl;
	cout<<setw(25)<<"Conservar [s/n]? ";
	if(!ingresar_sn())
	{
		cout<<endl;
		cout<<setw(25)<<"Celular? ";
		strcpy(datos.movil,ingresar_numero("#########"));
		cout<<endl;
	}
	cout<<endl;
	//validar el objeto
	datos.valido = true;	
}
//FUNCIONES DE CLASE PARA ELIMINACION
//eliminar los datos de la estructura de datos
void estudiante::validar(bool valor)
{
	datos.valido = valor;
}
//FUNCIONES DE CLASE SOBRECARGADAS
// operador friend de test de igualdad sobrecargado
bool operator== (const datos_estudiante& a, const datos_estudiante& b)
{
	for(int i=0; i<MAX_CEDULA; i++)
		if(a.cedula[i] != b.cedula[i])
			return false;
	return true;
}
//FUNCIONES DE USUARIO
//funcion para imprimir el menu del estudiante
void menu_estudiante(usuario* usu)
{
	char opcion = '*';
	do
	{
		system("cls");
		cout<<"\n\t\t\tESTUDIANTES\n\n";
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
				if(usu->permiso_escribir(USU_ESTUDIANTE))
					ingresar_estudiantes();
				break;
			case 'B': 
				buscar_estudiantes();
				break;
			case 'P': 
				imprimir_estudiantes();
				break;
			case 'M':
				if(usu->permiso_escribir(USU_ESTUDIANTE))
					modificar_estudiantes();
				break; 
			case 'E': 
				if(usu->permiso_escribir(USU_ESTUDIANTE))
					eliminar_estudiantes();
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
					n = estudiantes_no_validos();
					if(n > 0)
					{
						cout<<setw(25)<<"Datos no validos: "<<n<<endl;
						//verificación de salida
						cout<<endl;
						cout<<setw(25)<<"Desea eliminarlos [s/n]? ";
						if(ingresar_sn())
							guardar_estudiantes();
					}
				}
				break;
		}
	}while((int)opcion != 27);	
}
//FUNCIONES DE USUARIO PARA INGRESO
//ingreso de datos en la clase
void ingresar_estudiantes(void)//MENU DE ALTAS
{
	//menu de ingreso de estudiantes
	char opcion = '*';
	do
	{
		system("cls");
		cout<<"\n\t\tINGRESAR ESTUDIANTE\n\n";
		cout<<setw(25)<<""<<"TECLA\n";
		cout<<setw(25)<<"Archivo: "		<<"[a/A]\n";
		cout<<setw(25)<<"Teclado: "		<<"[t/T]\n\n";
		cout<<setw(25)<<"Retornar: "	<<"[ESC]\n\n";
		cout<<setw(25)<<"Elija una opcion? ";
		opcion = toupper(getche());
		switch(opcion)
		{
			case 'A': ingresar_archivo_estudiantes();
				break;
			case 'T': ingresar_estudiante();
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
void ingresar_archivo_estudiantes(void)
{
	//apertura del archivo
	char ruta[EST_BUFFER];
	cout<<endl<<endl;
	cout<<setw(25)<<"Path del archivo CSV? ";
	cin.getline(ruta,EST_BUFFER);
	//buffer de entrada
	char fila[EST_BUFFER];
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
	while(archivo.getline(fila,EST_BUFFER,'\n') != NULL)
	{
		if(strcmp(fila,"") != 0)
		{
			datos_estudiante data;
			data = obtener_estudiante(fila);
			if(!buscar_estudiante(data,pos))
			{
				estudiante* est = new estudiante();
				est->copiar(data);
				est->escribir();
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
datos_estudiante obtener_estudiante(char* fila)
{
	char campo[EST_CAMPOS][EST_MAX];	
	unsigned short indices[EST_CAMPOS];
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
	if(n != EST_CAMPOS)
	{
		cout<<setw(25);
		imprimir_error(ARCH_EST_NO_COMPLETO);
		datos_estudiante data;
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
			if(i==EST_CEDULA && c==MAX_CEDULA)
				break;
			if(i==EST_NOMBRE && c==EST_MAX_NOMBRE-1)
				break;
			if(i==EST_INSTITUCION && c==EST_MAX_INSTITUCION-1)
				break;
			if(i==EST_SEXO && c==EST_MAX_SEXO)
				break;
			if(i==EST_FEC_NACIMIENTO && c==FEC_MAX)
				break;
			if(i==EST_DIRECCION && c==EST_MAX_DIRECCION-1)
				break;
			if(i==EST_EMAIL && c==EST_MAX_EMAIL-1)
				break;
			if(i==EST_TELEFONO && c==EST_MAX_TELEFONO-1)
				break;
			if(i==EST_MOVIL && c==EST_MAX_MOVIL-1)
				break;
		}
		campo[i][c] = '\0';			
	}
	//verifico que sea una cedula valida
	int k;
	k = validar_cedula(campo[EST_CEDULA]);
	if(k > 0)
	{
		cout<<setw(25);
		imprimir_error(k);
		datos_estudiante data;
		return data;
	}
	datos_estudiante data;
	//numero de cedula valida
	strcpy(data.cedula,campo[EST_CEDULA]);	
	//nombre del estudiante
	strcpy(data.nombre,campo[EST_NOMBRE]);	
	//año de estudios
	n = 0;
	for(int i=0;i<strlen(campo[EST_ANNO]);i++) 
		n = 10 * n + (campo[EST_ANNO][i] - '0');
	data.anno = n;	
	//institucion a la que pertenece
	strcpy(data.institucion,campo[EST_INSTITUCION]);
	//genero del estudiante
	data.sexo = campo[EST_SEXO][0];
	//ingreso de la edad del estudiante
	fecha* fec = new fecha();
	fec->ingresar_mmddaaaa(campo[EST_FEC_NACIMIENTO]);
	fec->copiar_en(data.fecha_nac);	
	//ingreso de la direccion
	strcpy(data.direccion,campo[EST_DIRECCION]);
	//ingreso de el correo electronico
	strcpy(data.email,campo[EST_EMAIL]);	
	//telefonos
	strcpy(data.telefono,campo[EST_TELEFONO]);
	//movil
	strcpy(data.movil,campo[EST_MOVIL]);
	//validar el objeto
	data.valido = true;
	//todos los datos han sido ingresados
	return data;
}
//funcion para ingresar desde teclado
void ingresar_estudiante(void)
{
	do
	{
		estudiante* est = new estudiante();
		est->ingresar();		
		est->escribir();//retorna error
		//ingresar mas estudiantes
		cout<<endl;
		cout<<setw(25)<<"Nuevo estudiante [s/n] ? ";
	}while(ingresar_sn());	
}
//FUNCIONES DE USUARIO PARA REPORTE
//funcion para imprimir el archivo de estudiantes
void imprimir_estudiantes(void)//MENU
{	
	unsigned long total = 0;
	//ubicar el total de los elementos
	//0 .. total-1
	total = total_estudiantes();
	if(total == 0)
		return;
	unsigned long pos = 0;
	char opcion = '*';
	do
	{		
		system("cls");
		cout<<"\n\t\tIMPRIMIR ESTUDIANTE\n";
		estudiante* est = new estudiante();
		est->leer(pos);//retorna error
		cout<<endl;
		est->imprimir();
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
//funcion para buscar estudiantes
void buscar_estudiantes(void)//MENU DE BUSQUEDAS
{
	system("cls");
	cout<<"\n\t\tBUSCAR ESTUDIANTE\n\n";
	datos_estudiante data;
	unsigned short n = 0;
	do
	{
		cout<<setw(25)<<"Cedula? ";
		strcpy(data.cedula,ingresar_numero("##########"));
		//validar la cedula ingresada
		n = validar_cedula(data.cedula);
		if(n > 0)
		{
			cout<<setw(25);
			imprimir_error(n);
		}
	}while(n > 0);
	//cedula valida
	cout<<endl;
	unsigned long pos;
	if(buscar_estudiante(data,pos))
	{
		estudiante* est = new estudiante();
		est->copiar(data);
		cout<<endl;
		est->imprimir();
	}
	else
	{
		cout<<setw(25);
		imprimir_error(EST_NO_ENCONTRADO);
	}
	cout<<endl;
	system("pause");
}
//funcion para buscar un estudiante en el archivo
bool buscar_estudiante(datos_estudiante &data, unsigned long &pos)
{
	//archivo
	fstream archivo;
	archivo.open("datos_estudiantes.dat",ios::in|ios::binary);	
	if(archivo.fail())
		return false;
	pos = 0;
	datos_estudiante cab;
	archivo.seekp(pos*sizeof(datos_estudiante),ios::beg);
	archivo.read((char*)&cab,sizeof(datos_estudiante));
	while(!archivo.eof())
	{
		estudiante* est = new estudiante();
		est->copiar(cab);
		if(est->comparar(data))
		{
			est->copiar_en(data);
			archivo.close();
			return true;
		}
		//leo el siguiente dato
		pos++;
		archivo.seekp(pos*sizeof(datos_estudiante),ios::beg);
		archivo.read((char*)&cab,sizeof(datos_estudiante));
	}
	//cierre del archivo
	archivo.close();
	return false;
}
//FUNCIONES DE USUARIO PARA MODIFICACION
//funcion para modificar estudiantes
void modificar_estudiantes(void)//MENU DE MODIFICACIONES
{
	system("cls");
	cout<<"\n\t\tMODIFICAR ESTUDIANTE\n\n";
	datos_estudiante data;
	unsigned short n = 0;
	do
	{
		cout<<setw(25)<<"Cedula? ";
		strcpy(data.cedula,ingresar_numero("##########"));
		//validar la cedula ingresada
		n = validar_cedula(data.cedula);
		if(n > 0)
		{
			cout<<setw(25);
			imprimir_error(n);
		}
	}while(n > 0);
	//cedula valida
	unsigned long pos;
	cout<<endl;
	if(buscar_estudiante(data,pos))
	{
		estudiante* est = new estudiante();
		est->copiar(data);
		cout<<endl;
		est->modificar();
		est->escribir(pos);
	}
	else
	{
		cout<<setw(25);
		imprimir_error(EST_NO_ENCONTRADO);
	}
	//se ingresaron los datos
	cout<<endl;
	system("pause");
}
//FUNCIONES DE USUARIO PARA ELIMINACION
//funcion para buscar un estudiante
void eliminar_estudiantes(void)//MENU DE ELMINACIONES
{
	system("cls");
	cout<<"\n\t\tELIMINAR ESTUDIANTE\n\n";
	datos_estudiante data;
	unsigned short n = 0;
	do
	{
		cout<<setw(25)<<"Cedula? ";
		strcpy(data.cedula,ingresar_numero("##########"));
		//validar la cedula ingresada
		n = validar_cedula(data.cedula);
		if(n > 0)
		{
			cout<<setw(25);
			imprimir_error(n);
		}
	}while(n > 0);
	//cedula valida
	unsigned long pos;
	cout<<endl;
	if(buscar_estudiante(data,pos))
	{
		estudiante* est = new estudiante();
		est->copiar(data);
		est->validar(false);
		est->escribir(pos);
		cout<<endl;
		cout<<data;
	}
	else
	{
		cout<<setw(25);
		imprimir_error(EST_NO_ENCONTRADO);
	}
	//se ingresaron los datos
	cout<<endl;
	system("pause");
}
//FUNCIONES UTILES
//obtencion del total de estudiantes en el registro
unsigned long total_estudiantes(void)
{
	ifstream archivo;
	archivo.open("datos_estudiantes.dat",ios::binary);
	if(archivo.fail())
		return 0;
	//lee el total de archivos
	unsigned long n = 0;
	datos_estudiante data;
	archivo.read((char*)&data,sizeof(datos_estudiante));
	while(!archivo.eof())
	{
		n++;
		archivo.read((char*)&data,sizeof(datos_estudiante));
	}
	archivo.close();	
	return n;
}
//verifica que existan datos invalidos
unsigned long estudiantes_no_validos(void)
{
	ifstream archivo;
	archivo.open("datos_estudiantes.dat",ios::binary);
	if(archivo.fail())
		return 0;
	//lee el total de archivos
	unsigned long n = 0;
	datos_estudiante data;
	archivo.read((char*)&data,sizeof(datos_estudiante));
	while(!archivo.eof())
	{
		if(!data.valido)
			n++;
		archivo.read((char*)&data,sizeof(datos_estudiante));
	}
	archivo.close();
	return n;
}
//ARCHIVOS
//verifica que existan datos invalidos
void guardar_estudiantes(void)
{
	//archivo de lectura
	ifstream archivo;
	archivo.open("datos_estudiantes.dat",ios::binary);
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
	datos_estudiante data;
	archivo.read((char*)&data,sizeof(datos_estudiante));
	while(!archivo.eof())
	{
		if(data.valido)
			temporal.write((char*)&data,sizeof(datos_estudiante));
		archivo.read((char*)&data,sizeof(datos_estudiante));
	}
	//datos escritos
	archivo.close();
	temporal.close();
	//cambio de nombre
	remove("datos_estudiantes.dat");
	rename("temporal.dat","datos_estudiantes.dat");
}
