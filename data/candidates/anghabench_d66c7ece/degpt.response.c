// Calculates the size of the private data structure for PWM LEDs.
// The size is determined by the number of LEDs multiplied by 4 bytes per LED,
// plus an additional 4 bytes for header or metadata.
size_t sizeof_pwm_leds_priv(int led_count)
{
  return (long)led_count * 4 + 4;
}