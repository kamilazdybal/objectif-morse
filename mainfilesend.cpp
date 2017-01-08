#include <iostream>
#include "morse.h"
#include "sendToPort.h"

using namespace std;

int main()
{

string inputString;
FILE* inputFile;
char temp;

int i;

cout << "Select translation:" << endl << "1) Text to Morse" << endl << "2) Morse to text" << endl << "3) Send pliczek.ppm file" << endl;
cin >> i;
cin.get();

if (i == 1)
{
// TESTING TEXT >> MORSE:

morse secretMessage;

cout << "Type text message:" << endl;

getline(cin, inputString);

secretMessage.inputText(inputString);

cout << "You've typed: " << endl << secretMessage.outputText() << endl;
cout << "Morse code: " << endl << secretMessage.outputMorse() << endl;

// Sending the message to the parallel port
sendToPort(secretMessage.outputMorse(), 1, 2500);

}

else if (i == 2)
{
// TESTING MORSE >> TEXT:

morse userInputMorse;

cout << "Type Morse message:" << endl;

getline(cin, inputString);

userInputMorse.inputMorse(inputString);

cout << "You've typed: " << endl << userInputMorse.outputMorse() << endl;
cout << "Text message: " << endl << userInputMorse.outputText() << endl;
}

else if (i == 3)
{
    morse secretMessage;
inputFile = fopen("pliczek.ppm","r");  
if(inputFile == NULL)
    {
        cout << "Error opening file" << endl;
        return -1;
    }
while((temp = fgetc(inputFile)) != EOF)
    {
        if(temp == '\n'){inputString += 'n';}
        else {inputString += temp;}
    }
secretMessage.inputText(inputString);
sendToPort(secretMessage.outputMorse(), 1, 2500);   

    
}

else
{
cout << "Unrecognized command." << endl;
return -1;
}
// OTHER TESTS:

//morse uncodedMessage;
//uncodedMessage.inputMorse(secretMessage.outputMorse());

//cout << "Message uncoded back: " << endl << uncodedMessage.outputText() << endl;
//cout << "Just in case, message in Morse code: " << endl << uncodedMessage.outputMorse() << endl;

}
