__attribute__((used)) static int hx711_get_gain(int gain)
{
	int i;
	int ret;

	for (i = 0;; i++) {
		if (i >= HX711_GAIN_MAX) {
			ret = 1;
			break;
		} else if (hx711_gain_to_scale[i].gain == gain) {
			ret = hx711_gain_to_scale[i].scale;
			break;
		}
	}

	return ret;
}