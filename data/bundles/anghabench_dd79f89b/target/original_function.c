int hx711_get_gain_to_pulse(int gain)
{
	int i;

	for (i = 0; i < HX711_GAIN_MAX; i++)
		if (hx711_gain_to_scale[i].gain == gain)
			return hx711_gain_to_scale[i].gain_pulse;
	return 1;
}