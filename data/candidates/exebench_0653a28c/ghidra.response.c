void reverse(char *li)

{
  char cVar1;
  char *pcVar2;
  char t;
  char *right;
  char *left;
  char *li_local;
  
  pcVar2 = li;
  do {
    right = pcVar2;
    pcVar2 = right + 1;
    left = li;
  } while (*right != '\0');
  for (; right = right + -1, left < right; left = left + 1) {
    cVar1 = *left;
    *left = *right;
    *right = cVar1;
  }
  return;
}