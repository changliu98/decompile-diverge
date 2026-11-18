void Perl_my_setenv(char *nam,char *val)

{
  int iVar1;
  int iVar2;
  size_t sVar3;
  char *s;
  int vlen;
  int nlen;
  char *envstr;
  char *val_local;
  char *nam_local;
  
  sVar3 = strlen(nam);
  iVar1 = (int)sVar3;
  val_local = val;
  if (val == (char *)0x0) {
    val_local = "";
  }
  sVar3 = strlen(val_local);
  iVar2 = (int)sVar3;
  s = vb_safesysmalloc((long)(iVar1 + iVar2 + 2));
  memcpy(s,nam,(long)iVar1);
  s[iVar1] = '=';
  memcpy(s + (iVar1 + 1),val_local,(long)iVar2);
  s[iVar1 + 1 + iVar2] = '\0';
  vb_PerlEnv_putenv(s);
  free(s);
  return;
}