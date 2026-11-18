void convert_to_celsius(float *p_humidity, float *p_temperature)
{
  float t_C;
  float rh_true;
  t_C = -39.65 + (0.01 * *p_temperature);
  rh_true = -2.0468 - (0.0000015955 * *p_humidity) + (0.0367 * *p_humidity) - (0.00007999 * *p_humidity * t_C) + (0.0099 * t_C);
  if (rh_true > 100.0)
    rh_true = 100.0;
  if (rh_true < 0.1)
    rh_true = 0.1;
  *p_temperature = t_C;
  *p_humidity = rh_true;
}