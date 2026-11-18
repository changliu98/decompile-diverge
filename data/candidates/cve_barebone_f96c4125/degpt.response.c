void special_keys(char_u *args)

{
  char cVar1;
  char *__s;
  char *pcVar2;
  size_t sVar3;
  int iVar4;
  int i;
  char cmdbuf [256];
  char keybuf [64];
  char *sep;
  char *tok;
  char *save_str;
  char_u *args_local;
  
  __s = nb_unquote(args,(char_u **)0x0);
  tok = strtok(__s," ");
  while (tok != (char *)0x0) {
    i = 0;
    pcVar2 = strchr(tok,0x2d);
    if (pcVar2 != (char *)0x0) {
      *pcVar2 = '\0';
      for (; *tok != '\0'; tok = tok + 1) {
        cVar1 = *tok;
        if ((((cVar1 == 'A') || (cVar1 == 'C')) || (cVar1 == 'M')) || (cVar1 == 'S')) {
          iVar4 = i + 1;
          keybuf[i] = *tok;
          i = i + 2;
          keybuf[iVar4] = '-';
        }
      }
      tok = tok + 1;
    }
    sVar3 = strlen(tok);
    if (sVar3 + (long)i < 0x40) {
      strcpy(keybuf + i,tok);
      vim_snprintf(cmdbuf,0x100,"<silent><%s> :nbkey %s<CR>",keybuf,keybuf);
      do_map(0,(char_u *)cmdbuf,1,0);
    }
    tok = strtok((char *)0x0," ");
  }
  vim_free(__s);
  return;
}