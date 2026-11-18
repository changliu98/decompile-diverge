void drwav_f32_to_s16(drwav_int16* pOut, const float* pIn, size_t sampleCount)
{
 size_t i;
 for (i = 0; ; ++i) {
  if (i >= sampleCount)
   break;

  float x = pIn[i];
  float c;
  c = ((x < -1) ? -1 : ((x > 1) ? 1 : x));
  c = c + 1;
  int v = (int)(c * 32767.5f);
  v = v - 32768;
  pOut[i] = (short)v;
 }
}