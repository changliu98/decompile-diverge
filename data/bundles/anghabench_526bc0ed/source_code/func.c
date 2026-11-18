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

uint16_t roccat_common2_feature_report(uint8_t report_id)
{
	return 0x300 | report_id;
}
