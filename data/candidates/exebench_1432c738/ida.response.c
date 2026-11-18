void __cdecl OsdGetBoxSplineWeights(float v, float w, float *wP)
{
  int i; // [rsp+0h] [rbp-3Ch]
  float w3; // [rsp+8h] [rbp-34h]
  float w2; // [rsp+Ch] [rbp-30h]
  float v3; // [rsp+14h] [rbp-28h]
  float v2; // [rsp+18h] [rbp-24h]
  float u3; // [rsp+20h] [rbp-1Ch]
  float u2; // [rsp+24h] [rbp-18h]
  float u; // [rsp+28h] [rbp-14h]

  u = (float)(1.0 - v) - w;
  u2 = u * u;
  u3 = u * (float)(u * u);
  v2 = v * v;
  v3 = v * (float)(v * v);
  w2 = w * w;
  w3 = w * (float)(w * w);
  *wP = (float)((float)(2.0 * u3) * v) + (float)(u * u3);
  wP[1] = (float)((float)(2.0 * u3) * w) + (float)(u * u3);
  wP[8] = (float)((float)(2.0 * w3) * u) + (float)(w * w3);
  wP[11] = (float)((float)(2.0 * w3) * v) + (float)(w * w3);
  wP[9] = (float)((float)(2.0 * v3) * w) + (float)(v * v3);
  wP[5] = (float)((float)(2.0 * v3) * u) + (float)(v * v3);
  wP[2] = (float)((float)((float)(6.0 * (float)(v * v)) * u) * w)
        + (float)((float)((float)(6.0 * v3) * u)
                + (float)((float)((float)(2.0 * v3) * w)
                        + (float)((float)((float)((float)(12.0 * (float)(u * u)) * (float)(v * v))
                                        + (float)((float)((float)((float)(6.0 * (float)(u * u)) * v) * w)
                                                + (float)((float)((float)(6.0 * u3) * v)
                                                        + (float)((float)((float)(2.0 * u3) * w) + (float)(u * u3)))))
                                + (float)(v * v3))));
  wP[4] = (float)((float)((float)(6.0 * (float)(u * u)) * v) * w)
        + (float)((float)((float)(6.0 * u3) * w)
                + (float)((float)((float)(2.0 * u3) * v)
                        + (float)((float)((float)((float)(12.0 * (float)(w * w)) * (float)(u * u))
                                        + (float)((float)((float)((float)(6.0 * (float)(w * w)) * u) * v)
                                                + (float)((float)((float)(6.0 * w3) * u)
                                                        + (float)((float)((float)(2.0 * w3) * v) + (float)(w * w3)))))
                                + (float)(u * u3))));
  wP[10] = (float)((float)((float)(6.0 * w3) * u) * v)
         + (float)((float)((float)(6.0 * w3) * v)
                 + (float)((float)((float)(2.0 * w3) * u)
                         + (float)((float)((float)((float)(12.0 * (float)(v * v)) * (float)(w * w))
                                         + (float)((float)((float)((float)(6.0 * (float)(v * v)) * w) * u)
                                                 + (float)((float)((float)(6.0 * v3) * w)
                                                         + (float)((float)((float)(2.0 * v3) * u) + (float)(v * v3)))))
                                 + (float)(w * w3))));
  wP[3] = (float)((float)(12.0 * v2) * w2)
        + (float)((float)((float)((float)(60.0 * u2) * v) * w)
                + (float)((float)((float)(u * u3) * 6.0)
                        + (float)((float)((float)(24.0 * w) * u3)
                                + (float)((float)((float)(24.0 * w2) * u2)
                                        + (float)((float)((float)((float)(36.0 * w2) * v) * u)
                                                + (float)((float)((float)(8.0 * w3) * u)
                                                        + (float)((float)((float)(6.0 * w3) * v)
                                                                + (float)((float)((float)((float)(24.0 * v) * u3)
                                                                                + (float)((float)((float)(24.0 * v2) * u2)
                                                                                        + (float)((float)((float)((float)(36.0 * v2) * w) * u)
                                                                                                + (float)((float)((float)(8.0 * v3) * u) + (float)((float)((float)(6.0 * v3) * w) + (float)(v * v3))))))
                                                                        + (float)(w * w3)))))))));
  wP[6] = (float)((float)(12.0 * w2) * u2)
        + (float)((float)((float)((float)(60.0 * v2) * w) * u)
                + (float)((float)((float)(v * v3) * 6.0)
                        + (float)((float)((float)(24.0 * u) * v3)
                                + (float)((float)((float)(24.0 * u2) * v2)
                                        + (float)((float)((float)((float)(36.0 * u2) * v) * w)
                                                + (float)((float)((float)(8.0 * u3) * v)
                                                        + (float)((float)((float)(6.0 * u3) * w)
                                                                + (float)((float)((float)((float)(24.0 * w) * v3)
                                                                                + (float)((float)((float)(24.0 * w2) * v2)
                                                                                        + (float)((float)((float)((float)(36.0 * w2) * u) * v)
                                                                                                + (float)((float)((float)(8.0 * w3) * v) + (float)((float)((float)(6.0 * w3) * u) + (float)(w * w3))))))
                                                                        + (float)(u * u3)))))))));
  wP[7] = (float)((float)(12.0 * u2) * v2)
        + (float)((float)((float)((float)(60.0 * w2) * u) * v)
                + (float)((float)((float)(w * w3) * 6.0)
                        + (float)((float)((float)(24.0 * v) * w3)
                                + (float)((float)((float)(24.0 * v2) * w2)
                                        + (float)((float)((float)((float)(36.0 * v2) * u) * w)
                                                + (float)((float)((float)(8.0 * v3) * w)
                                                        + (float)((float)((float)(6.0 * v3) * u)
                                                                + (float)((float)((float)((float)(24.0 * u) * w3)
                                                                                + (float)((float)((float)(24.0 * u2) * w2)
                                                                                        + (float)((float)((float)((float)(36.0 * u2) * v) * w)
                                                                                                + (float)((float)((float)(8.0 * u3) * w) + (float)((float)((float)(6.0 * u3) * v) + (float)(u * u3))))))
                                                                        + (float)(v * v3)))))))));
  for ( i = 0; i < 12; ++i )
    wP[i] = 0.083333336 * wP[i];
}