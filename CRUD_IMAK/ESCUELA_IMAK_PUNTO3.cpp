#include <iostream>
#include <string>
#include <regex>
#include <limits>
#include <cstdlib> 

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

struct Pila{
    Estudiante datos;
    Pila* abajo;
};

void dar_de_alta_Estudiante(Nodo*&);
void insertar_alumno(Nodo*&, Estudiante);
void menu(int*);
bool validar_menu_principal(int);
bool validar_matricula(Nodo*, int);
Nodo* mergesort(Nodo*);
Nodo* merge(Nodo*, Nodo*);
void dividir_lista(Nodo*, Nodo**, Nodo**);
void submenu(int *);
void Encabezado(const string &titulo);
void BusquedaSecuencial(Nodo*& lista, Pila*& pila);
bool ValidarCaracteres(string nombre);
void push(Pila*& pila, Estudiante dar_baja);
void BusquedaBinaria(Nodo*& lista, Pila*& pila);
int contarNodos(Nodo* lista);
Nodo* obtenerNodoEnIndice(Nodo* lista, int indice, Nodo** prev);
void mostrarLista(Nodo* lista);     
void mostrarPila(Pila* pila);        
bool pop(Pila*& pila, Estudiante& recuperado);   
void RecuperarAlumno(Nodo*& lista, Pila*& pila); 

int main()
{
    Nodo* lista_alumnos = NULL;
    Pila* pila_bajas = NULL; 
    int opcion_principal = 0;
    int opcion_submenu = 0;
    
    do{
        menu(&opcion_principal);
    
        switch(opcion_principal){
            case 1:
                dar_de_alta_Estudiante(lista_alumnos);
                break;
        
            case 2:
                do{
                    submenu(&opcion_submenu);
                    switch(opcion_submenu){
                        case 1:
                            BusquedaSecuencial(lista_alumnos, pila_bajas);
                            break;
                        case 2:
                            BusquedaBinaria(lista_alumnos, pila_bajas);
                            break;
                    }
                } while(opcion_submenu != 3);
                break;
        
            
            case 3:
                RecuperarAlumno(lista_alumnos, pila_bajas);
                break;
        
            case 4:
                
                cout << "Funcionalidad en desarrollo..." << endl;
                system("pause");
                system("cls");
                break;
        
            case 5:
                
                cout << "Funcionalidad en desarrollo..." << endl;
                system("pause");
                system("cls");
                break;
        
            case 6:                 
                mostrarLista(lista_alumnos);
                break;
                
            case 7:                 
                mostrarPila(pila_bajas);
                break;
        
            case 8:
                cout << "Saliendo..." << endl;
        }
    } while(opcion_principal != 8);
    
    return 0;
}

void mostrarLista(Nodo* lista) {
    Encabezado("LISTA DE ESTUDIANTES ACTIVOS");
    if (lista == NULL) {
        cout << "No hay estudiantes registrados." << endl;
    } else {
        Nodo* actual = lista;
        int contador = 1;
        while (actual != NULL) {
            cout << "\n--- Estudiante " << contador++ << " ---" << endl;
            cout << "Matricula: " << actual->datos.matricula << endl;
            cout << "Nombre: " << actual->datos.nombre << endl;
            cout << "Edad: " << actual->datos.edad << endl;
            cout << "Promedio: " << actual->datos.promedio << endl;
            cout << "Direccion: " << actual->datos.direccion << endl;
            cout << "Telefono: " << actual->datos.telefono << endl;
            cout << "----------------------------------------" << endl;
            actual = actual->siguiente;
        }
    }
    system("pause");
    system("cls");
}

void mostrarPila(Pila* pila) {
    Encabezado("PILA DE ESTUDIANTES DADOS DE BAJA (RECUPERABLES)");
    if (pila == NULL) {
        cout << "No hay estudiantes en la pila de bajas." << endl;
    } else {
        Pila* actual = pila;
        int contador = 1;
        while (actual != NULL) {
            cout << "\n--- Baja " << contador++ << " (tope hacia abajo) ---" << endl;
            cout << "Matricula: " << actual->datos.matricula << endl;
            cout << "Nombre: " << actual->datos.nombre << endl;
            cout << "Edad: " << actual->datos.edad << endl;
            cout << "Promedio: " << actual->datos.promedio << endl;
            cout << "Direccion: " << actual->datos.direccion << endl;
            cout << "Telefono: " << actual->datos.telefono << endl;
            cout << "----------------------------------------" << endl;
            actual = actual->abajo;
        }
    }
    system("pause");
    system("cls");
}


