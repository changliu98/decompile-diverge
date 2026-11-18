void bo_backoff(int *bwait,int cap)

{
  int local_1c;
  int i;
  int cap_local;
  int *bwait_local;
  
  for (i = *bwait; i != 0; i = i + -1) {
  }
  local_1c = cap;
  if (*bwait * 2 < cap) {
    local_1c = *bwait << 1;
  }
  *bwait = local_1c;
  return;
}