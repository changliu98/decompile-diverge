int __cdecl sdsHdrSize(char type)
{
  switch (type & 7)
  {
    case 0:
      return 1;
    case 1:
      return 3;
    case 2:
      return 5;
    case 3:
      return 9;
    case 4:
      return 17;
    default:
      return 0;
  }
}