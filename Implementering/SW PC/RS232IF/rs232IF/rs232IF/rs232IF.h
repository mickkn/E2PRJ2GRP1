
#pragma once

#include "Serial.h"

#define port 4
#define commandSize 7

class RS232IF
{
public:
	RS232IF();
	~RS232IF();
	bool aktiver(int);
	bool deaktiver(int);
	int read();

private:
	CSerial serial;
};