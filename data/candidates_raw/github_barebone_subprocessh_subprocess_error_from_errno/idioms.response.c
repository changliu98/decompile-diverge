int get_err(int err)
{
  switch (err)
    {
    case 1:
      return -5;
    case 2:
      return -4;
    case 12:
      return -6;
    case 13:
      return -5;
    case 20:
      return -4;
    case 23:
    case 24:
      return -6;
    default:
      return -1;
    }
  return -1;
}