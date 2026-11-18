void func0(char *text)

{
  char *pcVar1;
  char *out;
  char *vowels;
  char *text_local;
  
  out = text;
  for (text_local = text; *text_local != '\0'; text_local = text_local + 1) {
    pcVar1 = strchr("AEIOUaeiou",(int)*text_local);
    if (pcVar1 == (char *)0x0) {
      *out = *text_local;
      out = out + 1;
    }
  }
  *out = '\0';
  return;
}