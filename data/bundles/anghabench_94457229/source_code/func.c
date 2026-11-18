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

uint32_t clk_div_even_up(uint32_t a)
{
	if (a == 1)
		return 1;
	return (a + 1) & ~1;
}
