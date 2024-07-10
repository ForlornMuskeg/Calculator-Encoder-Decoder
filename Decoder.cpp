#include "Decoder.h"

Decoder::Decoder() : Encoder() {

}


std::istream& operator>>(std::istream& is, Decoder& decoder) {
	std::string TestInput;
	long double UserInput{ 0.0 };

	if (decoder.Emessage.empty()) {
		std::cout << "\n\nEnter Encoded Message (by seperating with spaces): ";
		do {
			std::cin >> TestInput;
			if ((std::istringstream{ TestInput } >> UserInput))
				decoder.Emessage.emplace_back(UserInput);
		} while (std::cin.get() != '\n' || !(std::istringstream{ TestInput } >> UserInput));
	}

	std::cout << "\n\nEnter Your Key (by seperating with spaces): ";
	do {
		std::cin >> TestInput;
		if ((std::istringstream{ TestInput } >> UserInput))
			decoder.key.emplace_back(UserInput);
	} while (std::cin.get() != '\n' || std::size(decoder.key) < 2);

	return is;
}

std::ostream& operator<<(std::ostream& os, const Decoder& decoder) {

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);

	os << "Encoded Message:" << std::setprecision(15);

	for (auto& c : decoder.Emessage)
		os << c;

	os << "\nKey: ";

	for (auto& c : decoder.key)
		os << c;

	os << "\nMessage: " << decoder.message;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

	return os;
}


void Decoder::ConvertMessage(long double& letter) {

	if (key.front() == 1) {
		message += static_cast<char>(letter);
	}
	else {
		for (uint16_t i = 0; i < std::size(phone); i++)
			for (uint16_t j = 0; j < 8; j++)
				if (letter == (i + 2) * 10 + (j + 1))
					message += phone[i][j];
	}


}

void Decoder::Key() {

	Calc::getOperation()->setValue2(key.back());

	for (long double letter : Emessage) {

		std::for_each(key.rbegin() + 1, key.rend() - 1, [&letter, this](int keys) {		//Apply the key in reverse order

			if (keys % 2 == 0)	//Change each key element to opposite version 
				--keys;
			else
				++keys;

			Calc::getOperation()->setOper(keys);

			Calc::getOperation()->setValue1(letter);
			letter = Calc::getOperation()->operate();

			});

		this->ConvertMessage(letter);
	}

}


int Decoder::DecoderProcess(std::vector<std::unique_ptr<Decoder>>& DecoderMessages) {

	do {
		cls(GetStdHandle(STD_OUTPUT_HANDLE));		//clear the screen
		std::cout << *this;							//Display current object
		std::cin >> *this;							//Request an encoded message and a key 
		this->Key();								//Apply the key in reverse order
		cls(GetStdHandle(STD_OUTPUT_HANDLE));		//clear the screen
		std::cout << *this;							//Display current object (decoded message)

		std::cout << "\n\n1.New Message\n2.Rebuild Your Current Key\n3.Access Your Messages\n\nESC.Return To Menu (All Messages Will Be Deleted)\n";

		switch (_getch()) {
		case '1':
		default:
			break;

		case '2':
			key.clear();
			message.clear();
			DecoderProcess(DecoderMessages);
			return 0;
		case '3':
		{
			int i{ 1 };

			cls(GetStdHandle(STD_OUTPUT_HANDLE));
			for (auto& messages : DecoderMessages) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				std::cout << i++ << " - " << *messages << "\n\n";
			}

			std::cout << "Select to edit the key of a message (If you do not want to change, enter anything): ";
			std::cin >> i;
			if (i < DecoderMessages.size() && i > 0) {
				DecoderMessages.at(i - 1)->key.clear();
				DecoderMessages.at(i - 1)->message.clear();
				DecoderMessages.at(i - 1)->DecoderProcess(DecoderMessages);
				return 0;
			}
		}
		break;

		case VK_ESCAPE:
			return 0;

		}

		DecoderMessages.emplace_back(std::make_unique<Decoder>(Decoder()));
		DecoderMessages.back()->DecoderProcess(DecoderMessages);
		break;

	} while (true);
}
