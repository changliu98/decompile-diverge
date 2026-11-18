void calc_sth11(float *pw, float *t) {
  float tc, pwc;
  tc = *t * 0.01f - 39.65f;
  pwc = *pw * 0.00008f + 0.01f;
  pwc = pwc * (tc - 25.0f) +
        (*pw * -0.0000015955f * *pw * *pw + 0.0367f * *pw - 2.0468f);
  if (pwc > 100.0f) pwc = 100.0f;
  if (pwc < 0.1f) pwc = 0.1f;
  *t = tc;
  *pw = pwc;
}