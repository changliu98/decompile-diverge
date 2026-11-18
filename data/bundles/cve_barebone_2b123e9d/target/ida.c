int __cdecl writefile(const char *name, string *s)
{
  int ret; // [rsp+Ch] [rbp-24h]
  FILE *f; // [rsp+10h] [rbp-20h]

  f = fopen(name, "w");
  if ( f )
  {
    ret = 0;
    if ( fwrite(s->s, 1uLL, s->n, f) != s->n || fflush(f) )
    {
      vLoggingPrintf("write %s:", name);
      ret = -1;
    }
    fclose(f);
    return ret;
  }
  else
  {
    vLoggingPrintf("open %s:", name);
    return -1;
  }
}