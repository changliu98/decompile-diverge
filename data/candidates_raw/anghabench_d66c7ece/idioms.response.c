static int get_led_data_size(int num_leds)
{
  return sizeof(struct led_data) + (num_leds * sizeof(struct led_data_per_led));
}