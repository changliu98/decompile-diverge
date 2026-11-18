int put_le16(void *ptr, int val)
{
  int *p = (int *)ptr;
  *p = (val);
  return (val);
}