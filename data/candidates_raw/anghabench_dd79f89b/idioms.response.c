int hx711_get_scale(int gain)
{
  int i = 0;
  for (i = 0; i < HX711_GAIN_MAX; i++)
  {
    if (hx711_gain_to_scale[i].gain == gain)
    {
      return (hx711_gain_to_scale[i].scale);
    }
  }
  return (1);
}