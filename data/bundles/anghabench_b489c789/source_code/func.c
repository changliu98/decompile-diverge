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

void update16(uint16_t *target, int max, int intensity, int limit)
{
    if (*target <= max)
        *target += intensity;
    else
        *target = limit;
}
