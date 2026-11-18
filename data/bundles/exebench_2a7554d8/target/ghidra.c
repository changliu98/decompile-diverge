int replace(char *rps,char whatc,char toc)

{
  char *p1;
  char toc_local;
  char whatc_local;
  char *rps_local;
  
  for (p1 = strchr(rps,(int)whatc); p1 != (char *)0x0; p1 = strchr(p1 + 1,(int)whatc)) {
    *p1 = toc;
  }
  return 0;
}