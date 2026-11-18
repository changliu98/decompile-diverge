static void
special_keys(char_u *keys)
{
    char_u *p;
    char_u *q;
    int i;
    char_u buf[256];
    char_u keybuf[64];

    p = nb_unquote(keys, NULL);

    for (q = strtok(p, " "); q != NULL; q = strtok(NULL, " "))
    {
 i = 0;

 if ((q = strchr(q, '-')) != NULL)
 {
     *q = '\0';
     while (*q != '\0')
     {
  switch (*q)
  {
      case 'C':
      case 'M':
      case 'S':
      case 'A':
   keybuf[i++] = *q;
   keybuf[i++] = '-';
   break;
  }
  ++q;
     }
 }
 else
     ++q;

 if (strlen(q) + i < sizeof(keybuf))
 {
     strcpy(keybuf + i, q);
     vim_snprintf((char *)buf, sizeof(buf),
      "<silent><%s> :nbkey %s<CR>", keybuf, keybuf);
     do_map(0, buf, 1, 0);
 }
    }

    vim_free(p);
}