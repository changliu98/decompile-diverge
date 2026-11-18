int sizeof_ns2_led_priv(int num_leds)

{
  int num_leds_local;
  
  return num_leds * 4 + 4;
}