void drwav_u8_to_s32(drwav_int32* pOut, const drwav_uint8* pIn, size_t sampleCount)
{
 size_t i;
 if( pOut == NULL || pIn == NULL ) return;

 for( i = 0 ; i < sampleCount ; ++i )
 {
  drwav_uint8 u8 = pIn[i];
  *pOut++ = ((int)u8) * 8388608;
 }
}