int __cdecl get_sorting_mode(int c)
{
  if ( (unsigned int)c < 0x80 )
    return *(_DWORD *)(tbl_sorting_mode + 4LL * c);
  else
    return -1;
}