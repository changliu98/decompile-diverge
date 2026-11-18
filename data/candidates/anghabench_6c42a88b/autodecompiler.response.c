static size_t
ext4_acl_size (int n)
{
  size_t res;
  if (n <= 4)
    res = 4 + (size_t) n * sizeof (BtorROLNBits);
  else
    res = 4 + (size_t) (n - 4) * sizeof (BtorROLNBits) + sizeof (BtorROLNBits4);
  return res;
}