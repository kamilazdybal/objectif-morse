#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/io.h>

#define base 0x378 

int main(void) 
{

if (ioperm(base, 1, 1))
        fprintf(stderr, "Couldn't open parallel port"), exit(1);

        outb(255, base);
        sleep(10);
        outb(0, base);

        return 0;

}
