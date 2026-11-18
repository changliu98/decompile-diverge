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

unsigned int mv78xx0_mbus_win_cfg_offset(int win)
{
	if (win < 8)
		return win << 4;
	else
		return 0x900 + ((win - 8) << 4);
}
