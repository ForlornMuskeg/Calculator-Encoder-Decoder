#pragma once
#include "Calc.h"

#include <memory>
#include <algorithm>

class Encoder {

	friend std::istream& operator>>(std::istream& is, Encoder& encoder);
	friend std::ostream& operator<<(std::ostream& os, const Encoder& encoder);
	friend class Calc;


protected:

	const std::array<std::array<char, 8>, 8> phone{
		{
			{'A', 'B', 'C', 'a', 'b', 'c'},
			{'D', 'E', 'F', 'd', 'e', 'f'},
			{'G', 'H', 'I', 'g', 'h', 'i'},
			{'J', 'K', 'L', 'j', 'k', 'l'},
			{'M', 'N', 'O', 'm', 'n', 'o'},
			{'P', 'Q', 'R', 'S', 'p', 'q', 'r', 's'},
			{'T', 'U', 'V', 't', 'u', 'v'},
			{'W', 'X', 'Y', 'Z', 'w', 'x', 'y', 'z'}
		}
	};

	std::string message;
	std::vector <int> key;
	std::vector <long double> Emessage;

public:

	Encoder();

	virtual void ConvertMessage();
	virtual void Key();
	int EncoderProcess(std::vector<std::unique_ptr<Encoder>>&);
	bool CheckSelectedOperations(long double&&);

	void setMessage(std::string NewMessage) { message = NewMessage; }
	void setEmessage(uint16_t& ReferenceList);


};

