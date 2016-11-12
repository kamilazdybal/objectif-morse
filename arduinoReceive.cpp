#ifndef protArduino
#define protArduino

#include "arduinoReceive.h"

// Function start(): ==================================================

void arduino::start()
{
arduinoFile = fopen("/dev/ttyACM0", "r");
if (arduinoFile == NULL) {std::cout << "Erreur opening file.";}
} // start()

// Function stop(): ==================================================

void arduino::stop()
{
fclose(arduinoFile);
} // stop()

// Function read(): ==================================================

void arduino::read()
{
char tempChar;
int tempInt;
int tempResult;

if (arduinoFile == NULL) 
{
std::cout << "Erreur reading message from Arduino.";
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

if (durations.size()%2 == 0) // case: we are at the even index
{//std::cout<<" even index ";
	switch(tempChar)
	{
		case 'H':
		{//std::cout<<"H ";
		durations.push_back(tempInt);
		break;
		}
		case 'L':
		{//std::cout<<"L ";
		durations.push_back(0);
		durations.push_back(tempInt);
		break;
		}
		default:
		{
		std::cout << "Transmission erreur.";
		break;
		}
	} // switch
} // if

else // case: we are at the odd index
{//std::cout<<" odd index ";
	switch(tempChar)
	{
		case 'L':
		{//std::cout<<"L ";
		durations.push_back(tempInt);
		break;
		}
		case 'H':
		{//std::cout<<"H ";
		durations.push_back(0);
		durations.push_back(tempInt);
		break;
		}
		default:
		{
		std::cout << "Transmission erreur.";
		break;
		}
	} // switch
} // else

} // read()

// Function clear(): ==================================================

void arduino::clear()
{
std::cout << "clear:todo" << std::endl;
} // clear()

// Function output(): ==================================================

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
std::string messageReceived;

// adding High signal times to compute the average time of High signals:

for (i = 0 ; i < durSize ; i += 2)
{
	if (durations[i] != 0) // including only non-zero vector element
	{
	++numNonZero; 
	averageHigh += durations[i];
	}
}


averageHigh /= numNonZero;

// calculates the average time of dots only and dashes only
// calculates the total number of dots and dashes in the message

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

averageDot /= numDot; // should be approximately equal to 1 dotTime
averageDash /= numDash; // should be approximately equal to 3 dotTime

if (numDot > numDash) // there's more dots in our signal, we trust the 1 dotTime more
{
bound13 = 2*averageDot;
bound37 = 6*averageDot;
std::cout << std::endl << "Dot:" << averageDot << std::endl;
}
else // there's more dashes in our signal, we trust the 3 dotTime more
{
bound13 = 2*averageDash/3;
bound37 = 2*averageDash;
std::cout << std::endl << "Dash:" << averageDash << std::endl;
}

// assembling the string:

for (i = 0 ; i < durSize ; ++i)
{std::cout<<durations[i]<<std::endl; // DEBUG ------------------------------
	if (i%2 == 0) // High signal
	{
		if (durations[i] < averageHigh) messageReceived += ".";
		else messageReceived += "-";
	}
	else // Low signal
	{
		if (durations[i] > bound13) 
		{
		messageReceived += " ";
		if (durations[i] > bound37) messageReceived += "  ";
		}		
	}

}

return messageReceived;

} // output()

#endif
