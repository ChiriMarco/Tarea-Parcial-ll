#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Estructura del Estudiante
struct Estudiante {
    int id;
    string nombres;
    string apellidos;
    float nota1, nota2, nota3, nota4;
    float promedio;
    string resultado;
};

// Función para calcular el promedio
float calcularPromedio(float n1, float n2, float n3, float n4) {
    return (n1 + n2 + n3 + n4) / 4.0;
}

// Función para calcular el resultado (Aprobado o Reprobado)
string obtenerResultado(float promedio) {
    return (promedio >= 60) ? "Aprobado" : "Reprobado";
}

// Función para guardar estudiantes (CREATE)
void agregarEstudiantes() {
    int n;
    cout << "Ingrese la cantidad de estudiantes a agregar: ";
    cin >> n;

    ofstream archivo("notas.dat", ios::binary | ios::app);

    if (!archivo) {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }

    Estudiante estudiante;

    for (int i = 0; i < n; i++) {
        cout << "\nEstudiante #" << (i + 1) << endl;
        cout << "Ingrese ID: ";
        cin >> estudiante.id;
        cin.ignore();

        cout << "Ingrese Nombres: ";
        getline(cin, estudiante.nombres);

        cout << "Ingrese Apellidos: ";
        getline(cin, estudiante.apellidos);

        cout << "Ingrese Nota 1: ";
        cin >> estudiante.nota1;
        cout << "Ingrese Nota 2: ";
        cin >> estudiante.nota2;
        cout << "Ingrese Nota 3: ";
        cin >> estudiante.nota3;
        cout << "Ingrese Nota 4: ";
        cin >> estudiante.nota4;

        estudiante.promedio = calcularPromedio(estudiante.nota1, estudiante.nota2, estudiante.nota3, estudiante.nota4);
        estudiante.resultado = obtenerResultado(estudiante.promedio);

        archivo.write(reinterpret_cast<char*>(&estudiante), sizeof(Estudiante));
    }

    archivo.close();
    cout << "\nEstudiantes agregados correctamente.\n";
}

// Función para leer estudiantes (READ)
void mostrarEstudiantes() {
    ifstream archivo("notas.dat", ios::binary);

    if (!archivo) {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }

    Estudiante estudiante;
    cout << "\n----- Lista de Estudiantes -----\n";

    while (archivo.read(reinterpret_cast<char*>(&estudiante), sizeof(Estudiante))) {
        cout << "\nID: " << estudiante.id << endl;
        cout << "Nombre Completo: " << estudiante.nombres << " " << estudiante.apellidos << endl;
        cout << "Notas: " << estudiante.nota1 << ", " << estudiante.nota2 << ", "
             << estudiante.nota3 << ", " << estudiante.nota4 << endl;
        cout << "Promedio: " << estudiante.promedio << endl;
        cout << "Resultado: " << estudiante.resultado << endl;
    }

    archivo.close();
}

// Función para actualizar estudiante (UPDATE)
void actualizarEstudiante() {
    fstream archivo("notas.dat", ios::binary | ios::in | ios::out);

    if (!archivo) {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }

    int idBuscar;
    cout << "Ingrese el ID del estudiante que desea actualizar: ";
    cin >> idBuscar;

    Estudiante estudiante;
    bool encontrado = false;

    while (archivo.read(reinterpret_cast<char*>(&estudiante), sizeof(Estudiante)) && !encontrado) {
        if (estudiante.id == idBuscar) {
            cout << "\nEstudiante encontrado. Ingrese los nuevos datos:\n";

            cout << "Ingrese Nombres: ";
            cin.ignore();
            getline(cin, estudiante.nombres);

            cout << "Ingrese Apellidos: ";
            getline(cin, estudiante.apellidos);

            cout << "Ingrese Nota 1: ";
            cin >> estudiante.nota1;
            cout << "Ingrese Nota 2: ";
            cin >> estudiante.nota2;
            cout << "Ingrese Nota 3: ";
            cin >> estudiante.nota3;
            cout << "Ingrese Nota 4: ";
            cin >> estudiante.nota4;

            estudiante.promedio = calcularPromedio(estudiante.nota1, estudiante.nota2, estudiante.nota3, estudiante.nota4);
            estudiante.resultado = obtenerResultado(estudiante.promedio);

            // Volver atrás en el archivo para sobrescribir
            archivo.seekp(-sizeof(Estudiante), ios::cur);
            archivo.write(reinterpret_cast<char*>(&estudiante), sizeof(Estudiante));

            encontrado = true;
            cout << "\nEstudiante actualizado exitosamente.\n";
        }
    }

    if (!encontrado) {
        cout << "Estudiante con ID " << idBuscar << " no encontrado.\n";
    }

    archivo.close();
}

// Función para eliminar estudiante (DELETE)
void eliminarEstudiante() {
    ifstream archivoLectura("notas.dat", ios::binary);
    ofstream archivoTemporal("temp.dat", ios::binary);

    if (!archivoLectura || !archivoTemporal) {
        cout << "No se pudo abrir uno de los archivos." << endl;
        return;
    }

    int idEliminar;
    cout << "Ingrese el ID del estudiante que desea eliminar: ";
    cin >> idEliminar;

    Estudiante estudiante;
    bool encontrado = false;

    while (archivoLectura.read(reinterpret_cast<char*>(&estudiante), sizeof(Estudiante))) {
        if (estudiante.id != idEliminar) {
            archivoTemporal.write(reinterpret_cast<char*>(&estudiante), sizeof(Estudiante));
        } else {
            encontrado = true;
        }
    }

    archivoLectura.close();
    archivoTemporal.close();

    remove("notas.dat");
    rename("temp.dat", "notas.dat");

    if (encontrado) {
        cout << "\nEstudiante eliminado correctamente.\n";
    } else {
        cout << "\nNo se encontró el estudiante con ID " << idEliminar << ".\n";
    }
}

// Función principal
int main() {
    int opcion;

    do {
        cout << "\n===== MENU CRUD DE ESTUDIANTES =====\n";
        cout << "1. Agregar Estudiantes\n";
        cout << "2. Mostrar Estudiantes\n";
        cout << "3. Actualizar Estudiante\n";
        cout << "4. Eliminar Estudiante\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                agregarEstudiantes();
                break;
            case 2:
                mostrarEstudiantes();
                break;
            case 3:
                actualizarEstudiante();
                break;
            case 4:
                eliminarEstudiante();
                break;
            case 5:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo.\n";
        }
    } while (opcion != 5);

    return 0;
}
