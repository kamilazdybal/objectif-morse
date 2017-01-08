#ifndef protHeadMorse
#define protHeadMorse

#include <iostream>

class morse
{
public:
	void inputMorse(std::string);	
	void inputText(std::string);
	std::string outputMorse();
	std::string outputText();

private:
	std::string morseMessage;
	std::string textMessage;
	static std::string code[];
	char translation(std::string);
};

#endif