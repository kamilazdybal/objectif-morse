#include <iostream>
#include "morse.h"
#include "arduinoReceive.h"
#include <ctime>
#include <unistd.h>

using namespace std;

int main()
{
int timeOut;

cout << "Input time:" << endl;
cin >> timeOut;

time_t begTime;
time_t curTime;

arduino myArduino;
morse received;

myArduino.start();

time(&begTime);
time(&curTime);


while (difftime(curTime, begTime) < timeOut)
{

	myArduino.read();
	usleep(10000);
	time(&curTime);
}

received.inputMorse(myArduino.output());
cout << "Received message:" << endl;
cout << received.outputMorse() << endl;
cout << received.outputText() << endl;

myArduino.stop();

}
