int get_size(int type)
{
  int size = 0;
  type = type & 0x7;
  switch (type)
  {
    case 0:
      size = 1;
      break;
    case 1:
      size = 3;
      break;
    case 2:
      size = 5;
      break;
    case 3:
      size = 9;
      break;
    case 4:
      size = 17;
      break;
    default:
      size = 0;
      break;
  }
  return size;
}