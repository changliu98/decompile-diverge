void update_dirty_range(int *dirty_start, int *dirty_end, int test_start, int test_end)
{
  if ( *dirty_start == *dirty_end )
  {
    *dirty_start = test_start;
    *dirty_end = test_end;
  }
  else
  {
    if ( test_start < *dirty_start )
      *dirty_start = test_start;
    if ( test_end > *dirty_end )
      *dirty_end = test_end;
  }
}