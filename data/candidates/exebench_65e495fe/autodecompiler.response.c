static void dopr_outch(char *buf, size_t *pos, size_t max, char c)
{
 if (*pos < max)
  buf[*pos] = c;
 (*pos)++;
}