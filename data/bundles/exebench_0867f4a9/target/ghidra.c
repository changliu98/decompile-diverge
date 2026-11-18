int compter_mots(char *saisie,size_t *lenght)

{
  bool bVar1;
  char *pcVar2;
  size_t lenght_max;
  size_t lenght_current;
  int gui;
  int words;
  char *p;
  size_t *lenght_local;
  char *saisie_local;
  
  p = strchr(saisie,0);
  bVar1 = false;
  lenght_current = 0;
  lenght_max = 0;
  while (p = p + -1, pcVar2 = saisie, *p == ' ') {
    *p = '\0';
  }
  while (p = pcVar2, *p == ' ') {
    pcVar2 = p + 1;
  }
  words = (int)(*p != '\0');
  for (; *p != '\0'; p = p + 1) {
    if ((*p == '\"') || (*p == '\'')) {
      bVar1 = !bVar1;
    }
    else if ((*p != ' ') || (bVar1)) {
      lenght_current = lenght_current + 1;
    }
    else {
      if (lenght_max < lenght_current) {
        lenght_max = lenght_current;
      }
      lenght_current = 0;
      words = words + 1;
      for (; *p == ' '; p = p + 1) {
      }
      p = p + -1;
    }
  }
  if (lenght_max < lenght_current) {
    lenght_max = lenght_current;
  }
  *lenght = lenght_max;
  return words;
}