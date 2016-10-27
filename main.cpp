#include<iostream>
using namespace std;

string tekst;
string morse;

int n;
int wie;
int ujemnik;
int num;

string kod[] ={".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--..","----",".----","..---","...--","....-",".....","-....","--...","---..","----."};
//a    b      c      d...
main()
{
tekst.clear();
morse.clear();
cout<<"Wpisz tekst:"<<endl;
getline(cin,tekst);
cout<<"Wpisany tekst: "<<tekst<<endl;
wie = tekst.size();

for(n=0;n<wie;++n)
	{
	num = (int)tekst[n];
	if(num>64 && num<91) morse+=kod[num - 65];		//wielkie litery
	else if(num>47 && num<58) morse+=kod[num-22]; 		//cyfry: - 48 + 26
	else if(num>96 && num<123) morse+=kod[num-97]; 		//maluxe litery
	else 
		{
		switch (num)
		{
			case 46: //kropka
				{
				morse+="/";
				break;
				}
			case 32: //spacja
				{
				morse+="   ";
				break;
				}
			case 44: //przecinek
				{
				morse+="/";
				break;
				}
			default: //wsxelkie inne goxwno
				{
				morse+=" ";
				break;
				}
			}
		}
        morse+=" ";
	}
cout<<morse<<endl;
}
