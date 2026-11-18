static float ssm_noise(float x)
{
  return (float)(x * (x > 0.0)) + (float)(x * 0.1);
}