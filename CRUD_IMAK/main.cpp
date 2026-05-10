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
void insertar_alumno(Nodo*&, Estudiante);
void menu(int*);
bool validar_menu_principal(int);
bool validar_matricula(Nodo*, int);
Nodo* mergesort(Nodo*);
Nodo* merge(Nodo*, Nodo*);
void dividir_lista(Nodo*, Nodo**, Nodo**);

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

    do{
        cout<<"Matricula: ";
        cin>>nuevo_Estudiante.matricula;
        if(validar_matricula(lista, nuevo_Estudiante.matricula)){
            cout<<"Error: La matricula ya existe en el sistema"<<endl;
        }
    }while(validar_matricula(lista, nuevo_Estudiante.matricula));

    cin.ignore();

    cout<<"Nombre: ";
    getline(cin, nuevo_Estudiante.nombre);
    cout<<"Edad: ";
    cin>>nuevo_Estudiante.edad;
    cout<<"Promedio: ";
    cin>>nuevo_Estudiante.promedio;
    cin.ignore();
    cout<<"Direccion: ";
    getline(cin, nuevo_Estudiante.direccion);
    cout<<"Telefono: ";
    getline(cin, nuevo_Estudiante.telefono);

    Nodo* nuevo = new Nodo();
    nuevo->datos = nuevo_Estudiante;
    nuevo->siguiente = NULL;

    if(lista == NULL){
        lista = nuevo;
    } else {
        Nodo* actual = lista;
        while(actual->siguiente != NULL){
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }

    lista = mergesort(lista);

    cout<<"Alumno dado de alta correctamente"<<endl;
    system("cls");
}

void insertar_alumno(Nodo*& lista, Estudiante estudiante){
    Nodo* nuevo = new Nodo();

    nuevo->datos = estudiante;
    nuevo->siguiente = NULL;

    if(lista == NULL || estudiante.matricula < lista->datos.matricula){
        nuevo->siguiente = lista;
        lista = nuevo;
    }
    else{
        Nodo* actual = lista;

        while(actual->siguiente != NULL &&
              actual->siguiente->datos.matricula < estudiante.matricula){
            actual = actual->siguiente;
        }
        nuevo->siguiente = actual->siguiente;
        actual->siguiente = nuevo;
    }
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
    cout<<"Error: opcion invalida, pruebe una opcion entre 1-6: ";
    }
    }while(validar_menu_principal(*opcion));
    system("cls");
}

bool validar_matricula(Nodo* lista, int matricula){
    bool validacion = false;
    Nodo* actual = lista;
    while(actual != NULL){
        if(actual->datos.matricula == matricula){
            validacion = true;
        }
        actual = actual->siguiente;
    }
    return validacion;
}

void dividir_lista(Nodo* fuente, Nodo** frente, Nodo** atras){
    Nodo* rapido;
    Nodo* lento;
    lento = fuente;
    rapido = fuente->siguiente;

    while(rapido != NULL){
        rapido = rapido->siguiente;
        if(rapido != NULL){
            lento = lento->siguiente;
            rapido = rapido->siguiente;
        }
    }

    *frente = fuente;
    *atras = lento->siguiente;
    lento->siguiente = NULL;
}

Nodo* merge(Nodo* a, Nodo* b){
    Nodo* resultado = NULL;

    if(a == NULL)
        return b;
    else if(b == NULL)
        return a;

    if(a->datos.matricula <= b->datos.matricula){
        resultado = a;
        resultado->siguiente = merge(a->siguiente, b);
    } else {
        resultado = b;
        resultado->siguiente = merge(a, b->siguiente);
    }

    return resultado;
}

Nodo* mergesort(Nodo* cabeza){
    if(cabeza == NULL || cabeza->siguiente == NULL)
        return cabeza;

    Nodo* a;
    Nodo* b;

    dividir_lista(cabeza, &a, &b);

    a = mergesort(a);
    b = mergesort(b);

    return merge(a, b);
}
