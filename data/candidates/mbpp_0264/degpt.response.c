double func0(int h_age)

{
  double d_age;
  int h_age_local;
  
  if (h_age < 0) {
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  if (h_age < 3) {
    d_age = (double)h_age * DAT_00102008;
  }
  else {
    d_age = (double)((h_age + -2) * 4 + 0x15);
  }
  return d_age;
}