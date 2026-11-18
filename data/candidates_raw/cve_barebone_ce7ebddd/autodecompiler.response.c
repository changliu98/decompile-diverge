static void
remove_trailing_spaces(struct line *line, int n)
{
 int len = strlen(line->data + 8);
 if (len >= n) {
  line->data[len - n] = '\0';
  line->nspaces += n;
 }
}