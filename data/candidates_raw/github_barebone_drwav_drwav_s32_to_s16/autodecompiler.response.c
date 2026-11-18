void drwav_s32_to_s16(short* pOut, const int* pIn, size_t sampleCount)
{
 size_t i;
# 7122 "/scratch/repos/new/home/jordi_armengol_estape/c-scraper/outputs/2022-01-22/02-19-57/repos/realnc/hlsdk/refs/heads/master/common/dr_wav.h"
 for (i = 0; i < sampleCount; ++i) {
  int x = pIn[i];
  int clamped = x;
  if (clamped < -32768) {
   clamped = -32768;
  }
  if (clamped > 32767) {
   clamped = 32767;
  }
  pOut[i] = (short)clamped;
 }

}