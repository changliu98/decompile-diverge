void MV_BytesToFloats( float *pOut, int *pIn, unsigned long numSamples )
{
 unsigned long i;

 if (( pOut == NULL ) || ( pIn == NULL ))
 {
  return;
 }

 for( i = 0; i < numSamples; i++ )
 {
  *pOut++ = (float) pIn[i] / 32768.0;
 }
}