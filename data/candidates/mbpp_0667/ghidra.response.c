int func0(char *string,char *vowels)

{
  char *v;
  char *s;
  int count;
  char *vowels_local;
  char *string_local;
  
  count = 0;
  s = string;
  do {
    v = vowels;
    if (*s == '\0') {
      return count;
    }
    for (; *v != '\0'; v = v + 1) {
      if (*s == *v) {
        count = count + 1;
        break;
      }
    }
    s = s + 1;
  } while( true );
}