#pragma once

#include "Matrix.h"

class SystemEquations {
public:
	// constructor
	SystemEquations();
	SystemEquations(int hidden_number);

	// destructor
	~SystemEquations();

	// input value for System Equations: dependent , freedom
	void inputData();

	// input value for System Equation: hidden number, precision,
	// dependent , freedom
	void input();

	// output System Equation to Console
	void output();

	// handle: Ax=B ---> x=Ax+B 
	void handleEquations();

	// check Matrix dependent is dominant diagonal matrix
	// should call this when isHandle = true
	bool checkDependentMatrix();

	// handle System Equations with Single Repeat
	void handleSingleRepeat(int times_repeat);
	void handleSingleRepeat(double error_number);

	// handle System Equations with Seidel Repeat
	void handleSeidelRepeat(int times_repeat);
	void handleSeidelRepeat(double error_number);

	// handle System Equations with Gauss Seidel
	void handleGaussSeidel();


	// check this System Equation is Handled. If true, Equations matrix is Ax = B,
	// if false, Equations matrix is x = Ax+B
	bool isHandle = false;

	// number precisions to hidden value of System Equations
	int precision_ = 8;

	// hidden number of System Equation
	int hidden_number_ = 0;

private:
	// Static variable .Matrix of Equations : Ax = B if |isHandle| is false,
	// or x =AX+B if |isHandle| is true.
	// Matrix A: dependent_
	// Matrix B: freedom_
	Matrix& dependent_;
	Matrix& freedom_;


};

