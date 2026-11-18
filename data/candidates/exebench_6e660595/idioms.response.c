void IdealTrack(unsigned long tracks, unsigned long top, unsigned long bot, unsigned long *ideal)
{
  if (top + bot == 0)
    *ideal = 1;
  else
    *ideal = (top * (top + 1) + (tracks - bot) * top) / (top + bot);
}