static size_t
btor_rol_n_bits (int n)
{
  size_t res;
  if (n <= 4)
    res = 4 + (size_t) n * sizeof (BtorROLNBits);
  else
    res = 4 + (size_t) (n - 4) * sizeof (BtorROLNBits) + sizeof (BtorROLNBits4);
  return res;
}