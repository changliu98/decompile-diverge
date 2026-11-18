//

#define NULL ((void*)0)
  // Customize by platform.
 
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */

int get_opcode(unsigned char *addr, unsigned int *opcode)
{
	int len;

	if (*addr == 0x0F) {
		/* 0x0F is extension instruction */
		*opcode = *(unsigned short *)addr;
		len = 2;
	} else {
		*opcode = *addr;
		len = 1;
	}

	return len;
}
