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

bool pmic_thermal_is_aux(int address)
{
	return (address >= 4 && address <= 0x40 && !((address - 4) % 12)) ||
	       (address >= 8 && address <= 0x44 && !((address - 8) % 12));
}
