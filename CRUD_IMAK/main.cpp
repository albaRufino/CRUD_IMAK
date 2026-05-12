#include <iostream>
#include <string>
#include <regex>
#include <limits>
#include <cstdlib>
#include <iomanip>

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

struct ColaNodo{
    Estudiante datos;
    ColaNodo* siguiente;
};

struct Cola{
    ColaNodo* frente;
    ColaNodo* final;
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
void Encabezado(string);
void BusquedaSecuencial(Nodo*&, Pila*&);
bool ValidarCaracteres(string);
void push(Pila*&, Estudiante);
void BusquedaBinaria(Nodo*&, Pila*&);
int contarNodos(Nodo*);
Nodo* obtenerNodoEnIndice(Nodo*, int, Nodo**);
void mostrarLista(Nodo*);
void mostrarPila(Pila*);
bool pop(Pila*&, Estudiante&);
void RecuperarAlumno(Nodo*&, Pila*&);
void submenuReportes(int*);
void menuReportes(Nodo*, Pila*);
void reportePorcentajes(Nodo*);
void reporteDatosGenerales(Nodo*);
void reporteAlumnosInactivos(Pila*);
void controlInscripciones(Nodo*&);
void inicializarCola(Cola&);
void encolar(Cola&, Estudiante);
bool desencolar(Cola&, Estudiante&);
bool colaVacia(Cola&);
void liberarCola(Cola&);
void formarColaPorPromedio(Nodo*, Cola&);
void formarGrupos(Cola&);
void mostrarGrupo(Estudiante[], int, int);
bool compararEstudiante(Estudiante, Estudiante);

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
                menuReportes(lista_alumnos, pila_bajas);
                break;

            case 5:
                controlInscripciones(lista_alumnos);
                break;

            case 6:
                cout << "Saliendo..." << endl;
        }
    } while(opcion_principal != 6);

    return 0;
}

void inicializarCola(Cola& c){
    c.frente = NULL;
    c.final = NULL;
}

void encolar(Cola& c, Estudiante estudiante){
    ColaNodo* nuevo = new ColaNodo();
    nuevo->datos = estudiante;
    nuevo->siguiente = NULL;

    if(colaVacia(c)){
        c.frente = nuevo;
        c.final = nuevo;
    } else {
        c.final->siguiente = nuevo;
        c.final = nuevo;
    }
}

bool desencolar(Cola& c, Estudiante& estudiante){
    if(colaVacia(c)){
        return false;
    }

    ColaNodo* a_eliminar = c.frente;
    estudiante = a_eliminar->datos;
    c.frente = c.frente->siguiente;

    if(c.frente == NULL){
        c.final = NULL;
    }

    delete a_eliminar;
    return true;
}

bool colaVacia(Cola& cola){
    return cola.frente == NULL;
}

void liberarCola(Cola& cola){
    Estudiante temp;
    while(desencolar(cola, temp));
}

bool compararEstudiante(Estudiante a, Estudiante b){
    if(a.promedio != b.promedio){
        return a.promedio > b.promedio;
    }
    return a.nombre < b.nombre;
}

void formarColaPorPromedio(Nodo* lista, Cola& colaEspera){
    if(lista == NULL){
        cout << "No hay estudiantes activos para formar la cola." << endl;
        return;
    }

    int total = contarNodos(lista);
    if(total == 0){
        cout << "No hay estudiantes activos." << endl;
        return;
    }

    Estudiante* arreglo = new Estudiante[total];

    Nodo* actual = lista;
    int i = 0;
    while(actual != NULL && i < total){
        arreglo[i] = actual->datos;
        actual = actual->siguiente;
        i++;
    }

    for(int i = 0; i < total - 1; i++){
        for(int j = i + 1; j < total; j++){
            if(!compararEstudiante(arreglo[i], arreglo[j])){
                Estudiante temp = arreglo[i];
                arreglo[i] = arreglo[j];
                arreglo[j] = temp;
            }
        }
    }

    for(int i = 0; i < total; i++){
        encolar(colaEspera, arreglo[i]);
    }

    delete[] arreglo;

    cout << "Cola formada exitosamente con " << total << " estudiantes" << endl;
    cout << "Ordenados por promedio (mayor a menor) y nombre." << endl;
}

