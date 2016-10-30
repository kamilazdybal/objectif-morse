#ifndef protHeadSend
#define protHeadSend

#include "sendToPort.h"
#include <cstdlib>
#include <unistd.h>
#include <sys/io.h>
#include <iostream>

#define base 0x378 

int sendToPort(std::string stringToSend, char bitsOn, unsigned int dotTime) 
{

if (ioperm(base, 1, 1))
{
std::cout << "Erreur" << std::endl;
return 1;
}


int stringSize = stringToSend.size();
char stringChar;

for (int i = 0 ; i < stringSize ; ++i)
{

stringChar = stringToSend[i];

	switch (stringChar)
	{
	case '.':
		{
        	outb(bitsOn, base);	
		usleep(dotTime);
		outb(0, base);
		usleep(dotTime);
		break;
		}
	case '-':
		{
        	outb(bitsOn, base);	
		usleep(3*dotTime);
		outb(0, base);
		usleep(dotTime);
		break;
		}
	case ' ':
		{
		outb(0, base);
		usleep(2*dotTime);

		if (stringToSend[i+1] == ' ') {++i;}
		if (stringToSend[i+1] == ' ') 
		{
		++i;
		usleep(4*dotTime);
		break;
		}
		}
	case '/':
		{
		usleep(6*dotTime);
		break;
		}

	} //switch
} //for

}

#endif
