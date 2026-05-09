#include <iostream>

using namespace std;

struct Estudiante{
    int matricula;
    string nombre;
    int edad;
    float promedio;
    string direccion;
    string telefono;
};

struct Nodo{
    Estudiante datos;
    Nodo* siguiente;
};

void dar_de_alta_Estudiante(Nodo*&);
void menu(int*);
bool validar_menu_principal(int);
bool validar_matricula(Nodo*, int);

int main()
{
    Nodo* lista_alumnos = NULL;
    int opcion_principal = 0;
    do{
    menu(&opcion_principal);

    switch(opcion_principal){
    case 1:
    dar_de_alta_Estudiante(lista_alumnos);
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
    }while(opcion_principal != 6);
}

void dar_de_alta_Estudiante(Nodo*& lista){
    cout<<"ALTA DE ESTUDIANTES"<<endl;

    Estudiante nuevo_Estudiante;

    cout<<"Matricula: ";
    cin>>nuevo_Estudiante.matricula;
    cout<<"Nombre: ";
    system("cls");
}

bool validar_menu_principal(int opcion){
    bool validacion = true;
    if(opcion >=1 && opcion<= 6)
    validacion = false;
    return validacion;
}

void menu(int* opcion){
    cout << "SISTEMA DE ESTUDIANTES IMAK" << endl;
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
    if(validar_menu_principal(*opcion)){
    cout<<"Error, ingreso una opcion invalida, pruebe una opcion entre 1-6: ";
    }
    }while(validar_menu_principal(*opcion));
    system("cls");
}
