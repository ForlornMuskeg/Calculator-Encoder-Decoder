#include "Decoder.h"

int main() {

	while (true) {

		DisplayHomeScreen();

		switch (_getch()) {
		case '1':	//Calculator
		{
			Calc* operation = Calc::getOperation();
			operation->CalcProcess();
		}
		break;
		case '2':	//Encoder								
		{
			std::vector<std::unique_ptr<Encoder>> EncoderMessages;
			EncoderMessages.emplace_back(std::make_unique<Encoder>(Encoder()));
			EncoderMessages.back()->EncoderProcess(EncoderMessages);
		}
		break;
		case '3':	//Decoder
		{
			std::vector<std::unique_ptr<Decoder>> DecoderMessages;
			DecoderMessages.emplace_back(std::make_unique<Decoder>(Decoder()));
			DecoderMessages.back()->DecoderProcess(DecoderMessages);
		}
		break;
		case '4':	//Exit
			cls(GetStdHandle(STD_OUTPUT_HANDLE));
			return 0;
		default:
			break;
		}

		cls(GetStdHandle(STD_OUTPUT_HANDLE));
	}
}

