#include <iostream>
#include <string>
using namespace std;

int main() {
    int n; // Número de estudiantes
    cout << "Ingrese la cantidad de estudiantes: ";
    cin >> n;

    // Declarar los arreglos
    int id[n];
    string nombres[n];
    string apellidos[n];
    float nota1[n], nota2[n], nota3[n], nota4[n];
    float promedio[n];

    // Ingreso de datos
    for (int i = 0; i < n; i++) {
        cout << "\nEstudiante #" << (i + 1) << endl;
        cout << "Ingrese ID: ";
        cin >> id[i];
        cin.ignore(); // Limpiar buffer

        cout << "Ingrese Nombres: ";
        getline(cin, nombres[i]);

        cout << "Ingrese Apellidos: ";
        getline(cin, apellidos[i]);

        cout << "Ingrese Nota 1: ";
        cin >> nota1[i];
        cout << "Ingrese Nota 2: ";
        cin >> nota2[i];
        cout << "Ingrese Nota 3: ";
        cin >> nota3[i];
        cout << "Ingrese Nota 4: ";
        cin >> nota4[i];

        // Calcular promedio
        promedio[i] = (nota1[i] + nota2[i] + nota3[i] + nota4[i]) / 4.0;
    }

    // Mostrar resultados
    cout << "\n----- Resultados -----\n";
    for (int i = 0; i < n; i++) {
        cout << "\nEstudiante #" << (i + 1) << endl;
        cout << "ID: " << id[i] << endl;
        cout << "Nombre Completo: " << nombres[i] << " " << apellidos[i] << endl;
        cout << "Promedio: " << promedio[i] << endl;

        if (promedio[i] >= 60) {
            cout << "Estado: Aprobado ✅" << endl;
        } else {
            cout << "Estado: Reprobado ❌" << endl;
        }
    }

    return 0;
}
