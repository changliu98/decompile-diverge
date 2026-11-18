void __cdecl count_down(int *counter, int *ghost_counter)
{
  int i; // [rsp+0h] [rbp-14h]

  if ( *counter > 0 )
    --*counter;
  for ( i = 0; i < 4; ++i )
  {
    if ( ghost_counter[i] > 0 )
      --ghost_counter[i];
  }
}