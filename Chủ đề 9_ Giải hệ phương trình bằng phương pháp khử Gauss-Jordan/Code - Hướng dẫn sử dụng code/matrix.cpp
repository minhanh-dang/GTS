#include <iomanip>

#include "Matrix.h"

using namespace std;

Matrix::Matrix() {
	matrix_ = alloc(0, 0);
}

Matrix::Matrix(int size) {
	matrix_ = alloc(size, size);
}

Matrix::Matrix(int row, int col) {
	matrix_ = alloc(row, col);
}

Matrix::Matrix(const Matrix& other) {
	matrix_ = alloc(other.row_, other.col_);
	for (int i = 0; i < row_; i++) {
		for (int j = 0; j < col_; j++) {
			matrix_[i][j] = other.matrix_[i][j];
		}
	}
}

Matrix::~Matrix() {
	dealloc();
}

double** Matrix::alloc(int row, int col) {
	row_ = row;
	col_ = col;
	double** new_matrix = new double* [row];
	for (int i = 0; i < row; i++) {
		new_matrix[i] = new double[col];
	}
	return new_matrix;
}

void Matrix::dealloc() {
	for (int i = 0; i < row_; i++) {
		delete[] matrix_[i];
	}
	delete[] matrix_;
}

int Matrix::row() {
	return row_;
}

int Matrix::col() {
	return col_;
}

double** Matrix::setSize(int row, int col) {
	if (row > row_ && col > col_) {
		double** new_matrix = alloc(row, col);
		for (int i = 0; i < row_; i++) {
			new_matrix[i] = matrix_[i];
		}
		dealloc();
		return new_matrix;
	}
	else return matrix_;
}

double* Matrix::getMatrix() {
	return matrix_[0];
}

double* Matrix::getRow(int row) {
	if (row > row_) {
		cout << "Error: Can not get row " << row << " of Matrix!";
	}
	else {
		return matrix_[row];
	}
}

double* Matrix::getCol(int col) {
	if (col > col_) {
		cout << "Error: Can not get col " << col << " of Matrix!";
	}
	else {
		return &matrix_[0][col];
	}
}

void Matrix::setRow(double* row_value, int row) {
	if (row > row_) {
		cout << "Error: dong " << row << " khong ton tai trong ma tran!";
	}
	else {
		matrix_[row] = row_value;
	}
}

void Matrix::setCol(double* col_value, int col) {
	if (col > col_) {
		cout << "Error: cot " << col << " khong ton tai trong ma tran!";
	}
	else {
		for (int i = 0; i < row_; i++) {
			matrix_[i][col] = col_value[i];
		}
	}
}

bool Matrix::isSquareMatrix()
{
	return (row_ == col_);
}

Matrix& Matrix::registedUnitMatrix()
{
	if (isSquareMatrix()) {
		Matrix* result = new Matrix(row_, col_);
		for (int i = 0; i < row_; i++) {
			for (int j = 0; j < col_; j++) {
				result->matrix_[i][j] = (i == j) ? 1 : 0;
			}
		}
		return *result;
	}
}

Matrix& Matrix::upperTriangularMatrix() {
	if (isSquareMatrix()) {
		Matrix* result = new Matrix(row_, col_);
		for (int i = 0; i < row_; i++) {
			for (int j = 0; j < col_; j++) {
				result->matrix_[i][j] = (i >= j) ? matrix_[i][j] : 0;
			}
		}
		return *result;
	}
}

Matrix& Matrix::lowerTriangularMatrix() {
	if (isSquareMatrix()) {
		Matrix* result = new Matrix(row_, col_);
		for (int i = 0; i < row_; i++) {
			for (int j = 0; j < col_; j++) {
				result->matrix_[i][j] = (i < j) ? matrix_[i][j] : 0;
			}
		}
		return *result;
	}
}

Matrix& Matrix::operator+(const Matrix& rhs) {
	Matrix* result = new Matrix(row_, col_);
	if (row_ == rhs.row_ && col_ == rhs.col_) {
		for (int i = 0; i < row_; i++) {
			for (int j = 0; j < col_; j++) {
				result->matrix_[i][j] = matrix_[i][j] + rhs.matrix_[i][j];
			}
		}
	}
	else {
		cout << "Invalid Addition!" << endl;
		for (int i = 0; i < row_; i++) {
			for (int j = 0; j < col_; j++) {
				result->matrix_[i][j] = NULL;
			}
		}
	}
	return *result;
}

