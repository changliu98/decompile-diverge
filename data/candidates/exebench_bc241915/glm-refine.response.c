void __cdecl fb_hSetDirty(int *dirty_start, int *dirty_end, int test_start, int test_end)
{
  // Check if the current dirty region is empty
  if ( *dirty_start == *dirty_end )
  {
    // Initialize the dirty region to the new test boundaries
    *dirty_start = test_start;
    *dirty_end = test_end;
  }
  else
  {
    // Expand the dirty region to include the new test boundaries
    if ( test_start < *dirty_start )
      *dirty_start = test_start;  // Extend the start boundary to the left
    
    if ( test_end > *dirty_end )
      *dirty_end = test_end;      // Extend the end boundary to the right
  }
}