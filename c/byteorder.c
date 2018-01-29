#include <stdio.h>
#include <stdlib.h>

/*
 * displays the bytes in physical memory order
 */
void print_bytes(unsigned char *bytes, size_t len) {
	size_t i;
	for (i=0; i<len; i++)
		printf("%01x ", bytes[i]);
	printf("\n");
}

/*
 * EXPLANATION:
 *
 * Demonstrates byte order on little-endian systems such as x86.
 *
 * The displayed value is always how the bytes are laid out in memory,
 * as per `print_bytes`.
 *
 * 1. 'original' simply prints out an array of 4 bytes, no surprises here.
 *
 * 2. 'converted' converts 4 bytes to a 64 bit integer value
 *    (if you read them left-to-right as they're hard-coded in 'original').
 *
 *    This will be displayed in the reverse order, because
 *    the integer value is physically represented that way on little-endian systems.
 *    
 *    original bytes:
 *    11 22 33 44
 *
 *    bit shifted bytes:
 *    11 00 00 00  (bytes[0] << 24)
 *    00 22 00 00  (bytes[1] << 16)
 *    00 00 33 00  (bytes[2] << 8)
 *    00 00 00 44  (bytes[3] << 0)
 *
 *    final value:
 *    11223344
 *
 *    displayed value:
 *    44332211
 *
 *    it's important to understand this works because
 *    bitshifting is defined by the _value_ of integers, not their physical layout.
 *
 *    on a big-endian system, the bitshifting would have no effect, because the value
 *    of the bytes would be exactly how they're already laid out in memory.
 *
 * 3. 'casted' takes the physical bytes and interprets them as an integer,
 *    it does no special conversion.
 *    
 *    the bytes will be displayed in the 'original' byte order:
 *    11223344
 *
 *    which would have the actual (hex) value of:
 *    44332211
 *
 * 4. 'constant' hard-codes the hex value 11223344,
 *
 *    the reverse bytes will be displayed:
 *    44332211
 *
 *    because that's how little-endian lays out this value in memory.
 */

int main(int argc, char *argv[]) {

	unsigned char bytes[4] =
		{ 0x11, 0x22, 0x33, 0x44 };
	
	unsigned int converted =
		  (bytes[0] << 24)
		| (bytes[1] << 16)
		| (bytes[2] << 8)
		| (bytes[3] << 0)
		;

	unsigned int casted =
		*((unsigned int *)bytes);

	unsigned int constant =
		0x11223344;

	printf("original:  ");
	print_bytes(bytes, 4);
	printf("converted: ");
	print_bytes(&converted, 4);
	printf("casted:    ");
	print_bytes(&casted, 4);
	printf("constant:  ");
	print_bytes(&constant, 4);

	return 0;
}
