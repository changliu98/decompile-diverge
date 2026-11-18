float __cdecl xCorrCoef(float *target, float *regressor, int subl)
{
  float dot_product = 0.0f;
  float energy_regressor = 0.0f;

  for (int i = 0; i < subl; ++i)
  {
    dot_product += target[i] * regressor[i];
    energy_regressor += regressor[i] * regressor[i];
  }

  if (dot_product <= 0.0f)
    return 0.0f;
  else
    return (dot_product * dot_product) / energy_regressor;
}