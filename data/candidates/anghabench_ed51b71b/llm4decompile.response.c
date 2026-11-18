u32 get_high_speed_hz(u32 usb_rate)
{
	u32 rate = usb_rate;

	/*
	 * Account for the 12.5% overhead of the USB 2.0 protocol.
	 * Since the unified driver reports in 1ks/s, we need to
	 * adjust the rate by 1250.
	 */
	rate *= 125;
	rate += 512;
	rate /= 1024;

	return rate;
}