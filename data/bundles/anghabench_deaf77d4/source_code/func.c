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
 scalar_t__ COUNTER_OVERFLOW ; 

uint32_t pmc_sample_period(uint32_t value)
{
	return COUNTER_OVERFLOW - value;
}
