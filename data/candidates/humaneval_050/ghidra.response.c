void func0(char *s,int encode)

{
  int iVar1;
  size_t sVar2;
  int w;
  size_t i;
  size_t len;
  int shift;
  int encode_local;
  char *s_local;
  
  iVar1 = 0x15;
  if (encode != 0) {
    iVar1 = 5;
  }
  sVar2 = strlen(s);
  for (i = 0; i < sVar2; i = i + 1) {
    s[i] = (char)((s[i] + -0x61 + iVar1) % 0x1a) + 'a';
  }
  return;
}