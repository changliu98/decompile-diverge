void fb_hSetDirty(int *dirty_start,int *dirty_end,int test_start,int test_end)

{
  int test_end_local;
  int test_start_local;
  int *dirty_end_local;
  int *dirty_start_local;
  
  if (*dirty_start == *dirty_end) {
    *dirty_start = test_start;
    *dirty_end = test_end;
  }
  else {
    if (test_start < *dirty_start) {
      *dirty_start = test_start;
    }
    if (*dirty_end < test_end) {
      *dirty_end = test_end;
    }
  }
  return;
}