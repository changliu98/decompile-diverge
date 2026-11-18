void __cdecl mlCubicBezier(const float *p0, const float *p1, const float *p2, const float *p3, float t, float *v)
{
  *v = (float)((float)((float)(t * t) * t) * *p3)
     + (float)((float)((float)((float)((float)(3.0 * (float)(1.0 - t)) * t) * t) * *p2)
             + (float)((float)((float)((float)((float)(1.0 - t) * (float)(1.0 - t)) * (float)(1.0 - t)) * *p0)
                     + (float)((float)((float)((float)(3.0 * (float)(1.0 - t)) * (float)(1.0 - t)) * t) * *p1)));
  v[1] = (float)((float)((float)(t * t) * t) * p3[1])
       + (float)((float)((float)((float)((float)(3.0 * (float)(1.0 - t)) * t) * t) * p2[1])
               + (float)((float)((float)((float)((float)(1.0 - t) * (float)(1.0 - t)) * (float)(1.0 - t)) * p0[1])
                       + (float)((float)((float)((float)(3.0 * (float)(1.0 - t)) * (float)(1.0 - t)) * t) * p1[1])));
  v[2] = (float)((float)((float)(t * t) * t) * p3[2])
       + (float)((float)((float)((float)((float)(3.0 * (float)(1.0 - t)) * t) * t) * p2[2])
               + (float)((float)((float)((float)((float)(1.0 - t) * (float)(1.0 - t)) * (float)(1.0 - t)) * p0[2])
                       + (float)((float)((float)((float)(3.0 * (float)(1.0 - t)) * (float)(1.0 - t)) * t) * p1[2])));
}