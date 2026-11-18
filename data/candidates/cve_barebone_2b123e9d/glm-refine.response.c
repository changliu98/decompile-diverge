int __cdecl writefile(const char *name, string *s)
{
  FILE *f = fopen(name, "w");
  
  if ( !f )
  {
    vLoggingPrintf("open %s:", name);
    return -1;
  }

  // Check if the full string was written and the stream was successfully flushed
  if ( fwrite(s->s, 1, s->n, f) != s->n || fflush(f) )
  {
    vLoggingPrintf("write %s:", name);
    fclose(f);
    return -1;
  }

  fclose(f);
  return 0;
}