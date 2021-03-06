
#include "rs232IF.h"

#include <string>
#include <iostream>

using namespace std;

RS232IF::RS232IF()
{
	serial.Open(port, 9600);
}

RS232IF::~RS232IF()
{
	// fors�ger at lukke serie port.
	serial.Close();
}

bool RS232IF::validLogin()
{
	string start = "SL";
	string data = "9999";
	char slut = '\r';

	string message = start + data + slut;
	const char * c = message.c_str();
	serial.SendData( c, commandSize);
	return true;
}


	
bool RS232IF::aktiver(int a)
{
	string start = "SA";
	string data = to_string(a);
	char slut = '\r';

	string message = start + data + slut;
	const char * c = message.c_str();
	serial.SendData( c, commandSize);
	return true;
}
	
bool RS232IF::deaktiver(int b)
{
	string start = "SD";
	string data = to_string(b);
	char slut = '\r';

	string message = start + data + slut;
	const char * c = message.c_str();

	serial.SendData( c, commandSize);
	return true;
}

int RS232IF::read()
{

	char *ipBuffer = new char[commandSize+1];

	if(serial.ReadDataWaiting() >= 7)
	{
		serial.ReadData(ipBuffer, commandSize+1);
	}
	string reading(ipBuffer, commandSize);

	cout << "bufferen read message :" << reading << endl;
	delete []ipBuffer;

	if(reading[1] == 'b' || reading[1] == 'B') // Lyd detekteret
		return 3;

	if(reading[1] == 't' || reading[1] == 'T') // Login 
		return 1;

	if(reading[1] == 'f' || reading[1] == 'F') // Login udl�bet
		return 2;

	return 0;
}

bool RS232IF::tester(string a)
{
	char slut = '\r';

	string message = a + slut;
	const char * c = message.c_str();

	serial.SendData( c, commandSize);
	return true;
}