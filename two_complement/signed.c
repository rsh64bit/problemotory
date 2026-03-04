#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>


unsigned char map[] = {'0', '1', '2', '3' , '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'}; 

/*num range max is 0xff = 255*/
void int2hex(int num)
{

    int i = 0;
    uint8_t hex[2] = {};
    uint8_t real_hex[8] = "\0";

    while (num != 0) {
        hex[i++] = map[num%16];
        num =  num / 16;
    }

    real_hex[0] = hex[1];
    real_hex[1] = hex[0];


    //printf("0x%s %d\n", hex, strlen(hex));
    printf("0x%s\n", real_hex);



}


int main()
{
    /*x = -128 to 127*/
    char x = 0xf9, c = 0;



    //for (uint32_t i = 0; i <= 255; ++i) printf(" %2d ", (char)i);
    /* signed from a hex 
     * 0xf9 -> 0b1111 1001 -> 2's complement to get the negative -> 0b0000 0110 +  1 -> 0b0000 0111 -> 7
     * MSB -> 1 so -7
     * */
    printf("signed maths %d\n", x);
    int2hex(114);
    return 0;
}
