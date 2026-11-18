int seq_diff(int s, int c)
{
 int diff;

 if (c <= s)
  diff = s - c;
 else
  diff = (8 - c) + s;

 return diff;
}