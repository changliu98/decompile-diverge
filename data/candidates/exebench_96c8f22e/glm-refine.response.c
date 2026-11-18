void __cdecl pa(float *e, float t, float t2)
{
  for (int j = 0; j < 6; ++j)
  {
    float e0 = e[0];
    float e1 = e[1];
    float e2 = e[2];
    float e3 = e[3];

    e[0] = ((e0 + e1) + e2 - e3) * t;
    e[1] = ((e0 + e1) - e2 + e3) * t;
    e[2] = ((e0 - e1) + e2 + e3) * t;
    e[3] = (-e0 + e1 + e2 + e3) / t2;
  }
}