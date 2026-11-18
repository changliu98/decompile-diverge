int llc_shdlc_w_used(int s, int c)
{
 int diff;

 if (c <= s)
  diff = s - c;
 else
  diff = (8 - c) + s;

 return diff;
}