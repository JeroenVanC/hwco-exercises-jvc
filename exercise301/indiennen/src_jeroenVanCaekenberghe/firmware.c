#include "print.h"
// #include "counter.h"
#include "sinusCalc.h"

void main(void) {

	uint32_t sin = sinus(60);

	print_str("sinus value:");
	print_hex(sin, 8);
}
