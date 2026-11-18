void fb_hSetDirty( int *dirty_start, int *dirty_end, int test_start, int test_end )
{
 if( *dirty_start == *dirty_end ) {
  *dirty_start = test_start;
  *dirty_end = test_end;
 }
 else {
  if( *dirty_start > test_start )
   *dirty_start = test_start;
  if( *dirty_end < test_end )
   *dirty_end = test_end;
 }
}