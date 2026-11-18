void
special_keys(char_u *args)
{
    char_u *arg;
    char *cmd;
    char *p;
    char buf[256];
    char keybuf[64];
    int i;

    arg = nb_unquote(args, NULL);

    cmd = " :nbkey %s<CR>";

    p = strtok((char *)arg, " ");
    while (p != NULL)
    {
 i = 0;
 if (strchr(p, '-') != NULL)
 {
     char *s;

     *strchr(p, '-') = '\0';
     s = p;
     while (*s != '\0')
     {
  if (*s == 'A' || *s == 'C' || *s == 'M' || *s == 'S')
  {
      keybuf[i++] = *s;
      keybuf[i++] = '-';
  }
  ++s;
     }
     ++p;
 }
 if (strlen(p) + i < sizeof(keybuf))
 {
     strcpy(keybuf + i, p);
     vim_snprintf(buf, sizeof(buf), cmd, keybuf);
     do_map(0, (char_u *)buf, 1, 0);
 }
 p = strtok(NULL, " ");
    }

    vim_free(arg);
}