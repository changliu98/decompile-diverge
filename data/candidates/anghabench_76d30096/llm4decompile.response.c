int sizeof_ns2_led_priv(int num_leds)
{
	return sizeof(struct ns2_led_priv) +
	       num_leds * sizeof(struct ns2_led_priv_led);
}