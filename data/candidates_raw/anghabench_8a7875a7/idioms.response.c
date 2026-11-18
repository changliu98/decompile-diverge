char to_hex(unsigned char val)
{
  if (val < 10)
    return (val + '0');
  if (val < 16)
    return ('a' - 10 + val);
  return '?';
}