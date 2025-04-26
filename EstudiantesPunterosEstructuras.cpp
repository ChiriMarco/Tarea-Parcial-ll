#include <iostream>
#include <string>
using namespace std;

// Definir la estructura Estudiante
struct Estudiante {
    int id;
    string nombres;
    string apellidos;
    float nota1, nota2, nota3, nota4;
    float promedio;
};

// Función para calcular el promedio
float calcularPromedio(float n1, float n2, float n3, float n4) {
    return (n1 + n2 + n3 + n4) / 4.0;
}

int main() {
    int n;
    cout << "Ingrese la cantidad de estudiantes: ";
    cin >> n;

    // Crear arreglo dinámico de estudiantes
    Estudiante* estudiantes = new Estudiante[n];

    // Ingresar datos
    for (int i = 0; i < n; i++) {
        cout << "\nEstudiante #" << (i + 1) << endl;
        cout << "Ingrese ID: ";
        cin >> (estudiantes + i)->id;
        cin.ignore();

        cout << "Ingrese Nombres: ";
        getline(cin, (estudiantes + i)->nombres);

        cout << "Ingrese Apellidos: ";
        getline(cin, (estudiantes + i)->apellidos);

        cout << "Ingrese Nota 1: ";
        cin >> (estudiantes + i)->nota1;
        cout << "Ingrese Nota 2: ";
        cin >> (estudiantes + i)->nota2;
        cout << "Ingrese Nota 3: ";
        cin >> (estudiantes + i)->nota3;
        cout << "Ingrese Nota 4: ";
        cin >> (estudiantes + i)->nota4;

        // Calcular promedio
        (estudiantes + i)->promedio = calcularPromedio(
            (estudiantes + i)->nota1,
            (estudiantes + i)->nota2,
            (estudiantes + i)->nota3,
            (estudiantes + i)->nota4
        );
    }

    // Mostrar resultados
    cout << "\n----- Resultados -----\n";
    for (int i = 0; i < n; i++) {
        cout << "\nEstudiante #" << (i + 1) << endl;
        cout << "ID: " << (estudiantes + i)->id << endl;
        cout << "Nombre Completo: " << (estudiantes + i)->nombres << " " << (estudiantes + i)->apellidos << endl;
        cout << "Promedio: " << (estudiantes + i)->promedio << endl;

        if ((estudiantes + i)->promedio >= 60) {
            cout << "Estado: Aprobado ✅" << endl;
        } else {
            cout << "Estado: Reprobado ❌" << endl;
        }
    }

    // Liberar memoria
    delete[] estudiantes;

    return 0;
}
