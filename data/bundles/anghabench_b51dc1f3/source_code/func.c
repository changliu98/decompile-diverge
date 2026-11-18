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
 int* tbl_sorting_mode ; 

int get_sorting_mode (int c) {
  if (c < 0 || c >= 128) return -1;
  return tbl_sorting_mode[c];
}