void push(Pila*& pila, Estudiante dar_baja){
    Pila* nuevo = new Pila;
    nuevo->datos = dar_baja;
    nuevo->abajo = pila;
    pila = nuevo;
}


bool pop(Pila*& pila, Estudiante& recuperado){
    if(pila == NULL){
        return false;
    }
    
    recuperado = pila->datos;
    Pila* a_eliminar = pila;
    pila = pila->abajo; 
    delete a_eliminar;
    return true;
}


void RecuperarAlumno(Nodo*& lista, Pila*& pila){
    Encabezado("RECUPERAR ALUMNO");

    Estudiante recuperado;

    
    if(!pop(pila, recuperado)){
        cout << "No hay alumnos en la pila de bajas para recuperar." << endl;
        system("pause");
        system("cls");
        return;
    }

    
    cout << "Se recuperara el siguiente alumno:" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Matricula: " << recuperado.matricula << endl;
    cout << "Nombre: "    << recuperado.nombre    << endl;
    cout << "Edad: "      << recuperado.edad       << endl;
    cout << "Promedio: "  << recuperado.promedio   << endl;
    cout << "Direccion: " << recuperado.direccion  << endl;
    cout << "Telefono: "  << recuperado.telefono   << endl;
    cout << "----------------------------------------" << endl;

    
    insertar_alumno(lista, recuperado);

    
    lista = mergesort(lista);

    cout << "Alumno recuperado y reintegrado a la lista activa correctamente." << endl;
    system("pause");
    system("cls");
}

void dar_de_alta_Estudiante(Nodo*& lista){
    Encabezado("ALTA DE ESTUDIANTE");

    Estudiante nuevo_Estudiante;

    do{
        cout << "Matricula: ";
        cin >> nuevo_Estudiante.matricula;
        if(validar_matricula(lista, nuevo_Estudiante.matricula)){
            cout << "Error: La matricula ya existe en el sistema" << endl;
        }
    } while(validar_matricula(lista, nuevo_Estudiante.matricula));

    cin.ignore();

    cout << "Nombre: ";
    getline(cin, nuevo_Estudiante.nombre);
    cout << "Edad: ";
    cin >> nuevo_Estudiante.edad;
    cout << "Promedio: ";
    cin >> nuevo_Estudiante.promedio;
    cin.ignore();
    cout << "Direccion: ";
    getline(cin, nuevo_Estudiante.direccion);
    cout << "Telefono: ";
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

    cout << "Alumno dado de alta correctamente" << endl;
    system("pause");
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
    return (opcion < 1 || opcion > 8);  
}

void menu(int* opcion){
    Encabezado("SISTEMA IMAK");
    cout << "MENU" << endl;
    cout << "1) Alta de estudiante" << endl;
    cout << "2) Baja de estudiante" << endl;
    cout << "3) Recuperar estudiante" << endl;
    cout << "4) Reporte de estudiantes" << endl;
    cout << "5) Control de inscripciones" << endl;
    cout << "6) Ver lista de estudiantes" << endl;  
    cout << "7) Ver pila de bajas" << endl;          
    cout << "8) Salir" << endl;                      

    cout << "Ingrese su opcion: ";
    do{
        cin >> *opcion;
        if(validar_menu_principal(*opcion)){
            cout << "Error: opcion invalida, pruebe una opcion entre 1-8: ";
        }
    } while(validar_menu_principal(*opcion));
    system("cls");
}

bool validar_matricula(Nodo* lista, int matricula){
    Nodo* actual = lista;
    while(actual != NULL){
        if(actual->datos.matricula == matricula)
            return true;
        actual = actual->siguiente;
    }
    return false;
}

bool ValidarCaracteres(string nombre){
    regex patron("^[A-Za-z ]+$");
    return regex_match(nombre, patron);
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
    if(a == NULL) return b;
    if(b == NULL) return a;

    if(a->datos.matricula <= b->datos.matricula){
        a->siguiente = merge(a->siguiente, b);
        return a;
    } else {
        b->siguiente = merge(a, b->siguiente);
        return b;
    }
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

void Encabezado(const string &titulo) {
    cout << "\n========================================" << endl;
    cout << "   " << titulo << endl;
    cout << "========================================" << endl;
}

void submenu(int *Ptropcion){
    do {
        Encabezado("BAJA DE ESTUDIANTE");
        cout << "1-Busqueda por nombre."<< endl;
        cout << "2-Busqueda por matricula."<< endl;
        cout << "3-Salir"<< endl << endl;
        cout << "Seleccionar: ";
        cin >> *Ptropcion;

        if (cin.fail() || *Ptropcion < 1 || *Ptropcion > 3) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "ERROR: opcion no valida....." << endl;
        }
    } while (cin.fail() || *Ptropcion < 1 || *Ptropcion > 3);
    system("cls");
}

