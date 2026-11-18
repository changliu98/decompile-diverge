int16 Clamp(int val)
{
 int16 i;
 int16 ret;

 if (val < -32767) {
  ret = -32767;
 } else {
  if (val > 32767) {
   i = 32767;
  } else {
   i = (int16)val;
  }
  ret = i;
 }

 return ret;
}