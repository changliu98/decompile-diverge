void update16(unsigned short* pI, int max, int add, int saturation)
{
 if( *pI <= max )
  *pI = *pI + add;
 else
  *pI = saturation;
}