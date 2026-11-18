unsigned_short calc_speed(unsigned_short *spds,int num,unsigned_short dflt)

{
  int i;
  unsigned_short speed;
  unsigned_short dflt_local;
  int num_local;
  unsigned_short *spds_local;
  
  speed = 0;
  for (i = 0; i < num; i = i + 1) {
    if (speed < spds[i]) {
      speed = spds[i];
    }
  }
  if (speed == 0) {
    speed = dflt;
  }
  return speed;
}