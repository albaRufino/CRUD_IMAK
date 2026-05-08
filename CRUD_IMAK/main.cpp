#include <iostream>

using namespace std;

struct Alumno{
    int matricula;
    string nombre;
    int edad;
    float promedio;
    string direccion;
    string telefono;
};

void menu(int*);
bool validarMenuPrincipal(int);

int main()
{
    int opcionPrincipal = 0;
    do{
    cout << "SISTEMA DE ESTUDIANTES IMAK" << endl;
    menu(&opcionPrincipal);

    switch(opcionPrincipal){
    case 1:
    cout<<"ALTA DE ESTUDIANTES"<<endl;

    break;

    case 2:

    break;

    case 3:

    break;

    case 4:

    break;

    case 5:

    break;

    case 6:
    cout<<"Saliendo..."<<endl;
    }
    }while(opcionPrincipal != 6);
}

bool validarMenuPrincipal(int opcion){
    bool validacion = true;
    if(opcion >=1 && opcion<= 6)
    validacion = false;
    return validacion;
}

void menu(int* opcion){
    cout << "MENU" << endl;
    cout <<"1) Alta de estudiante"<<endl;
    cout <<"2) Baja de estudiante"<<endl;
    cout<<"3) Recuperar estudiante"<<endl;
    cout<<"4) Reporte de estudiantes"<<endl;
    cout<<"5) Control de inscripciones"<<endl;
    cout<<"6) Salir"<<endl;

    cout<<"Ingrese su opcion: ";
    do{
    cin>>*opcion;
    if(validarMenuPrincipal(*opcion)){
    cout<<"Error, ingreso una opcion invalida, pruebe una opcion entre 1-6: ";
    }
    }while(validarMenuPrincipal(*opcion));
    system("cls");
}
