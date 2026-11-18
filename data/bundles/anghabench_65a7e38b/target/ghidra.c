int SCALE(long val,int mul,int div)

{
  int div_local;
  int mul_local;
  long val_local;
  undefined4 local_c;
  
  if (val < 0) {
    local_c = (int)((val * mul - (long)(div / 2)) / (long)div);
  }
  else {
    local_c = (int)((val * mul + (long)(div / 2)) / (long)div);
  }
  return local_c;
}