//libreria para las clases
#include "errores.cpp"
#include "funciones.cpp"
#include "usuarios.cpp"
#include "fechas.cpp"
//acceso a los headers
#include "estudiantes.cpp"
#include "libros.cpp"
#include "prestamos.cpp"
//menus de seleccion
using namespace std;
int menu(usuario*);
//funcion principal
int main(int argc, char const *argv[])
{
	//inicio la sesion con el usuario
	usuario* usu = new usuario();
	usu->sesion();
	menu(usu);	
	return 0;
}
//funcion para imprimir el menu
int menu(usuario* usu)
{
	char opcion = '*';
	do
	{
		system("cls");
		cout<<"\n\t\tBIBLIOTECA NACIONAL QUARY\n\n";
		cout<<setw(25)<<""<<"TECLA\n";
		cout<<setw(25)<<"Estudiantes: "	<<"[e/E]\n";
		cout<<setw(25)<<"Libros: "		<<"[l/L]\n";
		cout<<setw(25)<<"Prestamos: "	<<"[p/P]\n";
		cout<<setw(25)<<"Usuarios: "	<<"[u/U]\n\n";
		cout<<setw(25)<<"Retornar: "	<<"[ESC]\n\n";
		cout<<setw(25)<<"Elija una opcion? ";
		opcion = toupper(getche());
		switch(opcion)
		{
			case 'E':
				if(usu->permiso_leer(USU_ESTUDIANTE))
					menu_estudiante(usu); 
			break;
			case 'L': 
				if(usu->permiso_leer(USU_LIBRO))
					menu_libro(usu); 
			break;
			case 'P':
				if(usu->permiso_leer(USU_PRESTAMO))
					menu_prestamo(usu); 
				break;
			case 'U':
				if(usu->permiso_leer(USU_USUARIO))
					menu_usuario(usu); 
				break;
			default: 
				if((int)opcion != 27)
				{
					cout<<endl<<endl;
					cout<<setw(25)<<"Opcion no valida!";
					getch();
				}
				else
				{
					//verificación de salida
					cout<<endl<<endl;
					cout<<setw(25)<<"Desea salir [s/n]? ";
					if(!ingresar_sn())
						opcion = (char)27;
					cout<<endl;
				}
				break;
		}
	}while((int)opcion != 27);
	return 0;
}
