/*
 * Assignment104_JeroenVanCaekenberghe.c
 *
 * Submit only this single C-file.
 * Rename the file so it contains your name.
 */

#include "print.h"

unsigned int get_hamming_distance(unsigned int x, unsigned int y);

void main(void) {
	volatile unsigned int value1, value2, hd;

	value1 = 5;
	value2 = 9;

	hd = get_hamming_distance(value1, value2);

	print_str("HD(0x");
	print_hex(value1, 2);
	print_str(", ");
	print_hex(value2, 2);
	print_str(") = 0x");
	print_dec(hd);
	print_str(";");
	print_str(".");
}

unsigned int get_hamming_distance(unsigned int x, unsigned int y) {
    /* Write your code here */
    int t = x ^ y;
    int setBits = 0;
 
    while (t > 0) {
        setBits += t & 1;
        t >>= 1;
    }
 
    return setBits;

}