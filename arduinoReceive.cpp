#ifndef protArduino
#define protArduino

#include "arduinoReceive.h"

// Function opening the Arduino output file:
void arduino::start()
{
arduinoFile = fopen("/dev/ttyACM0", "r");
if (arduinoFile == NULL) {std::cout << "Error opening Arduino output file.";}
}

// Function closing the Arduino output file:
void arduino::stop()
{
fclose(arduinoFile);
}

// Function reading the Arduino output:
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

// Uncomment this line for debugging:
// std::cout << tempChar << " " << tempInt << " " << tempResult << std::endl;

tempResult = 0;

// Appending signal to the vector durations:
if (durations.size()%2 == 0)
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

else
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

// Function translating the Arduino output to a string written in the Morse code:
std::string arduino::output()
{

int i;
int durSize = durations.size();
long int averageHigh = 0;
long int averageDot = 0;
long int averageDash = 0;
int numDot = 0;
int numDash = 0;
int numNonZero = 0;
int bound13;
int bound37;
int element;
std::string messageReceived;

for (i = 0 ; i < durSize ; i += 2)
{
	if (durations[i] != 0)
	{
		++numNonZero;
		averageHigh += durations[i];
	}
}

if (numNonZero == 0) {return "";}

averageHigh /= numNonZero;

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

if (numDot > numDash)
{
	averageDot /= numDot;
	bound13 = 2*averageDot;
	bound37 = 6*averageDot;
	// Uncomment this line for debugging:
	// std::cout << std::endl << "Dot:" << averageDot << std::endl;
}

else
{
	if (numDash == 0 ) {return "";}
	averageDash /= numDash;
	bound13 = 2*averageDash/3;
	bound37 = 2*averageDash;
	// Uncomment this line for debugging:
	// std::cout << std::endl << "Dash:" << averageDash << std::endl;
}

for (i = 0 ; i < durSize ; ++i)
{
	element = durations[i];
	// Uncomment this line for debugging:
	// std::cout << element << std::endl;
	if(element == 0){continue;}
	if (i%2 == 0)
	{
		if (element < averageHigh) messageReceived += ".";
		else messageReceived += "-";
	}
	else
	{
		if (element > bound13)
		{
			messageReceived += " ";
			if (element > bound37) messageReceived += "  ";
		}
	}

}

return messageReceived;

}

#endif
