void GetWord(char *out, char *in, int max)
{
  int i = 0;
  for (; ((*in < ' ') && (*in > 0)); in++);
  for (; !((((*in < ' ') && (*in < 0)) || (i >= (max - 1)))); i++)
    *out++ = *in++;
  *out = '\0';
}