int sizeof_ns2_led_priv(int num_leds)
{
	return sizeof(struct ns2_led_priv) +
		      (sizeof(struct ns2_led_data) * num_leds);
}