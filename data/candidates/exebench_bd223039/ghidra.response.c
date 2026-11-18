void clearMarker(char *s,char marker)

{
  char *pcVar1;
  char *pos;
  char marker_local;
  char *s_local;
  
  pcVar1 = strchr(s,(int)marker);
  if (pcVar1 != (char *)0x0) {
    *pcVar1 = '\0';
  }
  return;
}