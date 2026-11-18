char *bittok2str(struct bittok_t *table, char *def_fmt, int val, char *sep)
{
 char *fmt;
 int i, len = 0;
 char *sepstr = "";
 static char bittok2str_internal_buf[256];

 while (1) {
  if (!table || !table->name)
   break;
  i = table->val;
  for (int j = 1; j; j <<= 1) {
   if (i == (val & j)) {
    len += snprintf(bittok2str_internal_buf + len,
      sizeof(bittok2str_internal_buf) - len,
      "%s%s", sepstr, table->name);
    sepstr = sep;
   }
  }
  table++;
 }
 if (!len) {
  if (!def_fmt)
   fmt = "#%08x";
  else
   fmt = def_fmt;
  snprintf(bittok2str_internal_buf, sizeof(bittok2str_internal_buf),
    fmt, val);
 }
 return bittok2str_internal_buf;
}