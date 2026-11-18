void reverse(char *s)

{
  char cVar1;
  uint uVar2;
  char tmp;
  uint max;
  uint e;
  char *s_local;
  
  for (e = 0; uVar2 = e, s[e] != '\0'; e = e + 1) {
  }
  for (e = 0; e < uVar2 >> 1; e = e + 1) {
    cVar1 = s[e];
    s[e] = s[uVar2 - (e + 1)];
    s[uVar2 - (e + 1)] = cVar1;
  }
  return;
}