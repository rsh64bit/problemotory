#include<stdio.h>
#include<stdint.h>

#define TEST_VAL 0x0f
int main()
{

    char x, y, z;
    int pos = 0;
    int count = 0;
    /*
     * x = 0x05 = 0000 0101
     * -x = two's(x) = 1111 1010 + 1 = 1111 1011 = 0xfb = 27
     * x = 0x04 = 0000 0100
     * -x = 1111 1011 + 1 = 1111 1100 -> add 1 + 1 and pass the carry  
     * Q: How 0xfb become -5 for signed integer?
     */

    x = y = z = TEST_VAL;



    while (y) {
        if ( y & 0x1) ++count;
        y = y >> 1;
    }

    printf("method 1 count %d\n", count);

    /*find the lowest bit set*/
    /*subtract that value from the original removes that*/
    count = 0;
    while (x) {
        x -= x & -x;
        ++count;
    }
    printf("method 2 count %d\n", count);

    count = 0;


    /*Brian Kernighan’s bit-count algorithm*/
    /*clear lowest bit. update value and keep clearing*/
    while (z) {
        z &= (z - 1);
        ++count;
    }
    printf("method 3 count %d\n", count);

    //clear lowest set bit quickly

    char l = 0x0a, _l = l;

    _l &= (_l - 1);

    printf("lowest bit cleared %x %x\n", l, _l);

    char __l = l;

    printf("find the first %d nth bit set -> %x\n", (__l & -__l) - 1, l);


    printf("built int __builtin_popcount of 0x0a -> %d\n", __builtin_popcount(0x0a));
    return 1;
};
