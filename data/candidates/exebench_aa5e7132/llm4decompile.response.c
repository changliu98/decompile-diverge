void GetWord(char *out, char *in, int max)
{
 int len = 0;

 while (*in > 0 && *in <= 32)
  in++;

 while (*in > 32 || *in < 0)
 {
  if (len < max - 1)
  {
   *out = *in;
   out++;
   len++;
  }
  in++;
 }
 *out = 0;
}