void strcpy_(char *dst, char *src)
{
  while (*src)
    *(dst++) = *(src++);
  *dst = 0;
}