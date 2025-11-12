#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct Expense {
    string category;
    string description;
    double amount;
};

void addExpense(vector<Expense>& expenses) {
    Expense e;
    cout << "\nIngrese la categoría del gasto (Ejemplo: comida, transporte, ocio, etc.): ";
    getline(cin, e.category);
    cout << "\nIngrese la descripción del gasto: ";
    getline(cin, e.description);
    
    while (true) {
        cout << "Ingrese el monto: $";
        string line;
        getline(cin, line);
        try {
            e.amount = stod(line);
            if (e.amount < 0) {
                cout << "El monto no puede ser negativo, porfavor intenta de nuevo\n";
                continue;
            }
            break;
        } catch (...) {
            cout << "Entrada inválida, porfavor ingrese un número\n";
        }
    }
    expenses.push_back(e);
    cout << "Gasto agregado correctamente\n";
}
void showSummary(const vector<Expense>& expenses) {
    if (expenses.empty()) {
        cout << "No hay gastos registrados\n";
        return;
    }

    map<string, double> summary;

    for (int i = 0; i < expenses.size(); i++) {
        summary[expenses[i].category] += expenses[i].amount;
    }

    double totalGastado = 0.0;
    cout << "\n=== Resumen de gastos ===\n";
    cout << fixed << setprecision(2);

    for(const auto& par : summary) {
        cout << "Categoría: " << par.first << ", total: " << par.second << '\n';
        totalGastado += par.second;
    }

    cout << "-------------------------\n";
    cout << "Total general: $" << totalGastado << '\n';
}
void listExpenses(const vector<Expense>& expenses) {
    if (expenses.empty()) {
        cout << "No hay gastos registrados\n";
        return;
    }

    cout << '\n' 
        << left << setw(5) << "N°"
        << left << setw(15) << "Categoría"
        << left << setw(30) << "Descripción"
        << left << setw(10) << "Monto" << '\n';

    cout << string(60, '-') << '\n';
    cout << fixed << setprecision(2);
    
    double totalGeneral = 0.0;

    for (int i = 0; i < expenses.size(); i++) {
        cout << left << setw(5) << i + 1
            << left << setw(15) << expenses[i].category
            << left << setw(30) << expenses[i].description
            << right << "$" << setw(9) << expenses[i].amount << "\n";
            totalGeneral += expenses[i].amount;
    } 
    cout << string(60, '-') << "\n";
    cout << "Total de compras: $" << totalGeneral << '\n';
}
void exportToCSV(const vector<Expense>& expenses) {
    if(expenses.empty()) {
        cout << "No hay gastos para exportar";
        return;
    }

    double totalGeneral = 0.0;
    for (const auto& e : expenses) {
        totalGeneral += e.amount;
    }

    ofstream myFile("gastos.csv");
    if (myFile.is_open()) {
        myFile << "Categoria, Descripción, Monto\n";

        for (int i = 0; i < expenses.size(); i++) {
            myFile << "\"" << expenses[i].category << "\","
            << "\"" << expenses[i].description << "\","
            << fixed << setprecision(2) << expenses[i].amount << "\n";
        }

        myFile << ",\"Total general\"," << fixed << setprecision(2) << totalGeneral;

        myFile.close();
        cout << "Gastos exportados correctamente a gastos.csv\n";
    } else {
        cout << "Error al crear el archivo\n";
        return;
    }
}

int main() {
    cout << "Bienvenido a BudgetMate!" << endl;
    vector<Expense> expenses;
    int option;

    do {
        cout << "\n=== BudgetMate ===\n";
        cout << "1. Agregar gasto\n";
        cout << "2. Mostrar resumen\n";
        cout << "3. Ver todos los gastos\n";
        cout << "4. Exportar a CSV\n";
        cout << "0. Salir\n";
        cout << "Opción: ";
        if (!(cin >> option)) {
            cin.clear();
            cin.ignore(10000, '\n');
            option = -1;
        }
        cin.ignore();

        switch(option) {
            case 1: addExpense(expenses);
            break;
            case 2: showSummary(expenses);
            break;
            case 3: listExpenses(expenses);
            break;
            case 4: exportToCSV(expenses);
            break;
            case 0: cout << "Saliendo del programa...\n";
            break;
            
            default: cout << "Opción no valida\n";
        }
    } while (option != 0);

    return 0;
}