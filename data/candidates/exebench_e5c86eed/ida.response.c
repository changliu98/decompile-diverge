int __cdecl SeekPoint(unsigned __int8 *TOC, int file_bytes, float percent)
{
  float fb; // [rsp+4h] [rbp-20h]
  float fa; // [rsp+8h] [rbp-1Ch]
  int a; // [rsp+10h] [rbp-14h]
  float percenta; // [rsp+14h] [rbp-10h]

  percenta = percent;
  if ( percent < 0.0 )
    percenta = 0.0;
  if ( percenta > 100.0 )
    percenta = 100.0;
  a = (int)percenta;
  if ( (int)percenta > 99 )
    a = 99;
  if ( a >= 99 )
    fb = 256.0;
  else
    fb = (float)TOC[a + 1];
  fa = (float)TOC[a];
  return (int)(float)((float)(0.00390625 * (float)((float)((float)(fb - fa) * (float)(percenta - (float)a)) + fa))
                    * (float)file_bytes);
}