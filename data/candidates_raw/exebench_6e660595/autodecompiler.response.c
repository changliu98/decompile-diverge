void track_percentages(unsigned long tracks, unsigned long done,
         unsigned long todo, unsigned long *percent)
{
 unsigned long num = done * (tracks - todo) + todo * (done + 1);
 unsigned long den = done + todo;

 if (den != 0)
  *percent = num / den;
 else
  *percent = 1;
}