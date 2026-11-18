void IdealTrack(unsigned long Tracks, unsigned long Top, unsigned long Bot, unsigned long *Ideal)
{
 if (Top + Bot == 0)
  *Ideal = 1;
 else
  *Ideal = (Tracks - Bot) * Top + (Top + 1) * Bot) / (Top + Bot);
}