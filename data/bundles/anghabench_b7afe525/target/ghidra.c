int mt76_incr(int val,int size)

{
  int size_local;
  int val_local;
  
  return val + 1U & size - 1U;
}