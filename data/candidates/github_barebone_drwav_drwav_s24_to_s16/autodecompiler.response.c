void drwav_s24_to_s16(drwav_int16* pOut, const drwav_uint8* pIn, size_t sampleCount)
{
 size_t i;





 for (i = 0; i < sampleCount; ++i)
 {
  int x;
  int s;

  x = ((int)(((unsigned int)(((unsigned char*)pIn)[i*3+0]) << 8) | ((unsigned int)(((unsigned char*)pIn)[i*3+1]) << 16) | ((unsigned int)(((unsigned char*)pIn)[i*3+2])) << 24)) >> 8;
  s = x >> 8;
  pOut[i] = (short)s;
 }

}