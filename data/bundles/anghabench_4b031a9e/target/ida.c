int __cdecl valid_bo_pre_v2(long value)
{
  switch ( value & 0x14 )
  {
    case 0LL:
      return 1;
    case 4LL:
      return (value & 2) == 0;
    case 16LL:
      return (value & 8) == 0;
  }
  return value == 20;
}