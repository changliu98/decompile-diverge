void IdealTrack(unsigned_long tracks,unsigned_long top,unsigned_long bot,unsigned_long *ideal)

{
  unsigned_long den;
  unsigned_long num;
  unsigned_long *ideal_local;
  unsigned_long bot_local;
  unsigned_long top_local;
  unsigned_long tracks_local;
  
  if (top + bot == 0) {
    *ideal = 1;
  }
  else {
    *ideal = (top * (tracks - bot) + bot * (top + 1)) / (top + bot);
  }
  return;
}