void mostrarGrupo(Estudiante grupo[], int tamaño, int numGrupo){
    cout << "========== GRUPO " << numGrupo << " ==========" << endl;
    for(int i = 0; i < tamaño; i++){
        cout << "----------------------------------------" << endl;
        cout << "Estudiante " << (i + 1) << ":" << endl;
        cout << "Matricula: " << grupo[i].matricula << endl;
        cout << "Nombre: " << grupo[i].nombre << endl;
        cout << "Edad: " << grupo[i].edad << endl;
        cout << "Promedio: " << grupo[i].promedio << endl;
        cout << "Direccion: " << grupo[i].direccion << endl;
        cout << "Telefono: " << grupo[i].telefono << endl;
    }
    cout << "========================================\n" << endl;
}

void formarGrupos(Cola& colaEspera){
    if(colaVacia(colaEspera)){
        cout << "La cola de espera esta vacia, primero forme la cola" << endl;
        return;
    }

    int tamanoGrupo;
    cout << "Ingrese el tamano de cada grupo: ";
    cin >> tamanoGrupo;

    if(tamanoGrupo <= 0){
        cout << "Tamano de grupo invalido" << endl;
        return;
    }

    int totalEstudiantes = 0;
    ColaNodo* temp = colaEspera.frente;
    while(temp != NULL){
        totalEstudiantes++;
        temp = temp->siguiente;
    }

    if(totalEstudiantes == 0){
        cout << "No hay estudiantes en la cola" << endl;
        return;
    }

    int numGrupos = (totalEstudiantes + tamanoGrupo - 1) / tamanoGrupo;
    cout << "Se formaran " << numGrupos << " grupos" << endl;
    cout << "Total de estudiantes: " << totalEstudiantes << endl;

    Estudiante* grupoActual = new Estudiante[tamanoGrupo];
    int grupoIndex = 0;
    int numGrupoActual = 1;
    Estudiante estudiante;

    while(desencolar(colaEspera, estudiante)){
        grupoActual[grupoIndex] = estudiante;
        grupoIndex++;

        if(grupoIndex == tamanoGrupo){
            mostrarGrupo(grupoActual, grupoIndex, numGrupoActual);
            numGrupoActual++;
            grupoIndex = 0;
        }
    }

    if(grupoIndex > 0){
        mostrarGrupo(grupoActual, grupoIndex, numGrupoActual);
    }

    delete[] grupoActual;

    cout << "Todos los estudiantes han sido inscritos en sus grupos" << endl;
    cout << "La cola de espera ha quedado vacia" << endl;
}

void controlInscripciones(Nodo*& lista){
    Encabezado("CONTROL DE INSCRIPCIONES");

    if(lista == NULL){
        cout << "No hay estudiantes activos registrados" << endl;
        cout << "Por favor, de alta estudiantes primero" << endl;
        system("pause");
        system("cls");
        return;
    }

    Cola colaEspera;
    inicializarCola(colaEspera);

    int opcion;
    do{
        Encabezado("Control de inscripciones");
        cout << "1) Formar cola de espera (por promedio)" << endl;
        cout << "2) Formar grupos e inscribir estudiantes" << endl;
        cout << "3) Volver al menu principal" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch(opcion){
            case 1:
                formarColaPorPromedio(lista, colaEspera);
                break;
            case 2:
                formarGrupos(colaEspera);
                break;
            case 3:
                liberarCola(colaEspera);
                cout << "Volviendo al menu principal..." << endl;
                break;
            default:
                cout << "Opcion invalida" << endl;
        }

        if(opcion != 3){
            cout << endl;
            system("cls");
        }

    } while(opcion != 3);
}

