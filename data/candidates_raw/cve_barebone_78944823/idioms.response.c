int regex_sub(struct arg *arg, struct sample *smp, void *priv)
{
  struct my_regex *reg = (my_regex *)arg->data.reg;
  struct buffer *trash = buffer_new();
  char *start = (char *)smp->data.u.str.area;
  char *end = start + smp->data.u.str.data;
  int flag = 0;
  int found = 0;
  int max;
  while (1) {
    if (arg->type_flags & 0x02 || (flag & 1))
      found = regex_match(reg, start, end - start, 10, pmatch, flag);
    if (!found)
      pmatch[0].rm_so = end - start;
    max = trash->size - trash->data;
    if (max > 0 && pmatch[0].rm_so > 0) {
      int len = (pmatch[0].rm_so < max) ? pmatch[0].rm_so : max;
      buffer_append(trash->area + trash->data, start, len);
      trash->data += len;
    }
    if (!found || !start || start >= end)
      break;
    if (!pmatch[0].rm_eo) {
      if (trash->data < trash->size)
        trash->area[trash->data++] = *start;
      pmatch[0].rm_eo++;
    }
    start += pmatch[0].rm_eo;
  }
  smp->data.u = trash->data;
  return 1;
}