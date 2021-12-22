#pragma once


#include <iostream>

using namespace std;


class Matrix {
public:
	// constructor 
	Matrix();
	Matrix(int size);
	Matrix(int row, int col);
	Matrix(const Matrix& other);

	// destructor
	~Matrix();

	// this function registed data of matrix with size. Call this in constructor
	double** alloc(int row, int col);

	// this function delete memory data of matrix. Call this in destructor
	void dealloc();

	// return row number of Matrix
	int row();

	// return col number of Matrix
	int col();

	// resized the Matrix and return pointer to new array[0][0]
	double** setSize(int row, int col);

	// return pointer to begining of array9[][]
	double* getMatrix();

	// return pointer to begining of the row at array[row][0]
	double* getRow(int row);

	// return pointer to begining of the col at array[0][col]
	double* getCol(int col);

	// function set row(col) for matrix with location
	void setRow(double* row_value, int row);
	void setCol(double* col_value, int col);

	// Check this matrix. Return true if this is square matrix
	bool isSquareMatrix();

	// return unit matrix with this size if this is square matrix
	Matrix& registedUnitMatrix();

	// Return upper triangular matrix from Matrix
	Matrix& upperTriangularMatrix();

	// Return lower triangular matrix from Matrix
	Matrix& lowerTriangularMatrix();

	// oveload operator with matrix. Ex: << , >> , + , - , * , !
	friend ostream& operator << (ostream& os, const Matrix& rhs);
	friend istream& operator >> (istream& is, const Matrix& rhs);
	Matrix& operator+ (const Matrix& rhs);
	Matrix& operator- (const Matrix& rhs);
	Matrix& operator* (const Matrix& rhs);
	Matrix& operator! ();

	// Check Matrix. Return true if this is dominant diagonal matrix
	bool isDominantDiagonalMatrix();

	// find standard of matrix. Return double
	double findStandard();

	// set precision for Matrix
	void setPrecision(int precision);

	// data of matrix
	double** matrix_;

	// number precisions to hidden value of Matrix
	int precision_ = 8;

private:
	// size of Matrix
	int row_ = 0;
	int col_ = 0;
};


