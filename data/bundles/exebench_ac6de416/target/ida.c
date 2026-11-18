void __cdecl adjust_mode_num(int *mode)
{
  if ( *mode <= 9 )
  {
    if ( *mode < 0 )
      *mode = 0;
  }
  else
  {
    *mode = 9;
  }
}