void drwav_u8_to_s32(float *pOut, unsigned char *pIn, unsigned long sampleCount)
{
    if ( pOut && pIn )
    {
        for ( unsigned long i = 0; i < sampleCount; i++ )
        {
            *pOut++ = ( ( ( ( ( pIn[i] ) - ( (unsigned char)(128) ) ) * ( (float)(1.0f) ) ) * ( (float)(1.0f) ) ) * ( (float)(1.0f) ) ) * ( (float)(1.0f) );
        }
    }
    return;
}