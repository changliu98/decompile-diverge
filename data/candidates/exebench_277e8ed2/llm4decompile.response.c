void calc_sth11(float *p_humidity, float *p_temperature)
{
 float rh_true;
 float t_C;
 float t;
 float rh;
 float d1;
 float d2;
 float T1;
 float T2;
 float C1;
 float C2;
 float C3;

 t = *p_temperature;
 rh = *p_humidity;

 t_C = (t * 0.01f) + 25.0f;
 rh_true = (rh * 0.01f) + 0.0f;

 d1 = -40.1f + (0.01f * rh_true);
 d2 = (rh_true * rh_true) * 0.000001f;

 T1 = (t_C * 0.01f) + 0.0f;
 T2 = (T1 * T1) * 0.000001f;

 C1 = 0.00000000000001f;
 C2 = -0.00000003999999f;
 C3 = 0.000040f;

 rh_true = d1 + (d2 * 100.0f) + (T1 * C3) + (T2 * C2) + (C1 * (T1 * 100.0f));

 if (rh_true > 100.0f)
  rh_true = 100.0f;
 if (rh_true < 0.0f)
  rh_true = 0.0f;

 *p_temperature = t_C;
 *p_humidity = rh_true;
}