Matrix& Matrix::operator-(const Matrix& rhs) {
	Matrix* result = new Matrix(row_, col_);
	if (row_ == rhs.row_ && col_ == rhs.col_) {
		for (int i = 0; i < row_; i++) {
			for (int j = 0; j < col_; j++) {
				result->matrix_[i][j] = matrix_[i][j] - rhs.matrix_[i][j];
			}
		}
	}
	else {
		cout << "Invalid Subtraction!" << endl;
		for (int i = 0; i < row_; i++) {
			for (int j = 0; j < col_; j++) {
				result->matrix_[i][j] = NULL;
			}
		}
	}
	return *result;
}

Matrix& Matrix::operator*(const Matrix& rhs) {
	Matrix* result = new Matrix(row_, rhs.col_);
	if (col_ == rhs.row_) {
		for (int i = 0; i < row_; i++) {
			for (int j = 0; j < rhs.col_; j++) {
				result->matrix_[i][j] = 0;
				for (int k = 0; k < col_; k++) {
					result->matrix_[i][j] += matrix_[i][k] * rhs.matrix_[k][j];
				}
			}
		}
	}
	else {
		cout << "Invalid Multiplication!" << endl;
		for (int i = 0; i < row_; i++) {
			for (int j = 0; j < rhs.col_; j++) {
				result->matrix_[i][j] = NULL;
			}
		}
	}
	return *result;
}

Matrix& Matrix::operator!() {
	// handle with Gauss Jordan
	if (row_ != col_) {
		cout << "Matrix is not Square Matrix!. Invalid Inverse!";
		return *(new Matrix());
	}
	else {
		int size = row_;
		Matrix* temp_matrix = new Matrix(size);
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				temp_matrix->matrix_[i][j] = matrix_[i][j];
			}
		}
		Matrix* result = new Matrix(size);
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				result->matrix_[i][j] = (i == j) ? 1 : 0;
			}
		}
		for (int i = 0; i < size; i++) {
			// find row to swap
			int r = i;
			for (int j = i + 1; j < size; j++) {
				if (abs(temp_matrix->matrix_[j][i] > abs(matrix_[r][i]))) r = j;
			}
			if (abs(temp_matrix->matrix_[r][i]) < 1.0E-8) {
				cout << "Error: Invalid Inverse!";
				return *result;
			}

			// swap row r,i
			for (int j = 0; j < size; j++) {
				double* temp = temp_matrix->getRow(i);
				temp_matrix->setRow(temp_matrix->getRow(r), i);
				temp_matrix->setRow(temp, r);
				temp = result->getRow(i);
				result->setRow(result->getRow(r), i);
				result->setRow(temp, r);
			}

			// Divide row i by matrix[i][i]
			double div_number = temp_matrix->matrix_[i][i];
			for (int j = 0; j < size; j++) {
				temp_matrix->matrix_[i][j] /= div_number;
				result->matrix_[i][j] /= div_number;
			}

			// handle col i: make matrix[j][i] = 0 for j != i
			for (int j = 0; j < size; j++) {
				if (j != i) {
					double temp = temp_matrix->matrix_[j][i];
					for (int k = 0; k < size; k++) {
						temp_matrix->matrix_[j][k] -= temp * temp_matrix->matrix_[i][k];
						result->matrix_[j][k] -= temp * result->matrix_[i][k];
					}
				}
			}
		}
		return *result;
	}
}

bool Matrix::isDominantDiagonalMatrix() {
	bool check = true;
	for (int i = 0; i < row_; i++) {
		double temp = 0;
		for (int j = 0; j < col_; j++) {
			temp += ((i == j) ? 0 : abs(matrix_[i][j]));
		}
		if (abs(matrix_[i][i]) <= temp) check = false;
	}
	return check;
}

double Matrix::findStandard() {
	double standard = 0;
	for (int i = 0; i < row_; i++) {
		double temp = 0;
		for (int j = 0; j < col_; j++) {
			temp += abs(matrix_[i][j]);
		}
		standard = max(standard, temp);
	}
	return standard;
}

void Matrix::setPrecision(int precision) {
	precision_ = precision;
}

ostream& operator<<(ostream& os, const Matrix& rhs) {
	os << setprecision(rhs.precision_) << setiosflags(ios::showpoint);
	for (int i = 0; i < rhs.row_; ++i) {
		os << "\n";
		for (int j = 0; j < rhs.col_; ++j)
			os << setw(rhs.precision_ + 4) << rhs.matrix_[i][j];
	}
	os << "\n";
	return os;
}

istream& operator>>(istream& is, const Matrix& rhs) {
	cout << "Enter elements :\n";
	for (int i = 0; i < rhs.row_; ++i)
		for (int j = 0; j < rhs.col_; ++j) {
			cout << "Element[" << i << "][" << j << "] = ";
			is >> rhs.matrix_[i][j];
		}
	return is;
}