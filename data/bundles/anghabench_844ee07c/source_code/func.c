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

int cvmx_helper_get_ipd_port(int interface, int port)
{
	switch (interface) {
	case 0:
		return port;
	case 1:
		return port + 16;
	case 2:
		return port + 32;
	case 3:
		return port + 36;
	case 4:
		return port + 40;
	case 5:
		return port + 44;
	}
	return -1;
}
