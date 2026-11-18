void __cdecl calc_sth11(float *p_humidity, float *p_temperature)
{
  // Datasheet constants for SHT1x/SHT7x
  const float d1 = -39.65f;       // Temperature offset for 3.3V supply
  const float d2 = 0.01f;         // Temperature slope (14-bit resolution)
  
  const float c1 = -2.0468f;      // Humidity constant 1
  const float c2 = 0.0367f;       // Humidity constant 2
  const float c3 = -1.5955e-3f;   // Humidity constant 3
  
  const float t1 = 0.01f;         // Temperature compensation coefficient 1
  const float t2 = 0.00008f;      // Temperature compensation coefficient 2

  // 1. Convert raw temperature to Celsius
  float t_C = (*p_temperature * d2) + d1;

  // 2. Calculate relative humidity (RH_linear)
  float rh_linear = (c3 * (*p_humidity) * (*p_humidity)) + (c2 * (*p_humidity)) + c1;

  // 3. Apply temperature compensation to get true relative humidity (RH_true)
  float rh_true = ((t_C - 25.0f) * (t1 + (t2 * (*p_humidity)))) + rh_linear;

  // 4. Clamp humidity to valid sensor range
  if (rh_true > 100.0f)
    rh_true = 100.0f;
  if (rh_true < 0.1f)
    rh_true = 0.1f;

  // 5. Output the calculated values
  *p_temperature = t_C;
  *p_humidity = rh_true;
}