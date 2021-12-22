#include "menu.h"

#include <string>
#include <iostream>
#include <Windows.h>

#include "system_equation.h"

using namespace std;


void menuTotal() {
    string menu = "Enter your selection : "
        "\n\t1.Solve the system of equations with Single repeat."
        "\n\t2.Solve the system of equations with Seidel repeat."
        "\n\t3.Solve the system of equations with Gauss Jordan."
        "\n\t4.Do Math With Matrix."
        "\n\t0.Exit.\n";
    int choice = 0;
    do {
        system("cls");
        cout << menu;
        cout << "Enter your selection : "; cin >> choice;

        switch (choice) {
            cout << "Thanks for use our program! . . ." << endl;
            cout << "_________________________________________________________";
        case kExitTatalMenu:
            break;
        case kCalculateWithSingleRepeat:
            menuSingleRepeat();
            break;
        case kCalculateWithSeidelRepeat:
            menuSeidelRepeat();
            break;
        case kCalculateWithGaussSeidel: {
            cout << "----- Input -----" << endl;
            equations_->input();
            equations_->handleGaussSeidel();
            continueOption();
            break;
        }
        case kDoMathWithMatrix:
            menuMathMatix();
            break;

        default:
            cout << "Your selection is invalid. Please re-enter!" << endl;
            Sleep(1800);
            break;
        }
    } while (choice != kExitTatalMenu);
}

void menuSingleRepeat() {
    string menu = "Enter your selection : "
        "\n\t1.Solve the system of equations with times repeat."
        "\n\t2.Solve the system of equations with error number."
        "\n\t0.Exit.\n";
    int choice = 0;
    do {
        system("cls");
        cout << menu;
        cout << "Enter your selection : "; cin >> choice;

        switch (choice) {
        case kExitSubMenu:
            break;
        case kRepeatWithTimesRepeat: {
            cout << "----- Input -----" << endl;
            equations_->input();
            int times_repeat = 0;
            cout << "Enter times repeat >> "; cin >> times_repeat;
            cout << "----- Caculate -----" << endl;
            equations_->handleEquations();
            equations_->handleSingleRepeat(times_repeat);
            cout << "----- Sussess -----" << endl;
            continueOption();
            break;
        }
        case kRepeatWithErrorNumber: {
            cout << "----- Input -----" << endl;
            equations_->input();
            double error_number = 0;
            cout << "----- Caculate -----" << endl;
            cout << "Enter error number >> "; cin >> error_number;
            equations_->handleSingleRepeat(error_number);
            cout << "----- Sussess -----" << endl;
            continueOption();
            break;
        }

        default:
            cout << "Your selection is invalid. Please re-enter!" << endl;
            Sleep(1800);
            break;
        }
    } while (choice != kExitSubMenu);
}

void menuSeidelRepeat() {
    string menu = "Enter your selection : "
        "\n\t1.Solve the system of equations with times repeat."
        "\n\t2.Solve the system of equations with error number."
        "\n\t0.Exit.\n";
    int choice = 0;
    do {
        system("cls");
        cout << menu;
        cout << "Enter your selection : "; cin >> choice;

        switch (choice) {
        case kExitSubMenu:
            break;
        case kRepeatWithTimesRepeat: {
            cout << "----- Input -----" << endl;
            equations_->input();
            int times_repeat = 0;
            cout << "Enter times repeat >> "; cin >> times_repeat;
            cout << "----- Caculate -----" << endl;
            equations_->handleEquations();
            equations_->handleSeidelRepeat(times_repeat);
            cout << "----- Sussess -----" << endl;
            continueOption();
            break;
        }
        case kRepeatWithErrorNumber: {
            cout << "----- Input -----" << endl;
            equations_->input();
            double error_number = 0;
            cout << "----- Caculate -----" << endl;
            cout << "Enter error number >> "; cin >> error_number;
            equations_->handleSeidelRepeat(error_number);
            cout << "----- Sussess -----" << endl;
            continueOption();
            break;
        }

        default:
            cout << "Your selection is invalid. Please re-enter!" << endl;
            Sleep(1800);
            break;
        }
    } while (choice != kExitSubMenu);
}

void menuMathMatix() {
    string menu = "Enter your selection : "
        "\n\t1.Add two matrices."
        "\n\t2.Subtract two matrices."
        "\n\t3.Multiply two matrices."
        "\n\t4.Find the inverse matrix."
        "\n\t0.Exit.\n";
    int choice = 0;
    do {
        system("cls");
        cout << menu;
        cout << "Enter your selection : "; cin >> choice;

        switch (choice) {
        case kExitMatrixMenu:
            break;
        case kAddMatrix: {
            int row, col;
            cout << "\nEnter row number : "; cin >> row;
            cout << "Enter col number : "; cin >> col;
            Matrix mat1(row, col);
            Matrix mat2(row, col);
            cout << "Enter Matrix 1:"; cin >> mat1;
            cout << "Enter Matrix 2:"; cin >> mat2;
            cout << "Result: " << mat1 + mat2;
            continueOption();
            break;
        }
        case kSubMatrix: {
            int row, col;
            cout << "\nEnter row number : "; cin >> row;
            cout << "Enter col number : "; cin >> col;
            Matrix mat1(row, col);
            Matrix mat2(row, col);
            cout << "Enter Matrix 1:"; cin >> mat1;
            cout << "Enter Matrix 2:"; cin >> mat2;
            cout << "Result: " << mat1 - mat2;
            continueOption();
            break;
        }
        case kMulMatrix: {
            int row, col;
            cout << "\nEnter row number : "; cin >> row;
            cout << "Enter col number : "; cin >> col;
            Matrix mat1(row, col);
            Matrix mat2(row, col);
            cout << "Enter Matrix 1:"; cin >> mat1;
            cout << "Enter Matrix 2:"; cin >> mat2;
            cout << "Result: " << mat1 * mat2;
            continueOption();
            break;
        }
        case kInvMatrix: {
            int size;
            cout << "\nEnter size of Matrix : "; cin >> size;
            Matrix mat(size);
            cout << "Enter Matrix : "; cin >> mat;
            cout << "Result: " << !mat;
            continueOption();
            break;
        }

        default:
            cout << "Your selection is invalid. Please re-enter!" << endl;
            Sleep(1800);
            break;
        }
    } while (choice != kExitMatrixMenu);
}

void continueOption() {
    int choice;
    do {
        cout << "\n-------------------------------\n";
        cout << "<<Enter 0 to continue >>... ";
        cin >> choice;
        cin.ignore();
    } while (choice != 0);
}
