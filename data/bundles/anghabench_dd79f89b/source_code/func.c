//

#define NULL ((void*)0)
  // Customize by platform.
 
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int gain; int gain_pulse; } ;

/* Variables and functions */
 int HX711_GAIN_MAX ; 
 TYPE_1__* hx711_gain_to_scale ; 

int hx711_get_gain_to_pulse(int gain)
{
	int i;

	for (i = 0; i < HX711_GAIN_MAX; i++)
		if (hx711_gain_to_scale[i].gain == gain)
			return hx711_gain_to_scale[i].gain_pulse;
	return 1;
}
