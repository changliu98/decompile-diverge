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
typedef  union mgmt_port_ring_entry {int dummy; } mgmt_port_ring_entry ;

/* Variables and functions */

unsigned int ring_size_to_bytes(unsigned int ring_size)
{
	return ring_size * sizeof(union mgmt_port_ring_entry);
}
