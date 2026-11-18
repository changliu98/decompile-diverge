void foo(unsigned char *set)
{
  int i;
  for (i = 0; i < 16; i++)
    set[i] = 0xff;
}