#include "Encoder.h"

Encoder::Encoder() : message(), key(), Emessage() {

}


std::istream& operator>>(std::istream& is, Encoder& encoder) {
	std::string Message;

	std::cout << "Enter your message:";
	std::getline(is, Message);
	encoder.setMessage(Message);

	return is;
}

std::ostream& operator<<(std::ostream& os, const Encoder& encoder) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);

	os << "Message: " << encoder.message << "\nKey: ";

	for (auto keyElements : encoder.key)
		os << keyElements << "-";

	os << "\nEncoded Message: " << std::showpos << std::setprecision(15);

	for (auto EmessageElements : encoder.Emessage)
		os << EmessageElements;

	os << std::noshowpos;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

	return os;
}


void Encoder::setEmessage(uint16_t& ReferenceList) {

	std::for_each(message.begin(), message.end(), [&](char letter) {	// Converting message(char) to Emessage (int)
		if (ReferenceList == 1) {										// ASCII
			Emessage.emplace_back(static_cast<int>(letter));
		}
		else {															// Phone array
			for (uint16_t i = 0; i < std::size(phone); i++)
				for (uint16_t j = 0; j < 8; j++)
					if (letter == phone[i][j])
						Emessage.emplace_back((i + 2) * 10 + (j + 1));
		}

		});

}

void Encoder::ConvertMessage() {
	std::string TestReferenceList;
	uint16_t ReferenceList{ 0 };

	std::cout << "Choose the reference list for numbers:\n" << "1.ASCII\n"
		<< "2.PhoneButtons (for messages containing only letters)\n";

	do {
		std::getline(std::cin, TestReferenceList);

	} while (!(std::stringstream{ TestReferenceList } >> ReferenceList) && (ReferenceList != 1 && ReferenceList != 2));

	key.emplace_back(ReferenceList);							//Set referencelist number to first digit of the key  
	this->setEmessage(ReferenceList);

}

void Encoder::Key() {
	std::string TestInput;
	int UserInput{ 1 };
	double SpecialNumber{ 0.0 };
	std::vector<long double> tempResults;

	std::cout << "Enter your special number:";							// Request their special number from the users 
	do {																// to use it as value2 of the calculator
		std::getline(std::cin, TestInput);
	} while (!(std::istringstream{ TestInput } >> SpecialNumber));
	Calc::getOperation()->setValue2(SpecialNumber);

	std::cout << "Enter operation numbers by seperating with spaces to make your key: ";     // Creating key
	do {
		std::cin >> TestInput;
		if ((std::istringstream{ TestInput } >> UserInput))
			key.emplace_back(UserInput);

	} while (std::cin.get() != '\n');

	key.emplace_back(SpecialNumber);	// Set special number to last digit of the key 

	cls(GetStdHandle(STD_OUTPUT_HANDLE));

	for (auto it_Key = key.begin() + 1; it_Key < key.end() - 1; it_Key++) {		// Check all elements of the key and
		// apply them to each character of the converted message
		Calc::getOperation()->setOper(*it_Key);
		tempResults.clear();

		for (long double& letter : Emessage) {

			Calc::getOperation()->setValue1(letter);

			if (CheckSelectedOperations(Calc::getOperation()->operate()) && *it_Key < 11 && *it_Key > 0) {

				tempResults.emplace_back(Calc::getOperation()->getResult());
			}
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);

				std::cout << "Invalid Result(must be a number): " << Calc::getOperation()->getResult()
					<< " or Invalid Operation Number(must be 1-10): " << *it_Key
					<< "\nFor Letter " << letter << "\nChosen Operation Number Will Be Removed From The Key...\n\n";
				it_Key = key.erase(it_Key);
				it_Key--;
				tempResults.clear();
				break;
			}
		}

		if (!tempResults.empty())
			Emessage.swap(tempResults);
	}
}

bool Encoder::CheckSelectedOperations(long double&& result) {

	return (result == result && result < LDBL_MAX && result > -LDBL_MAX);	//If the result is a number, return true

}

int Encoder::EncoderProcess(std::vector<std::unique_ptr<Encoder>>& EncoderMessages) {

	do {

		cls(GetStdHandle(STD_OUTPUT_HANDLE));							//clear the screen
		std::cout << "Current Message\n" << *this << "\n\n";			//Display current object
		Calc::getOperation()->DisplayOperations(0, true);				//Display operations 
		if (this->message.empty())										//If the current object does not have a message
			std::cin >> *this;											//Request a message from the users
		this->ConvertMessage();											//Request a reference number and convert message(char) to Emessage (int)
		this->Key();													//Apply the key
		std::cout << *this;												//Display current object(final Encoded Message)

		std::cout << "\n\n1.New Message\n2.Rebuild Your Current Key\n3.Access Your Messages\n\nESC.Return To Menu (All Messages Will Be Deleted)\n";

		switch (_getch()) {
		case '1':
		default:
			break;

		case '2':
			key.clear();
			Emessage.clear();
			EncoderProcess(EncoderMessages);
			return 0;
		case '3':
		{
			int i{ 1 };

			cls(GetStdHandle(STD_OUTPUT_HANDLE));
			for (auto& messages : EncoderMessages) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				std::cout << i++ << " - " << *messages << "\n\n";
			}

			std::cout << "Select to edit the key of a message (If you do not want to change, enter anything to continue): ";
			std::cin >> i;
			if (i <= std::size(EncoderMessages) && i > 0) {
				EncoderMessages.at(i - 1)->key.clear();
				EncoderMessages.at(i - 1)->Emessage.clear();
				EncoderMessages.at(i - 1)->EncoderProcess(EncoderMessages);
				return 0;
			}
		}
		std::cin.ignore();
		std::cin.clear();
		break;

		case VK_ESCAPE:
			return 0;

		}

		EncoderMessages.emplace_back(std::make_unique<Encoder>(Encoder()));
		EncoderMessages.back()->EncoderProcess(EncoderMessages);
		break;

	} while (true);

}
