int __cdecl sdsHdrSize(char type)
{
  int v2; // [rsp+Ch] [rbp-4h]

  switch ( type & 7 )
  {
    case 0:
      v2 = 1;
      break;
    case 1:
      v2 = 3;
      break;
    case 2:
      v2 = 5;
      break;
    case 3:
      v2 = 9;
      break;
    case 4:
      v2 = 17;
      break;
    default:
      v2 = 0;
      break;
  }
  return v2;
}