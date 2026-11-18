static void messageAddArgument(message *m, char *arg)
{
 int i;
 char *newarg, *p;

 do { if (!(m != NULL)) ___assert_fail("m != NULL", "harness.c", 346, "void messageAddArgument(message *, const char *)"); } while (0);
 if (!arg) return;

 while (*arg && (((*___ctype_b_loc ())[(int) ((*arg))] & (unsigned short int) 0x2000) != 0))
  arg++;

 if (!*arg || !usefulArg(arg)) return;

 for (i = 0; i < m->argc && m->argv[i] != NULL; i++) {
  if (!strcasecmp(arg, m->argv[i]))
   return;
 }

 if (i == m->argc) {
  char **new_argv;

  m->argc++;
  new_argv = cli_realloc(m->argv, sizeof(char*) * m->argc);
  if (!new_argv) {
   m->argc--;
   return;
  }
  m->argv = new_argv;
 }

 newarg = m->argv[i] = rfc2231(arg);
 if (!newarg) return;

 if (!strchr(newarg, '=')) {
  if (!strncmp(newarg, "filename", 8)) {
   newarg[8] = '=';
  } else if (!*newarg) {
   free(m->argv[i]);
   m->argv[i] = NULL;
   return;
  }
 } else if (!strncasecmp(newarg, "filename", 9) ||
            !strncasecmp(newarg, "filename*", 5)) {
  if (!messageGetMimeType(m))
   messageSetMimeType(m, "application");
 }
}