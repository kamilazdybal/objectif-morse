#include <iostream>
#include "morse.h"
#include "sendToPort.h"

using namespace std;

int main()
{

string inputString;

int i;

cout << "Select translation:" << endl << "1) Text to Morse" << endl << "2) Morse to text" << endl;
cin >> i;
cin.get();

// Trigger translation from text to Morse:
if (i == 1)
{
  morse secretMessage;

  cout << "Type text message:" << endl;
  getline(cin, inputString);
  secretMessage.inputText(inputString);
  cout << "You've typed: " << endl << secretMessage.outputText() << endl;
  cout << "Morse code: " << endl << secretMessage.outputMorse() << endl;

  // Send message to the parallel port:
  sendToPort(secretMessage.outputMorse(), 1, 25000);
}

// Trigger translation from Morse to text:
else if (i == 2)
{
  morse userInputMorse;

  cout << "Type Morse message:" << endl;
  getline(cin, inputString);
  userInputMorse.inputMorse(inputString);
  cout << "You've typed: " << endl << userInputMorse.outputMorse() << endl;
  cout << "Text message: " << endl << userInputMorse.outputText() << endl;
}

// No message translation option has been chosen:
else
{
  cout << "Unrecognized command." << endl;
  return -1;
}
}
