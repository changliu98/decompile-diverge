static int BinaryFiles__swap_bytes32(int *i)
{
 int j = ((*i & 0xff) << 24) + ((*i & 0xff00) << 8) +
  ((*i & 0xff0000) >> 8) + ((*i & 0xff000000) >> 24);
 return *i = j;
}