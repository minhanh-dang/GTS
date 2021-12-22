#pragma once

#include "system_equation.h"

static SystemEquations* equations_ = new SystemEquations();


// enum for user choice of Total menu
enum totalMenuOption {
	kExitTatalMenu = 0,
	kCalculateWithSingleRepeat = 1,
	kCalculateWithSeidelRepeat = 2,
	kCalculateWithGaussSeidel = 3,
	kDoMathWithMatrix = 4,
	// call max option when you want to check option
	kMaxOptionTotalMenu
};

// enum for user choice of Sub menu
enum subMenuOption {
	kExitSubMenu = 0,
	kRepeatWithTimesRepeat = 1,
	kRepeatWithErrorNumber = 2,
	// call max option when you want to check option
	kMaxOptionSubMenu
};

// enum for menu: do math with matrix
enum doMatrixOption {
	kExitMatrixMenu = 0,
	kAddMatrix = 1,
	kSubMatrix = 2,
	kMulMatrix = 3,
	kInvMatrix = 4,
	// call max option when you want to check option
	kMaxOptionMatrixMenu
};


// Total menu of program: Solve System Equations
void menuTotal();

// sub menu of program: Handle System Equations with Single repeat
// For user: Caculate if he known error number or times repeat
void menuSingleRepeat();

// sub menu of program: Handle System Equations with Seidel repeat
// For user: Caculate if he known error number or times repeat
void menuSeidelRepeat();

// sub menu of program: Do Math With Matrix. Ex: + - * !
void menuMathMatix();

// For user: Enter 0 to continue program
// Call this after hidden result, if user need any time to check result
void continueOption();