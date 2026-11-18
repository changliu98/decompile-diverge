int writefile(char *name, struct string *s)
{
  int ret;
  struct file *f = open_file(name, "w");
  if (f == ((void *)0)) {
    print_error("open %s:", name);
    return -1;
  }
  ret = 0;
  if (write_all(s->s, 1, s->n, f) != s->n || write_end(f)) {
    print_error("write %s:", name);
    ret = -1;
  }
  close_file(f);
  return ret;
}