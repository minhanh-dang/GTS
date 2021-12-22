#include "system_equation.h"
#include "Matrix.h"

SystemEquations::SystemEquations()
	:dependent_(*(new Matrix())),
	freedom_(*(new Matrix())) {
	hidden_number_ = 0;
}

SystemEquations::SystemEquations(int hidden_number)
	: dependent_(*(new Matrix(hidden_number))),
	freedom_(*(new Matrix(hidden_number, 1))) {
	hidden_number_ = hidden_number;
}

SystemEquations::~SystemEquations() {
	hidden_number_ = 0;
}

void SystemEquations::inputData() {
	cout << "Enter data of System equations: " << endl;
	cout << "Enter dependent matrix : " << endl;
	cin >> dependent_;
	cout << "Enter freedom matrix : " << endl;
	cin >> freedom_;
	cout << endl;
}

void SystemEquations::input() {
	int hidden_number, precision;
	cout << " Enter hidden number : "; cin >> hidden_number;
	cout << " Enter precision : "; cin >> precision;
	hidden_number_ = hidden_number;
	precision_ = precision;
	dependent_ = *(new Matrix(hidden_number_));
	dependent_.setPrecision(precision_);
	freedom_ = *(new Matrix(hidden_number_, 1));
	freedom_.setPrecision(precision_);
	inputData();
}

void SystemEquations::output() {

}

void SystemEquations::handleEquations() {
	if (!isHandle) {
		// Analysis Matrix: dependent = S - T;
		int size = dependent_.row();
		Matrix& S = *(new Matrix(size));
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				S.matrix_[i][j] = (i == j) ? dependent_.matrix_[i][j] : 0;
			}
		}
		Matrix& T = S - dependent_;
		// calculate: Ax = b --> x = Bx + g;
		// B = !S*T  ; g = !S*b ;
		Matrix& g = !S * freedom_;
		Matrix& B = !S * T;
		dependent_ = B;
		freedom_ = g;
	}
}

bool SystemEquations::checkDependentMatrix() {
	if (dependent_.isDominantDiagonalMatrix()) {
		cout << "Dependent Matrix is Dominant Diagonal Matrix! " << endl;
		return true;
	}
	else {
		cout << "Dependent Matrix is not Dominant Diagonal Matrix! " << endl;
		return false;
	}
}

void SystemEquations::handleSingleRepeat(int times_repeat) {
	double standard = dependent_.findStandard();
	cout << "Standard of Dependent Matrix = " << standard;
	if (standard < 1) {
		cout << "\nCan converge!" << endl;
	}
	else {
		cout << "\nCan't converge!" << endl;
		return;
	}

	cout << "Start repeat: " << endl;
	Matrix* result = new Matrix[times_repeat + 4];
	result[0] = freedom_;
	for (int i = 1; i < times_repeat + 1; i++) {
		cout << "Times " << i << " : ";
		result[i] = dependent_ * result[i - 1] + freedom_;
		cout << result[i] << endl;
	}

	double error_number = (pow(standard, times_repeat) / (1 - standard)) * (freedom_.findStandard());
	cout << "Error number = " << error_number;
}

void SystemEquations::handleSingleRepeat(double error_number) {
	double standard = dependent_.findStandard();
	cout << "Standard of Dependent Matrix = " << standard;
	if (standard < 1) {
		cout << "\nCan converge!" << endl;
	}
	else {
		cout << "\nCan't converge!" << endl;
		return;
	}

	double temp = (error_number / (freedom_.findStandard())) * (1 - standard);
	int times_repeat = 1;
	while (pow(standard, times_repeat) > temp) times_repeat++;

	cout << "Start repeat: " << endl;
	Matrix* result = new Matrix[times_repeat + 1];
	result[0] = freedom_;
	for (int i = 1; i < times_repeat + 1; i++) {
		cout << "Times " << i << " : ";
		result[i] = dependent_ * result[i - 1] + freedom_;
		cout << result[i] << endl;
	}
}

