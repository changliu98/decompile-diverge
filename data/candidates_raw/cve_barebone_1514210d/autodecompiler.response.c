static int
parse_number(struct archive_entry *entry, struct archive_read *a,
    char *value)
{
 long long v;
 int (*func)(int, long long *, char **);
 int i, numargs;
 long long numbers[4];
 char *p, *v2;
 char *err = NULL;

 memset(entry, 0, sizeof(*entry));

 if ((v2 = strchr(value, ',')) != NULL) {
  *v2++ = '\0';
  func = pack_find(value);
  if (func == NULL) {
   archive_set_error(&a->archive, 22,
       "Unknown format `%s'", value);
   return (-20);
  }
  numargs = 0;
  while ((p = la_strsep(&v2, ",")) != NULL) {
   switch (*p) {
   case '\0':
    archive_set_error(&a->archive, 22,
        "Missing number");
    return (-20);
   default:
    numbers[numargs++] = mtree_atol(&p);
    if (numargs > 3) {
     archive_set_error(&a->archive, 22,
         "Too many arguments");
     return (-20);
    }
    break;
   }
  }
  if (numargs < 3) {
   archive_set_error(&a->archive, 22,
       "Not enough arguments");
   return (-20);
  }
  v = func(numargs, numbers, &err);
  if (err != NULL) {
   archive_set_error(&a->archive, 22, "%s", err);
   return (-20);
  }
 } else
  v = mtree_atol(&value);

 entry->ae_stat.aest_size = v;
 return (0);
}