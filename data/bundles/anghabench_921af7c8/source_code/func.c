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
 unsigned long BUDDY_SHIFT ; 
 unsigned long PAGE_MASK ; 

unsigned short handle_to_chunks(unsigned long handle)
{
	return (handle & ~PAGE_MASK) >> BUDDY_SHIFT;
}
