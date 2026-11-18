void remove_line_ending(char *text,char ending)

{
  char *pcVar1;
  char ending_local;
  char *text_local;
  
  pcVar1 = strrchr(text,(int)ending);
  if (pcVar1 != (char *)0x0) {
    *pcVar1 = '\0';
  }
  return;
}