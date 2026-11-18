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

void RewindBitPosition(const size_t new_storage_ix,
                              size_t* storage_ix, uint8_t* storage) {
  const size_t bitpos = new_storage_ix & 7;
  const size_t mask = (1u << bitpos) - 1;
  storage[new_storage_ix >> 3] &= (uint8_t)mask;
  *storage_ix = new_storage_ix;
}
