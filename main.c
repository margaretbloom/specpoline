#include <stdio.h>
#include <limits.h>

#if CHAR_BIT != 8
    #error CHAR_BIT MUST BE 8
#endif


extern unsigned int timings[256];
extern void leak();

int main()
{
    int i;

    /* Test specpoline */
    leak();

    /* Show results */
    for (i = 0; i < 256; i++)
    {
        if (i % 16 == 0)
            printf("\n");

        printf("   %4d", timings[i]);
    }
    printf("\n\n");

    return 0;    
}
