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
struct xfs_phys_extent {int dummy; } ;
struct xfs_cui_log_format {int dummy; } ;

/* Variables and functions */

size_t
xfs_cui_log_format_sizeof(
	unsigned int		nr)
{
	return sizeof(struct xfs_cui_log_format) +
			nr * sizeof(struct xfs_phys_extent);
}
