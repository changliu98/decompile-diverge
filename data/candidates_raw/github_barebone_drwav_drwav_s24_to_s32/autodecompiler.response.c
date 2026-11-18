void drwav_s24_to_s32(int32_t* pOut, const unsigned char* pIn, size_t sampleCount)
{
 size_t i;





 if (!pOut || !pIn) return;






 for (i = 0; i < sampleCount; ++i)
 {
  unsigned char b0 = pIn[i*3 + 0];
  unsigned char b1 = pIn[i*3 + 1];
  unsigned char b2 = pIn[i*3 + 2];

  int32_t x = (((int)b0) << 8) | ((int)b1 << 16) | ((int)b2 << 24);
  *pOut++ = x;
 }

}