void submenuReportes(int* opcion){
    do {
        Encabezado("REPORTE DE ESTUDIANTES");
        cout << "1) Porcentajes (aprobados / reprobados)" << endl;
        cout << "2) Datos generales de alumnos activos"   << endl;
        cout << "3) Alumnos inactivos (pila de bajas)"    << endl;
        cout << "4) Regresar"                              << endl << endl;
        cout << "Seleccionar: ";
        cin >> *opcion;

        if (cin.fail() || *opcion < 1 || *opcion > 4) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "ERROR: opcion no valida....." << endl;
        }
    } while (cin.fail() || *opcion < 1 || *opcion > 4);
    system("cls");
}

void menuReportes(Nodo* lista, Pila* pila){
    int opcion = 0;
    do {
        submenuReportes(&opcion);
        switch(opcion){
            case 1: reportePorcentajes(lista);
            break;

            case 2: reporteDatosGenerales(lista);
            break;

            case 3: reporteAlumnosInactivos(pila);
            break;
        }
    } while(opcion != 4);
}

void reportePorcentajes(Nodo* lista){
    Encabezado("REPORTE - PORCENTAJES");

    if(lista == NULL){
        cout << "No hay estudiantes registrados" << endl;
        system("pause");
        system("cls");
        return;
    }

    int total = 0, aprobados = 0, reprobados = 0;
    Nodo* actual = lista;
    while(actual != NULL){
        total++;
        if(actual->datos.promedio >= 6.0f)
            aprobados++;
        else
            reprobados++;
        actual = actual->siguiente;
    }

    float pct_aprobados  = (float)aprobados  / total * 100.0f;
    float pct_reprobados = (float)reprobados / total * 100.0f;

    cout << fixed << setprecision(2);
    cout << "Total de alumnos activos : " << total     << endl;
    cout << "Alumnos aprobados        : " << aprobados  << "  (" << pct_aprobados  << " %)" << endl;
    cout << "Alumnos reprobados       : " << reprobados << "  (" << pct_reprobados << " %)" << endl;

    system("pause");
    system("cls");
}

void reporteDatosGenerales(Nodo* lista){
    Encabezado("REPORTE - DATOS GENERALES DE ALUMNOS ACTIVOS");

    if(lista == NULL){
        cout << "No hay estudiantes registrados" << endl;
        system("pause");
        system("cls");
        return;
    }

    Nodo* actual = lista;
    int contador = 1;
    while(actual != NULL){
        cout << "\n--- Alumno " << contador++ << " ---" << endl;
        cout << "Nombre    : " << actual->datos.nombre    << endl;
        cout << "Edad      : " << actual->datos.edad      << endl;
        cout << "Direccion : " << actual->datos.direccion << endl;
        cout << "Telefono  : " << actual->datos.telefono  << endl;
        cout << "----------------------------------------" << endl;
        actual = actual->siguiente;
    }

    system("pause");
    system("cls");
}

void reporteAlumnosInactivos(Pila* pila){
    Encabezado("REPORTE - ALUMNOS INACTIVOS");

    if(pila == NULL){
        cout << "No hay alumnos en la pila de bajas" << endl;
        system("pause");
        system("cls");
        return;
    }

    Pila* actual = pila;
    int contador = 1;
    cout << "\n" << left << setw(6) << "#"
                 << setw(12) << "Matricula"
                 << "Nombre" << endl;
    cout << "------------------------------------" << endl;
    while(actual != NULL){
        cout << left << setw(6)  << contador++
                     << setw(12) << actual->datos.matricula
                     << actual->datos.nombre << endl;
        actual = actual->abajo;
    }

    system("pause");
    system("cls");
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
    return (opcion < 1 || opcion > 6);
}

void menu(int* opcion){
    Encabezado("SISTEMA IMAK");
    cout << "MENU" << endl;
    cout << "1) Alta de estudiante" << endl;
    cout << "2) Baja de estudiante" << endl;
    cout << "3) Recuperar estudiante" << endl;
    cout << "4) Reporte de estudiantes" << endl;
    cout << "5) Control de inscripciones" << endl;
    cout << "6) Salir" << endl;

    cout << "Ingrese su opcion: ";
    do{
        cin >> *opcion;
        if(validar_menu_principal(*opcion)){
            cout << "Error: opcion invalida, pruebe una opcion entre 1-6: ";
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

void Encabezado(string titulo) {
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
