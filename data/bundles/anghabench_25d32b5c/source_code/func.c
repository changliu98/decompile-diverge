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
 unsigned int DM_VERITY_FEC_BUF_RS_BITS ; 

unsigned fec_buffer_rs_index(unsigned i, unsigned j)
{
	return (i << DM_VERITY_FEC_BUF_RS_BITS) + j;
}
