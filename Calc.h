#pragma once
#include "Utility.h"

#include <vector>
#include <array>
#include <conio.h>
#include <sstream>
#include <string>

class Calc
{
	friend std::istream& operator>>(std::istream& is, Calc* operation);
	friend std::ostream& operator<<(std::ostream& os, const Calc* operation);

private:
	//degree to radian 
	static constexpr long double DtoR{ 3.1415926535897932384626433832795 / 180 };

	enum class Operations : int {
		add = 1, sub, mult, div, pow, root, log, alog, ln, aln, sin, asin, cos, acos, tan, atan, cot, acot,
		sec, asec, cosec, acosec, abs, aabs
	};

	const std::array <std::string, 24> OperationNames
	{
	  "add: (v1 + v2 = ?)", "sub: (v1 - v2 = ?)", "mult: (v1 * v2 = ?)", "div ( v1 / v2 = ?)",
	  "pow: (v1 ^ v2 = ?)", "root: (v2root(v1) = ?)", "log: (log basev2 (v1) = ?)", "alog: (log basev2 (?) = v1)",
	  "ln: (log base'e' (v1) = ?)", "aln: (log base'e' (?) = v1)", "abs: (-/+ v1) = ?)", "aabs: ((+/- v1) = ?)",
	  "sin: (sin(v1) = ?)", "asin: (sin(?) = v1)", "cos: (cos(v1) = ?)", "acos: (cos(?) = v1)", "tan: (tan(v1) = ?)",
	  "atan: (tan(?) = v1)", "cot: (cot(v1) = ?)", "acot: (cot(?) = v1)", "sec: (sec(v1) = ?)", "asec: (sec(?) = v1)",
	  "cosec: (cosec(v1) = ?)", "acosec: (cosec(?) = v1)"
	};

	//only instance of the class - (calculator has only one operation) (singleton)
	static Calc* operation;

	//only member methods can access the constructor (singleton)
	Calc();

protected:

	double value1;
	double value2;
	long double result;
	Operations oper;

public:

	//copy constructor and assignment were not allowed to create another object (singleton)
	Calc(const Calc& obj) = delete;
	Calc& operator=(const Calc& obj) = delete;

	//it calls the constructor to create the object and always returns the same (singleton)
	static Calc* getOperation();

	long double operate();

	void CalcProcess();

	void DisplayOperations(const uint16_t ChosenOp = 0, bool CallFromEncoder = false) const;

	void PrintHistory() const;

	//setters
	void setValue1(double value) { value1 = value; }
	void setValue2(double value) { value2 = value; }
	void setOper(std::underlying_type_t <Calc::Operations> NewOper) { oper = Calc::Operations(NewOper); }

	//getter
	long double getResult() const { return result; }
};

