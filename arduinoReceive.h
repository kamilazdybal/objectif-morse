#ifndef protHeadArduino
#define protHeadArduino

#include <cstdio>
#include <vector>
#include <iostream>

class arduino
{
private:
	FILE* arduinoFile;
	std::vector<int> durations;

public:
	void start();
	void stop();
	void read();
	void clear();
	std::string output();
};

#endif
