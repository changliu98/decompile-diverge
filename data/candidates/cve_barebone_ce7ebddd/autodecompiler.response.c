static void
delete_buff_tail(struct line *line, int n)
{
 int len = strlen(line->data + 8);
 if (len >= n) {
  line->data[len - n] = '\0';
  line->nspaces += n;
 }
}