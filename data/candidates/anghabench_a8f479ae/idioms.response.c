static int ice_txd_use_count(int size)
{
  return (size * 85 / 4) + 1;
}