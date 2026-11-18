float __cdecl ramp_activate(float x)
{
  return x * 0.1 + (float)(x * (float)(x > 0.0));
}