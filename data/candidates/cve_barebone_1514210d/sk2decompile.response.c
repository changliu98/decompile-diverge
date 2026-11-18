static int parse_device(struct mtree_entry *entry, struct archive *a,
                        char *p) {
  dev_t dev;
  const char *q;
  const char *r;
  const char *errstr = NULL;
  unsigned long nums[3];
  int num_nums;
  pack_function_p pack;
  memset(entry, 0, sizeof(*entry));
  q = strchr(p, ',');
  if (q != NULL) {
    *q++ = '\0';
    pack = pack_find(p);
    if (pack == NULL) {
      archive_set_error(a, 22, "Unknown format `%s'", p);
      return (-20);
    }
    num_nums = 0;
    while ((r = la_strsep(&q, ",")) != NULL) {
      if (*r == '\0') {
        archive_set_error(a, 22, "Missing number");
        return (-20);
      }
      nums[num_nums++] = mtree_atol(&r);
      if (num_nums > 3) {
        archive_set_error(a, 22, "Too many arguments");
        return (-20);
      }
    }
    if (num_nums < 2) {
      archive_set_error(a, 22, "Not enough arguments");
      return (-20);
    }
    dev = pack(num_nums, nums, &errstr);
    if (errstr != NULL) {
      archive_set_error(a, 22, "%s", errstr);
      return (-20);
    }
  } else {
    dev = mtree_atol(&p);
  }
  entry->dev = dev;
  return (0);
}