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
 int SUNXI_CPUS_PER_CLUSTER ; 
 scalar_t__** sunxi_mc_smp_cpu_table ; 

bool sunxi_mc_smp_cluster_is_down(unsigned int cluster)
{
	int i;

	for (i = 0; i < SUNXI_CPUS_PER_CLUSTER; i++)
		if (sunxi_mc_smp_cpu_table[cluster][i])
			return false;
	return true;
}
