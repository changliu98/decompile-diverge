int writefile(char *name,string *s)

{
  int iVar1;
  FILE *__s;
  size_t sVar2;
  int ret;
  FILE *f;
  string *s_local;
  char *name_local;
  
  __s = fopen(name,"w");
  if (__s != (FILE *)0x0) {
    ret = 0;
    sVar2 = fwrite(s + 1,1,s->n,__s);
    if ((sVar2 != s->n) || (iVar1 = fflush(__s), iVar1 != 0)) {
      warn("write %s:",name);
      ret = -1;
    }
    fclose(__s);
    return ret;
  }
  warn("open %s:",name);
  return -1;
}