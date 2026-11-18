void messageAddArgument(message *m,char *arg)

{
  int iVar1;
  mime_type mVar2;
  ushort **ppuVar3;
  char **ppcVar4;
  char *__s;
  char *pcVar5;
  char **q;
  char *p;
  int offset;
  char *arg_local;
  message *m_local;
  
  if (m == (message *)0x0) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("m != NULL","/work/harness.c",0x15a,
                  "void messageAddArgument(message *, const char *)");
  }
  arg_local = arg;
  if (arg != (char *)0x0) {
    while (ppuVar3 = __ctype_b_loc(), ((*ppuVar3)[(int)*arg_local] & 0x2000) != 0) {
      arg_local = arg_local + 1;
    }
    if ((*arg_local != '\0') && (iVar1 = usefulArg(arg_local), iVar1 != 0)) {
      for (offset = 0; (offset < m->numberOfArguments && (m->mimeArguments[offset] != (char *)0x0));
          offset = offset + 1) {
        iVar1 = strcasecmp(arg_local,m->mimeArguments[offset]);
        if (iVar1 == 0) {
          return;
        }
      }
      if (offset == m->numberOfArguments) {
        m->numberOfArguments = m->numberOfArguments + 1;
        ppcVar4 = cli_realloc(m->mimeArguments,(long)m->numberOfArguments << 3);
        if (ppcVar4 == (char **)0x0) {
          m->numberOfArguments = m->numberOfArguments + -1;
          return;
        }
        m->mimeArguments = ppcVar4;
      }
      __s = rfc2231(arg_local);
      m->mimeArguments[offset] = __s;
      if (__s != (char *)0x0) {
        pcVar5 = strchr(__s,0x3d);
        if (pcVar5 == (char *)0x0) {
          iVar1 = strncmp(__s,"filename",8);
          if (iVar1 != 0) {
            free(m->mimeArguments[offset]);
            m->mimeArguments[offset] = (char *)0x0;
            return;
          }
          __s[8] = '=';
        }
        iVar1 = strncasecmp(__s,"filename=",9);
        if (((iVar1 == 0) || (iVar1 = strncasecmp(__s,"name=",5), iVar1 == 0)) &&
           (mVar2 = messageGetMimeType(m), mVar2 == NOMIME)) {
          messageSetMimeType(m,"application");
        }
      }
    }
  }
  return;
}