void BusquedaSecuencial(Nodo*& lista, Pila*& pila){
    string nombre_busqueda;
    bool encontrado = false;
    
    cin.ignore();
    do{
        Encabezado("BUSQUEDA POR NOMBRE");
        cout << "Ingresa el nombre: ";
        getline(cin, nombre_busqueda);
        if(!ValidarCaracteres(nombre_busqueda))
            cout << "Error: Solo se aceptan caracteres!!!!!!" << endl;
    } while(!ValidarCaracteres(nombre_busqueda));
    
    Nodo *actual = lista;
    Nodo *anterior = NULL;
    
    while(actual != NULL){
        if(actual->datos.nombre == nombre_busqueda){
            encontrado = true;
        
            Encabezado("Datos del alumno");
            cout << "Matricula: " << actual->datos.matricula << endl;
            cout << "Nombre: " << actual->datos.nombre << endl;
            cout << "Edad: " << actual->datos.edad << endl;
            cout << "Promedio: " << actual->datos.promedio << endl;
            cout << "Direccion: " << actual->datos.direccion << endl;
            cout << "Telefono: " << actual->datos.telefono << endl;
            cout << "----------------------------------------" << endl;
            
            if(anterior == NULL){
                lista = actual->siguiente;
            } else {
                anterior->siguiente = actual->siguiente;
            }
            
            push(pila, actual->datos);
            Nodo* a_eliminar = actual;
            actual = actual->siguiente;   
            delete a_eliminar;
            cout << "Alumno borrado con exito...." << endl << endl;
        } else {
            anterior = actual;
            actual = actual->siguiente;
        }
    }
    
    if(!encontrado)
        cout << "No se encontro '" << nombre_busqueda << "' en la lista....." << endl;
    
    system("pause");
    system("cls");
}

int contarNodos(Nodo* lista) {
    int count = 0;
    Nodo* actual = lista;
    while (actual != NULL) {
        count++;
        actual = actual->siguiente;
    }
    return count;
}

Nodo* obtenerNodoEnIndice(Nodo* lista, int indice, Nodo** anterior) {
    *anterior = NULL;
    Nodo* actual = lista;
    for (int i = 0; i < indice && actual != NULL; i++) {
        *anterior = actual;
        actual = actual->siguiente;
    }
    return actual;
}

void BusquedaBinaria(Nodo*& lista, Pila*& pila){
    int busqueda_matricula;
    bool validar = false;
    
    Encabezado("ELIMINAR POR MATRICULA");
    
    do{
        cout << "Ingresa la matricula: ";
        cin >> busqueda_matricula;
        if(cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            validar = false;
            cout << "ERROR: Debe ser un numero entero....." << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            validar = true;
        }
    } while(!validar);

    int izquierda = 0;
    int derecha = contarNodos(lista) - 1;
    bool encontrado = false;
    
    while (izquierda <= derecha) {
        int medio = (izquierda + derecha) / 2;
        Nodo* anterior = NULL;
        Nodo* actual = obtenerNodoEnIndice(lista, medio, &anterior);
        
        if (actual == NULL) break;
        
        if (actual->datos.matricula == busqueda_matricula) {
            encontrado = true;
            Encabezado("Datos del alumno");
            cout << "Matricula: " << actual->datos.matricula << endl;
            cout << "Nombre: " << actual->datos.nombre << endl;
            cout << "Edad: " << actual->datos.edad << endl;
            cout << "Promedio: " << actual->datos.promedio << endl;
            cout << "Direccion: " << actual->datos.direccion << endl;
            cout << "Telefono: " << actual->datos.telefono << endl;
            cout << "----------------------------------------" << endl;
            
            if (anterior == NULL) {
                lista = actual->siguiente;
            } else {
                anterior->siguiente = actual->siguiente;
            }
            push(pila, actual->datos);
            delete actual;
            cout << "Alumno borrado con exito...." << endl;
            break;
            
        } else if (actual->datos.matricula < busqueda_matricula) {
            izquierda = medio + 1;
        } else {
            derecha = medio - 1;
        }
    }
    
    if(!encontrado)
        cout << "No se encontro ninguna matricula con valor " << busqueda_matricula << endl;
    
    system("pause");
    system("cls");
}
