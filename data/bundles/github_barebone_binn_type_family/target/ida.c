int __cdecl type_family(int type)
{
  if ( !type )
    return 241;
  if ( (unsigned int)(type - 32) < 2 || (unsigned int)(type - 64) < 2 || (unsigned int)(type - 96) < 2 )
    return 242;
  if ( type == 98 )
    return 243;
  if ( (unsigned int)(type - 128) < 2 )
    return 242;
  switch ( type )
  {
    case 130:
      return 243;
    case 131:
      return 244;
    case 160:
      return 244;
  }
  if ( (unsigned int)(type - 161) < 4 )
    return 244;
  if ( (unsigned int)(type - 166) < 2 )
    return 243;
  if ( type == 192 )
    return 245;
  if ( (unsigned int)(type - 224) < 3 )
    return 247;
  if ( (unsigned int)(type - 45057) < 5 )
    return 244;
  if ( (unsigned int)(type - 53249) < 4 )
    return 245;
  if ( type == 524385 )
    return 246;
  else
    return 0;
}