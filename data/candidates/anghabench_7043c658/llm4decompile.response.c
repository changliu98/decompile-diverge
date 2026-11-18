unsigned short calc_speed(unsigned short *spds, int num, unsigned short dflt)
{
 int i;
 unsigned short speed = 0;

 for (i = 0; i < num; i++)
  if (spds[i] > speed)
   speed = spds[i];

 if (!speed)
  speed = dflt;

 return speed;
}