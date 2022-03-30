#include <stdint.h>

int main(void) {
	
	/*  Set up output pins
		From an old project, to cause a conflict
		*/
	AD1PCFG = 0xFFFF;
	ODCE = 0x0;
	TRISECLR = 0xFF;
	PORTE = 0x0;
	
	return 0;
}
