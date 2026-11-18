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

int byte_row_gbk1 (int byte) {
  if (byte >= 0x81 && byte < 0xff)
    return byte-0x81;
  else
    return -1;
}
