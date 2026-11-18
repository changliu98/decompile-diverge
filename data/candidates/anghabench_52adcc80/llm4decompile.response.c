unsigned_short BigUnsignedShort (unsigned_short l)
{
 byte b0,b1;

 b0 = l&0xFF;
 b1 = (l>>8)&0xFF;

 return (b0<<8) + b1;
}