void SystemEquations::handleSeidelRepeat(int times_repeat) {
	cout << "Standard of Dependent Matrix = " << dependent_.findStandard();

	double standard = dependent_.findStandard();
	if (standard < 1) {
		cout << "\nCan converge!" << endl;
	}
	else {
		cout << "\nCan't converge!" << endl;
		return;
	}

	cout << "Start repeat: " << endl;
	Matrix* result = new Matrix[times_repeat + 1];
	result[0] = freedom_;
	for (int i = 1; i < times_repeat + 1; i++) {
		cout << "Times " << i << " : ";
		// Repeat: X(m) = B(1)*X(m) + B(2)*X(m-1) + g
		// Trong do: B1, B2 là ma trận tam giác dưới và trên được tách từ ma trận dependent
		// Khi đó X(m) = !(1 - B1) * (B(2)*X(m-1) + g
		// Vì B1 là Matrix tam giác nên !(1-B1) = 1 + B1
		// Rút gọn: X(m) = (1+B1) * (B2*(X(m-1)) +g
		Matrix& upper_triangular_matrix = dependent_.upperTriangularMatrix();
		Matrix& lower_triangular_matrix = dependent_.lowerTriangularMatrix();
		Matrix& unit_matrix = dependent_.registedUnitMatrix();
		result[i] = (unit_matrix + lower_triangular_matrix) *
			(upper_triangular_matrix * result[i - 1] + freedom_);
		cout << result[i] << endl;
	}

	// caculate error number
	double v = 0;
	for (int i = 0; i < dependent_.row(); i++) {
		double temp_left = 0, temp_right = 0;
		for (int j = 0; j < dependent_.col(); j++) {
			temp_left += (j < i) ? abs(dependent_.matrix_[i][j]) : 0;
			temp_right += (j > i) ? abs(dependent_.matrix_[i][j]) : 0;
		}
		v = max(v, temp_right / (1 - temp_left));
	}
	double error_number = pow(v, times_repeat) / (1 - v) * (freedom_.findStandard());
	cout << "Error number = " << error_number;
}

void SystemEquations::handleSeidelRepeat(double error_number) {
	cout << "Standard of Dependent Matrix = " << dependent_.findStandard();

	double standard = dependent_.findStandard();
	if (standard < 1) {
		cout << "\nCan converge!" << endl;
	}
	else {
		cout << "\nCan't converge!" << endl;
		return;
	}

	// caculate times repeat
	double temp = (error_number / (freedom_.findStandard()));
	double v = 0;
	int times_repeat = 1;
	for (int i = 0; i < dependent_.row(); i++) {
		double temp_left = 0, temp_right = 0;
		for (int j = 0; j < dependent_.col(); j++) {
			temp_left += (j < i) ? abs(dependent_.matrix_[i][j]) : 0;
			temp_right += (j > i) ? abs(dependent_.matrix_[i][j]) : 0;
		}
		v = max(v, temp_right / (1 - temp_left));
	}
	while (pow(v, times_repeat) / (1 - v) > temp) times_repeat++;

	// start repeat
	cout << "Start repeat: " << endl;
	Matrix* result = new Matrix[times_repeat + 1];
	result[0] = freedom_;
	for (int i = 1; i < times_repeat + 1; i++) {
		cout << "Times " << i << " : ";
		// Repeat: X(m) = B(1)*X(m) + B(2)*X(m-1) + g
		// Trong do: B1, B2 là ma trận tam giác dưới và trên được tách từ ma trận dependent
		// Khi đó X(m) = !(1 - B1) * (B(2)*X(m-1) + g
		// Vì B1 là Matrix tam giác nên !(1-B1) = 1 + B1
		// Rút gọn: X(m) = (1+B1) * (B2*(X(m-1)) +g
		Matrix& upper_triangular_matrix = dependent_.upperTriangularMatrix();
		Matrix& lower_triangular_matrix = dependent_.lowerTriangularMatrix();
		Matrix& unit_matrix = dependent_.registedUnitMatrix();
		result[i] = (unit_matrix + lower_triangular_matrix) *
			(upper_triangular_matrix * result[i - 1] + freedom_);
		cout << result[i] << endl;
	}
}

void SystemEquations::handleGaussSeidel() {
	if (!isHandle) {
		Matrix res = (!dependent_) * freedom_;
		cout << "Result with Gauss Seidel: " << res;
	}
}
