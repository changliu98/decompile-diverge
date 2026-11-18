void edosk2674_smsc_outw(unsigned_short d,unsigned_short *a)

{
  unsigned_short *a_local;
  unsigned_short d_local;
  
  *a = d >> 8 | d << 8;
  return;
}