#ifndef protMorse
#define protMorse

#include <iostream>
#include "morse.h"

// Function translating from text to Morse:
void morse::inputText(std::string textCode)
{

textMessage.clear();
morseMessage.clear();

textMessage = textCode;

int len = textMessage.size();
int num;

// This for loop runs over all text characters and matches them with the Morse alphabet characters from the Morse alphabet table.
for(int n = 0 ; n < len ; ++n)
{
	num = (int)textMessage[n];
	if(num > 64 && num < 91) morseMessage += code[num - 65];				// upper-case letters
	else if(num > 47 && num < 58) morseMessage += code[num - 22];		// numbers
	else if(num > 96 && num < 123) morseMessage += code[num - 97];	// lower-case letters
	else
	{
		switch (num)
		{
			case 46: // full stop
			{
				morseMessage += "/";
				break;
			}
			case 32: // space
			{
				morseMessage += " "; // adding two spaces instead of three, because one is added after each letter
				break;
			}
			case 44: // comma
			{
				morseMessage += "/";
				break;
			}
			default: // everything else is ignored
			{
        morseMessage += " ";
				break;
			}
		}
	}
morseMessage+=" ";
}
}

// Function translating from Morse to text:
void morse::inputMorse(std::string morseCode)
{

textMessage.clear();
morseMessage.clear();

morseMessage = morseCode;		// full Morse message
int len = morseCode.size(); // number of characters in the full Morse message

char tempChar;					// stores one character from the Morse message
std::string tempString; // stores a set of characters from the Morse message (typically one full word)

int n = 0;
bool addDot = false;

// This while loop runs over all Morse alphabet characters in the Morse message and checks what alphanumeric characters they are.
// Characters allowed during typing are "/", ".", "-", " ". Other characters, if typed, are replaced with "*".
// Unknown Morse alphabet characters are replaced with "_".
while (n < len)
{
	tempChar = morseCode[n];
	switch (tempChar)
	{
		case '.':
		{
			tempString += ".";
			++n;
			break;
		}
		case '-':
		{
			tempString += "-";
			++n;
			break;
		}
		case '/':
		{
			addDot = true;
			++n;
		}
		case ' ':
		{
			textMessage += translation(tempString);

			// Clear temporary string:
			tempString.clear();

			if (addDot == true)
			{
				textMessage += ". ";
				addDot = false;
			}

			// Checking the number of spaces:
			int spaceCount = 0;

			while (morseCode[n] == ' ' && n < len)
			{
				++spaceCount;
				++n;
			}

			if (spaceCount < 3) // case: 0, 1 or 2 spaces - do nothing - interpreted as space between charaters
			{
				break;
			}

			else // case: 3 or more spaces - interpreted as space between words
			{
				textMessage += " ";
				break;
			}
		}

		default:
		{
			textMessage += "*";
			break;
		}
	}
}

textMessage += translation(tempString);

}

// Function that translates dots "." and dashes "-" sequence to ASCII:
char morse::translation(std::string tempString)
{

if (!tempString.empty())
{
	for (int k = 0 ; k < 36 ; ++k)
		{
			if (tempString == code[k])
			{
				if (k > 25)	// numbers in Morse code
				{
					return (char)(k + 22);
				}
				else				// letters in Morse code
				{
					return (char)(k + 97);
				}
				break;
			}
			if (k == 35)	// character not found in Morse alphabet
			{
				return '_';
			}
		}
}
}

// Function returning the Morse message:
std::string morse::outputMorse()
{
return morseMessage;
}

// Function returning the text message:
std::string morse::outputText()
{
return textMessage;
}

// Morse alphabet table definition:
std::string morse::code[] = {".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--..","----",".----","..---","...--","....-",".....","-....","--...","---..","----."};

#endif
