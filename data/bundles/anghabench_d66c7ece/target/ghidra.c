size_t sizeof_pwm_leds_priv(int num_leds)

{
  int num_leds_local;
  
  return (long)num_leds * 4 + 4;
}