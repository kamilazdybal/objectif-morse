#include<cstdio>

//using namespace std;

int main()
{
FILE* parport;
parport = NULL;
unsigned char tobesent = 0;
parport = fopen("/dev/lp0","r+");
if(parport != NULL)
 {
 printf("Port opened succesfully, input characters to be sent, 255 to exit!");

 while(tobesent != 255)
  {
  scanf("%d",&tobesent);
  getchar();
  fputc(tobesent,parport);
  }
 fclose(parport);
 }
return 0;
}
