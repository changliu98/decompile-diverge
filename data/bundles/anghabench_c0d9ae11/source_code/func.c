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
 unsigned short* crc_flex_table ; 

int check_crc_flex(unsigned char *cp, int size)
{
	unsigned short crc = 0xffff;

	if (size < 3)
		return -1;

	while (size--)
		crc = (crc << 8) ^ crc_flex_table[((crc >> 8) ^ *cp++) & 0xff];

	if ((crc & 0xffff) != 0x7070)
		return -1;

	return 0;
}
