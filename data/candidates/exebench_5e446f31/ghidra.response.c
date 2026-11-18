void copy2(char *s1,char *s2)

{
  char cVar1;
  char *s2_local;
  char *s1_local;
  
  s1_local = s1;
  for (s2_local = s2; cVar1 = *s2_local, *s1_local = cVar1, cVar1 != '\0'; s2_local = s2_local + 1)
  {
    s1_local = s1_local + 1;
  }
  return;
}