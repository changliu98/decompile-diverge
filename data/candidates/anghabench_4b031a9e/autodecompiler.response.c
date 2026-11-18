static int
valid_bo_pre_v2 (long mode)
{
  int valid;

  if ((mode & 0x14) == 0)
    valid = 1;
  else if ((mode & 0x14) == 4)
    valid = (mode & 2) ? 0 : 1;
  else if ((mode & 0x14) == 16)
    valid = (mode & 8) ? 0 : 1;
  else
    valid = (mode == 20) ? 1 : 0;

  return valid;
}