#pragma once
#include "Encoder.h"

class Decoder : public Encoder
{
	friend std::istream& operator>>(std::istream& is, Decoder& decoder);
	friend std::ostream& operator<<(std::ostream& os, const Decoder& decoder);

public:
	Decoder();

	virtual void ConvertMessage(long double&);
	virtual void Key() override;
	int DecoderProcess(std::vector<std::unique_ptr<Decoder>>&);
};

