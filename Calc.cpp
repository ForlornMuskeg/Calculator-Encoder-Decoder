#include "Calc.h"

#include <cmath>
#include <map>


Calc* Calc::operation = nullptr;

Calc* Calc::getOperation() {
	if (operation == nullptr) {
		operation = new Calc();
		return operation;
	}
	return operation;
}

Calc::Calc() : value1(0.0), value2(0.0), result(0.0), oper(Calc::Operations::add) {
}

std::istream& operator>>(std::istream& is, Calc* operation) {

	double value{ 0.0 };
	std::underlying_type_t <Calc::Operations> UserInput{ 0 };
	std::string TestInput;

	do {
		std::cout << "Operation Number: ";

		std::getline(is, TestInput);
		std::stringstream(TestInput) >> UserInput;

	} while (UserInput < 1 || UserInput > 24);

	operation->oper = Calc::Operations(UserInput);

	cls(GetStdHandle(STD_OUTPUT_HANDLE));
	operation->DisplayOperations(UserInput);

	do {

		std::cout << "Value1: ";
		std::getline(is, TestInput);

		cls(GetStdHandle(STD_OUTPUT_HANDLE));
		operation->DisplayOperations(UserInput);

	} while (!(std::stringstream{ TestInput } >> value));

	if (UserInput >= 11 && UserInput % 2 == 1 && UserInput <= 21)
		value = RegulateDegree(value);

	operation->setValue1(value);


	if (UserInput <= 8) {

		do {

			std::cout << std::setprecision(15) << "Value1: " << operation->value1;

			std::cout << "\nValue2: ";
			std::getline(is, TestInput);


			cls(GetStdHandle(STD_OUTPUT_HANDLE));
			operation->DisplayOperations(UserInput);

		} while (!(std::stringstream{ TestInput } >> value));

		operation->setValue2(value);
	}

	return is;
}

std::ostream& operator<<(std::ostream& os, const Calc* operation) {
	cls(GetStdHandle(STD_OUTPUT_HANDLE));
	operation->DisplayOperations(static_cast<int>(operation->oper));

	os << "Value1: " << operation->value1;

	if (static_cast<int>(operation->oper) <= 8)
		os << "\nValue2: " << operation->value2;

	os << "\nResult: " << operation->result;

	return os;
}

long double Calc::operate() {

	switch (oper) {

	case Operations::add:
		return result = value1 + value2;

	case Operations::sub:
		return result = value1 - value2;

	case Operations::mult:
		return result = value1 * value2;

	case Operations::div:
		return result = value1 / value2;

	case Operations::pow:
		return result = pow(value1, value2);

	case Operations::root:
		return result = pow(value1, (1 / value2));

	case Operations::log:
		return result = log(value1) / log(value2);

	case Operations::alog:
		return result = pow(value2, value1);

	case Operations::ln:
		return result = log(value1);

	case Operations::aln:
		return result = pow(2.71828, value1);

	case Operations::abs:
		return result = abs(value1);

	case Operations::aabs:
		if (value1 > 0)
			return result = -value1;

		return result = value1;

	case Operations::sin:
		if (value1 == 180 || value1 == -180)								     //To accurate the calculation for some degrees
			return result = 0;

		return result = sin(value1 * DtoR);

	case Operations::asin:
		return result = asin(value1) / DtoR;

	case Operations::cos:
		if (value1 == 90 || value1 == 270 || value1 == -90 || value1 == -270)     //To accurate the calculation for some degrees
			return result = 0;

		return result = cos(value1 * DtoR);

	case Operations::acos:
		return result = acos(value1) / DtoR;

	case Operations::tan:
		if (value1 == 90 || value1 == 270 || value1 == -90 || value1 == -270)    //To accurate the calculation for some degrees
			return result = std::numeric_limits<long double>::quiet_NaN();

		else if (value1 == 180 || value1 == -180)
			return result = 0;

		return result = tan(value1 * DtoR);

	case Operations::atan:
		return result = atan(value1) / DtoR;

	case Operations::cot:
		if (value1 == 90 || value1 == 270 || value1 == -90 || value1 == -270)  //To accurate the calculation for some degrees
			return result = 0;

		else if (value1 == 180 || value1 == -180)							   //To accurate the calculation for some degrees
			return result = std::numeric_limits<long double>::quiet_NaN();

		return result = (cos(value1 * DtoR) / sin(value1 * DtoR));

	case Operations::acot:
		return result = atan(1 / value1) / DtoR;

	case Operations::sec:
		if (value1 == 90 || value1 == 270 || value1 == -90 || value1 == -270)  //To accurate the calculation for some degrees
			return result = std::numeric_limits<long double>::quiet_NaN();

		return result = 1 / cos(value1 * DtoR);

	case Operations::asec:
		return result = acos(1 / value1) / DtoR;

	case Operations::cosec:
		if (value1 == 180 || value1 == -180)								   //To accurate the calculation for some degrees
			return result = std::numeric_limits<long double>::quiet_NaN();

		return result = 1 / sin(value1 * DtoR);

	case Operations::acosec:
		return result = asin(1 / value1) / DtoR;

	}
}

