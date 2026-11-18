char * func0(int interval1_start,int interval1_end,int interval2_start,int interval2_end)

{
  int local_38;
  int local_34;
  int i;
  int l;
  int inter2;
  int inter1;
  int interval2_end_local;
  int interval2_start_local;
  int interval1_end_local;
  int interval1_start_local;
  char *local_10;
  
  local_34 = interval2_start;
  if (interval2_start < interval1_start) {
    local_34 = interval1_start;
  }
  local_38 = interval2_end;
  if (interval1_end < interval2_end) {
    local_38 = interval1_end;
  }
  local_38 = local_38 - local_34;
  if (local_38 < 2) {
    local_10 = "NO";
  }
  else {
    for (i = 2; i * i <= local_38; i = i + 1) {
      if (local_38 % i == 0) {
        local_10 = "NO";
        return local_10;
      }
    }
    local_10 = "YES";
  }
  return local_10;
}