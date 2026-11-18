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

uint32_t F(uint32_t x, uint32_t y, uint32_t z)
{
	return (x & y) | ((~x) & z);
}
