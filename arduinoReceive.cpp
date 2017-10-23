#ifndef protArduino
#define protArduino

#include "arduinoReceive.h"

// Function
void arduino::start()
{
arduinoFile = fopen("/dev/ttyACM0", "r");
if (arduinoFile == NULL) {std::cout << "Error opening file.";}
}

// Function
void arduino::stop()
{
fclose(arduinoFile);
}

// Function
void arduino::read()
{
char tempChar;
int tempInt;
int tempResult;

if (arduinoFile == NULL)
{
	std::cout << "Error reading message from Arduino.";
	return;
}

tempResult = fscanf(arduinoFile, "%c %d", &tempChar, &tempInt);

if (tempResult < 2 || tempInt<0)
{
	return;
}

std::cout << tempChar << " " << tempInt << " " << tempResult << std::endl; //DEBUG !!! 1 1!!1!!
tempResult = 0;

// Appending signal to a vector:
if (durations.size()%2 == 0) // we are at the even index
{
	switch(tempChar)
	{
		case 'H':
		{
			durations.push_back(tempInt);
			break;
		}
		case 'L':
		{
			durations.push_back(0);
			durations.push_back(tempInt);
			break;
		}
		default:
		{
			std::cout << "Transmission error.";
			break;
		}
	}
}

else // we are at the odd index
{
	switch(tempChar)
	{
		case 'L':
		{
			durations.push_back(tempInt);
			break;
		}
		case 'H':
		{
			durations.push_back(0);
			durations.push_back(tempInt);
			break;
		}
		default:
		{
			std::cout << "Transmission error.";
			break;
		}
	}
}

}

// Function
void arduino::clear()
{
std::cout << "clear:todo" << std::endl;
}

// Function returning the string received in the Morse code:
std::string arduino::output()
{

int i;
int durSize = durations.size();
long int averageHigh = 0; // average time when the signal is High
long int averageDot = 0; // average time of the dot signal
long int averageDash = 0; // average time of the dash signal
int numDot = 0; // total number of dots in the message
int numDash = 0; // total number of dashes in the message
int numNonZero = 0; // total number of non-zero elements in the vector `durations`
int bound13; // boundary time between 1 dotTime and 3 dotTime
int bound37; // boundary time between 3 dotTime and 7 dotTime
int tempA; // auxiliary variable
std::string messageReceived; // string of "." and "-" received

/* Adding High signal times to compute the average time of High signals:
this for loop goes every 2 vector element, because we assume that the
High signal always follows Low signal, etc.
Also, we always start vector `durations` with a High signal.
*/

for (i = 0 ; i < durSize ; i += 2)
{
	if (durations[i] != 0) // including only non-zero vector element
	{
		++numNonZero;
		averageHigh += durations[i];
	}
}

if (numNonZero == 0) {return "";}
averageHigh /= numNonZero;

// This for loop calculates the average time of a dot and a dash in the message.
// It also calculates the total number of dots and dashes in the message.
for (i = 0 ; i < durSize ; i += 2)
{
     	if(durations[i] != 0)
	{
		if (durations[i] < averageHigh)
		{
			++ numDot;
			averageDot += durations[i];
		}
		else
		{
			++ numDash;
			averageDash += durations[i];
		}
	}
}

if (numDot > numDash) // there's more dots in our signal, we trust the 1 dotTime more
{
	averageDot /= numDot; // should be approximately equal to 1 dotTime
	bound13 = 2*averageDot;
	bound37 = 6*averageDot;
	std::cout << std::endl << "Dot:" << averageDot << std::endl;
}

else // there's more dashes in our signal, we trust the 3 dotTime more
{
	if (numDash == 0 ) {return "";}
	averageDash /= numDash; // should be approximately equal to 3 dotTime
	bound13 = 2*averageDash/3;
	bound37 = 2*averageDash;
	std::cout << std::endl << "Dash:" << averageDash << std::endl;
}

// This for loop is assembling the string:
for (i = 0 ; i < durSize ; ++i)
{
	tempA = durations[i];
	std::cout<<tempA<<std::endl; // DEBUG ------------------------------
	if(tempA == 0){continue;}
	if (i%2 == 0) // High signal
	{
		if (tempA < averageHigh) messageReceived += ".";
		else messageReceived += "-";
	}
	else // Low signal
	{
		if (tempA > bound13)
		{
			messageReceived += " ";
			if (tempA > bound37) messageReceived += "  ";
		}
	}

}
return messageReceived;
}

#endif
