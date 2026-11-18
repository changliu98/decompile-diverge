void __cdecl Perl_my_setenv(const char *nam, const char *val)
{
  int vlen; // [rsp+0h] [rbp-20h]
  int nlen; // [rsp+4h] [rbp-1Ch]
  char *envstr; // [rsp+8h] [rbp-18h]
  const char *vala; // [rsp+10h] [rbp-10h]

  vala = val;
  nlen = strlen(nam);
  if ( !val )
    vala = "";
  vlen = strlen(vala);
  envstr = (char *)vb_safesysmalloc(vlen + nlen + 2);
  memcpy(envstr, nam, nlen);
  envstr[nlen] = 61;
  memcpy(&envstr[nlen + 1], vala, vlen);
  envstr[vlen + 1 + nlen] = 0;
  vb_PerlEnv_putenv(envstr);
  free(envstr);
}