void Calc::CalcProcess() {

	do {
		cls(GetStdHandle(STD_OUTPUT_HANDLE));						// clear the screen
		DisplayOperations();										// Display operations
		std::cin >> operation;										// Get values and operation number from users
		operation->operate();										// Call operate() with given values 
		std::cout << operation;										// Display value1, value2 and result
		PrintHistory();												// Display previous operations
	} while ((_getch() && !(GetKeyState(VK_ESCAPE) & 0x8000)));		// İf ESC is not pressed, continue


}


void Calc::DisplayOperations(const uint16_t ChosenOp, bool CallFromEncoder) const {

	std::cout << "OPERATIONS:";

	size_t OperationNamesSize = std::size(OperationNames);

	if (CallFromEncoder)										// If the function is used in EncoderProcess(),
		OperationNamesSize -= 12;								// decrease the size to not displaying trigonometric operations

	for (uint16_t i = 1; i <= OperationNamesSize; i++) {

		if ((i % 3) == 1)
			std::cout << "\n\n";

		if (i == ChosenOp)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	// Text Color Set

		std::cout << std::left << std::setw(3) << i << std::setw(2) << "- " << std::setw(30)   // Display the operation names
			<< OperationNames[i - 1] << std::setw(5) << " ";

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);    // Text Color Reset

	}

	std::cout << "\n\n";

}


void Calc::PrintHistory() const {
	static int i = 0;
	std::vector<long double> Values;													// Hold value1, value2 and result
	std::multimap<Operations, std::vector<long double>> OldOperations;					// Hold values and the operation number
	static std::map<int, std::multimap<Operations, std::vector<long double>>> History;  // Hold operations in order

	Values.emplace_back(value1);

	if (static_cast<int>(oper) <= 8)							// If the operation needs value2
		Values.emplace_back(value2);

	Values.emplace_back(result);

	OldOperations.insert(std::make_pair(oper, Values));
	History.insert(std::make_pair(++i, OldOperations));

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 50,20 });

	std::cout << "HISTORY\n";

	for (auto& HistoryPairs : History) {                                  // Run through History map
		for (auto& OldOperationPairs : HistoryPairs.second) {			  // Run through Old Operations multimap  

			std::cout << std::setw(50) << "";

			std::string OpName = OperationNames[static_cast<int>(OldOperationPairs.first) - 1];
			auto it = OpName.begin();

			while (it != OpName.end()) {

				auto v = std::find(OpName.begin(), OpName.end(), 'v');					// Find the adress of a 'v'	
				auto re = std::find(OpName.begin(), OpName.end(), '?');					// Find the adress of a '?'

				if (it == v) {															// Replace 'v' with values 
					if (*(it + 1) == '1')
						std::cout << OldOperationPairs.second.at(0);
					else if (*(it + 1) == '2')
						std::cout << OldOperationPairs.second.at(1);

					OpName.erase(it);
					it += 1;
				}
				else if (it == re) {													// Replace '?' with result
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);		// Text Color Set

					if (static_cast<int>(OldOperationPairs.first) > 8)					// If the Operations Number > 8, which means that value2 does not exist,
						std::cout << OldOperationPairs.second.at(1);					// display the second element as the result.
					else
						std::cout << OldOperationPairs.second.at(2);

					it += 1;

					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);		// Text Color Reset
				}
				else {
					std::cout << *it;
					it++;
				}

			}
			std::cout << "\n";

		}

	}

}
