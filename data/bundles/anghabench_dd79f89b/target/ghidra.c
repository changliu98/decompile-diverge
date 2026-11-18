int hx711_get_gain_to_pulse(int gain)

{
  int i;
  int gain_local;
  
  i = 0;
  while( true ) {
    if (HX711_GAIN_MAX <= i) {
      return 1;
    }
    if (hx711_gain_to_scale[i].gain == gain) break;
    i = i + 1;
  }
  return hx711_gain_to_scale[i].gain_pulse;
}