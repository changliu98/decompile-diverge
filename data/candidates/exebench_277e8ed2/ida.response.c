void __cdecl calc_sth11(float *p_humidity, float *p_temperature)
{
  float t_C; // [rsp+0h] [rbp-40h]
  float rh_true; // [rsp+4h] [rbp-3Ch]

  t_C = (float)(*p_temperature * 0.0099999998) + -39.650002;
  rh_true = (float)((float)(t_C - 25.0) * (float)((float)(*p_humidity * 0.000079999998) + 0.0099999998))
          + (float)((float)((float)((float)(-0.0000015955 * *p_humidity) * *p_humidity)
                          + (float)(0.036699999 * *p_humidity))
                  + -2.0467999);
  if ( rh_true > 100.0 )
    rh_true = 100.0;
  if ( rh_true < 0.1 )
    rh_true = 0.1;
  *p_temperature = t_C;
  *p_humidity = rh_true;
}