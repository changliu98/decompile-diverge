static int sizeof_pwm_leds_priv(int num_leds)
{
  return sizeof(struct led_data) + (num_leds * sizeof(struct led_data_per_led));
}