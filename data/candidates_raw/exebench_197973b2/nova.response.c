static void func0(const u32 *rates, u32 bitrate,
			    u32 *best_rate, int *best_index)
{
	u32 diff_new = 0, diff_old = (u32) -1;
	u32 rate = rates[0];
	int index = 0;

	
	if (!rate)
		rate = rates[1];

	
	if (rate >= bitrate->legacy) {
		diff_new = 1;
		index = 1;
	}

	
	while (diff_new < diff_old) {
		if (rates[index] > 0) {
			rate += rates[index];
			if (rate >= bitrate->legacy) {
				diff_new = 0;
				diff_old = rate - bitrate->legacy;
				break;
			}
		} else {
			index++;
			continue;
		}
		index++;
	}

	*best_index = index - 1;
	*best_rate = (diff_new == 0)? 0 : (1 << diff_new);
}